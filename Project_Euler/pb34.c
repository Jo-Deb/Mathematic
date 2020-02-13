#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "genList.h"

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

/*Il s'agit de faire des combinaisons avec répétition
 *Je comprends que le 2ème argument int nbr se sert
 *absolument à rien
*/
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
			lt = lt->l;
		}
		tmp = tmp->suiv;
	}
	printf("\n");
}

/*On commence avec des listes de taille 2
 *et on augmente au fur et à mesure*/
genList * augmente(genList * l, int limit){
	genList * res = NULL; genList * p = l; liste * pcr = NULL;
	
	while(p != NULL){
		pcr = p->ptr;
		int i = maxListe(pcr);
		for(int j = i; j<=limit; j++){
			liste * tmp = recopie(pcr);
			tmp = ajoutEnQueue(tmp, j);
			res = g_ajoutEnQueue(res, tmp);
		}
		supprimeListe(pcr);
		p = p->suiv;
	}
	g_supprimeListe(l);
	return res;
}

/*On commence avec des listes de taille 2
 *et on augmente au fur et à mesure*/
genList * combinaison(int limit, int taille){
	genList * res = NULL;
	res = combi2(limit, taille);

	for(int i = 3; i<=taille; i++){res = augmente(res, limit);}
	return res;
}


int factorielle(int n){ 
	if (n == 1) {return 1; } else {return n * factorielle(n-1);}
}


int tailleEntier (int elt){
	int compteur = 0; int tmp = elt;
	while((tmp = elt / 10) > 0){++compteur;}
	return ++compteur; 	
}


int compare(liste * lst, int elt){
	liste * tmp = lst; int val = elt;
	if(taille(lst) == tailleEntier(elt)){
		while(val > 0){
			if(EstPresent(lst, val%10) == 1){return 1;}
			val = val / 10;
		}
		return 0;	
	}
	return 1;
}

genList * test (genList * lst){
	genList * res = NULL; genList * pcr = lst; liste * lt = NULL;
	int somme;
	while( pcr != NULL){
		lt = pcr->ptr; somme = 0;
		while(lt!=NULL){somme += factorielle(lt->value); lt = lt->l;}
		if (compare(lt, somme) == 0){res = g_ajoutEnQueue(res, pcr->ptr);}
		pcr = pcr->suiv;
	}
	g_supprimeListe(lst);
	return res;
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
	genList * res = NULL;
	/*
		printf("voici les valeurs des paramètres : taille = %d et nbr = %d\n", taille, nbr);
		int ret = calCombinatoireRepetition(taille, nbr);
		printf("le nombre de combinaison avec répétition de %d pris dans 9 est : %d\n",nbr, ret);
		afficheList(combi2(taille, nbr));
		return EXIT_SUCCESS;
	*/
	res = test(combinaison(6,3));
	afficheList(res);
	res = test(combinaison(6,4));
	afficheList(res);
	return EXIT_SUCCESS;
	
}
