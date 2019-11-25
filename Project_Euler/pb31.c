#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int TAB[7] = {1, 2, 5, 10, 20, 50, 100};

/*le code ci-dessous a pour objectif de générer les différentes
 *combinaisons nécessaires à la résolution du pb31
 */

int indexTab(int elt){
	for(int i = 0; i<=6; i++){
		if(TAB[i] == elt){return i;}
	}
	return -1;
}

int tailleSup(liste * tab[], liste * l, int *cpt){
	//printf("dans la fonction tailleSup\n");
	int max = maxListe(l);
	int ind = indexTab(max);
	liste * racine = supprimeFin(l, max);
	for(int i = ind+1; i <=6; i++){
		tab[++(*cpt)] = copie(racine);
		tab[*cpt] = ajoutEnQueue(tab[*cpt], max);
		tab[*cpt] = ajoutEnQueue(tab[*cpt], TAB[i]);
	}
	return 0;
}

int combinaisonDe2(liste * tab[]){
	int cpt = -1;
	for(int i = 0; i <= 5; i++){
		for(int j = i+1; j<=6; j++){
			cpt++;
			tab[cpt] = ajoutEnQueue(NULL, TAB[i]);
			tab[cpt] = ajoutEnQueue(tab[cpt], TAB[j]);
		}
	}
	return cpt;
}

int combi(liste * tab[], int * cpt, int nbr_elt){
	int tNessaire = nbr_elt - 1;
	for(int i = 0; i <= *cpt; i++){
		if(taille(tab[i]) == tNessaire){ tailleSup(tab, tab[i], cpt);}
	}
	return 0;
}


int main(){
	//int tab[7] = {1, 2, 5, 10, 20, 50, 100};
	liste * tab[127];
	int cpt = combinaisonDe2(tab);
	for(int i=3; i <=7; i++){
		combi(tab, &cpt, i);
	}
	for(int i = 0; i <= cpt; i++){
		printf("taille : %d - ", taille(tab[i]));
		afficheListe(tab[i]);
		printf("\n");
	}
	return 0;
}