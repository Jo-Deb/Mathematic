#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "genList.c"

int TAB[9]={1, 2, 3, 4, 5, 6, 7, 8, 9};

int pgcd(int a, int b){
	if(b > a){return pgcd(b, a);}
	if(b == 0){return a;}
	return pgcd(b, a%b); 
}

int calCombinatoireRepetition(int taille, int nbrElt){
	int borne = taille + nbrElt - 1; int limit = borne - nbrElt;
	int tmp = nbrElt, m, res = 1;
	liste * num = NULL; liste * den = NULL; liste * t_list = NULL;
	for(int i = borne; i > limit; i--){num=ajoutEnTete(num, i);}
	for(int i = nbrElt; i > 1; i--){ den=ajoutEnTete(den, i);}
	
	while(den != NULL){
		tmp = den->value;
		t_list = num;
		while(tmp > 1){
			m = pgcd(t_list->value, tmp);
			t_list->value = t_list->value / m;
			tmp = tmp / m;
			t_list = t_list->l;
		}
		den=supprElt(den, den->value);
	}	

	t_list = num;
	while(t_list != NULL){ res *= t_list->value; t_list = t_list->l;}
	return res;
}

/*Il s'agit de faire des combinaisons avec répétition*/
genList * combi2(int limit, int nbr){
	if(limit == nbr){
		liste * res = NULL;
		for(int i = 1; i<=limit; i++){res=ajoutEnTete(res, i);}
		return g_createList(res);
	}
	liste * l = NULL; liste * l2 = NULL; genList * res = NULL;
	
	for(int i = 1; i<=limit; i++){
		l = createList(i);
		l = ajoutEnTete(l, i);
		res = g_ajoutEnQueue(res, l);
		for(int j = i+1; j<=limit; j++){
			l2 = recopie(l);
			l2 = remplace(l2, l->value, j);
			res = g_ajoutEnQueue(res, l2);
		}
	}
	
	return res;
}

void afficheList(genList * l){
	genList * tmp = l; liste * lt = NULL;
	while(tmp != NULL){
		lt = tmp->ptr;
		while(lt != NULL){
			if(lt->l != NULL){printf("%d, ", lt->value);}
			else{ printf("%d\n", lt->value);}
		}
		tmp = tmp->suiv;
	}
	printf("\n");
}

/*Fonction récursive pour la génération des combinaisons
 *avec répétitions 
genList * combinaison(genList * l, int taille){
	if (taille == 2){l = combi2();}	
}
*/

int main(int argc, char ** argv){
	if(argc != 3 ){printf("le nombre de paramètres est incorrect, assurez-vous de passer deux entiers non signés en paramètres.\nArrêt du programme.\n"); return EXIT_FAILURE;}
	int taille = 0, nbr = 0;
	sscanf(argv[1], "%d", &taille);
	sscanf(argv[2], "%d", &nbr);
	printf("voici les valeurs des paramètres : taille = %d et nbr = %d\n", taille, nbr);
	int ret = calCombinatoireRepetition(taille, nbr);
	printf("le nombre de combinaison avec répétition de %d pris dans 9 est : %d\n",nbr, ret);
	return EXIT_SUCCESS;
}
