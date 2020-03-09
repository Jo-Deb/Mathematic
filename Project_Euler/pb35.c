#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include "genList.h"

void triTab(int tab[], int start, int taille){
	int i, j, tmp;
	for(i=start; i<taille; i++){
		for(j=i+1; j<taille && i<taille; j++){
			if(tab[j] < tab[i]){ tmp = tab[j]; tab[j] = tab[i]; tab[i]=tmp;}
		}
	}
}

/*Chercher le pivot le plus éloigné*/
int pivot(int tab[], int taille, int start){
	int pos = 0, pivot = 0, find = 0, i, lim = taille - 1;
	for(i=start; i<lim; i++){
		if(tab[i] > tab[i+1]){pos = i; find=1;}	
	}
	if(find == 1){return pos;}
	else{printf("Aucun pivot trouvé, la liste est entièrement triée\n"); return taille-1;}
}

/*Dans la sous-liste je cherche le plus petit entier supérieur tab[j_pos]*/
int majorant(int tab[], int j_pos, int taille){
	int i, majo = 9; /*chaque case de notre tableau devant contenir un chiffre d'ou le 9 comme valeur maximale*/ 
	int find = 0, index = 0;
	for(i=j_pos; i<taille; i++){
		if(tab[i] > tab[j_pos-1] && tab[i] < majo){ majo = tab[i]; find = 1; index = i;}
	}
	if(find == 1){ return index;} else {return -1;}
}

void intervertir(int tab[], int pos1, int pos2){
	int tmp = 0;
	tmp = tab[pos1];  tab[pos1] = tab[pos2]; tab[pos2] = tmp;
}

int calculTailleEntier(int val){
	int taille = 0, reste = 0, tmp = val;
	while(tmp > 0){
		reste = tmp % 10;
		tmp = tmp/10;
		++taille;
	}
	return taille;
}

int * intToTab(int val){
	int taille = calculTailleEntier(val);
	int * res = malloc(taille * sizeof(int)); 
	int i, tmp = val;
	for(i=taille-1; i>=0; i--){ res[i] = tmp % 10; tmp = tmp/10;}
	return res;
}

int tabToInt(int tab[], int taille){
	int i, res = 0;
	for(i=0; i<taille; i++){res = res * 10 + tab[i];}
	free(tab);
	return res;
}

/*L'objectif de cette fonction est de retourner le plus petit nombre supérieur
 *à celui donné en argument, avec la contrainte que celui-ci soit composé des 
 *même chiffres que le nombre en input
 */
int sup(int tab[], int taille){
	/*Le pivot est l'index où la monotonie de la suite se casse, 
	*c-a-d tab[pivot-1] < tab[pivot] > tab[pivot + 1]
	*/
	int pivot_pos = pivot(tab, taille, 0); /*J'obtiens le pivot le plus éloigné*/
	if(pivot_pos == taille-1){intervertir(tab, taille-1, taille-2); return tabToInt(tab, taille);}
	int pos_majorant = majorant(tab, pivot_pos, taille);
	if(pivot_pos < 0){printf("Aucun majorant au pivot n'a été trouvé, on retourne la valeur donnée en entrée.\n"); return tabToInt(tab, taille);}
	else{ 
		intervertir(tab, pivot_pos-1, pos_majorant); 
		triTab(tab, pivot_pos, taille);
	}
	return tabToInt(tab, taille); 
}

void testPermutation(int val, liste * res, int * decompte, int start){
	liste * l = split(val); liste * pcr = l; int pos = 1;
	/*Positionnement*/
	while(pos < start){ pcr = pcr->l; ++pos;}
	l = trieSousListe(l, start);
	res = ajoutEnTete(res, listeToInt(l));
	
}


int main(int argc, char ** argv){
	int in1, in2;
	if(argc != 2){ 
		printf("Vous devez donner deux valeurs entières; le programme va s'arrêter en échec\n"); 
		exit(EXIT_FAILURE);
	}
	sscanf(argv[1], "%d", &in1);
	
	liste * l1 = split(in1);
	l1 = listTrie(l1);
	l1 = triInverse(l1);
	int limite = listeToInt(l1);
	printf("limite = %d\n", limite);
	int taille = calculTailleEntier(in1);
	printf("taille = %d\n", taille);
	printf("____________________début des permutations : \n");
	while(in1 < limite){
		in1 = sup(intToTab(in1), taille);
		printf("%d\n", in1);
	}
	printf("____________________Fin des permutations\n");
	return EXIT_SUCCESS;
}
