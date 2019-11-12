#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/*le code ci-dessous a pour objectif de générer les différentes
 *combinaisons nécessaires à la résolution du pb31
 */

int generationCombi(int longueur) {
	int tab[7] = {1, 2, 5, 10, 20, 50, 100}, tmp;
	
	//Première boucle pour faire avancer dans les combinaisons
	for (int i = 0; i < 7-longueur; i++){
		liste * l =  NULL;
		//Construction complète de la première combinaison
		//for(int k = i; k <= i+longueur-1; k++){ l = ajoutEnQueue(l, tab[k]);}
		//Curseur indiquant la valeur "pivot"
		for( int j = i+longueur-1; j <= 0; j--){
			tmp = i;
			while(tab[j] >= tab[tmp] && tmp <= 6){++tmp;}
			printf("\n");
			afficheListe(l);
			l = supprimeFin(l, tab[j]);
		}
	}
}


void generefin(liste * l, int ind, int longueur, int combi){
	int tab[7] = {1, 2, 5, 10, 20, 50, 100};
	int mesure = taille(l); int limit = longueur-combi+mesure;
	int to_complete = combi-mesure-1;

	for(int i = ind; i <= limit; i++){
		for(int j = i; j <=6 && j <= i+to_complete; j++){l = ajoutEnQueue(l, tab[j]);}
		for(int k = j; k < 6; k++){
			if(k > j){l = ajoutEnQueue(l, tab[k]);}
			printf("\n");
			afficheListe(l);
			l = supprElt(l, tab[k]);
		}
	}
}

int main(){
	int tab[7] = {1, 2, 5, 10, 20, 50, 100};
	int t1 = 0, t2 = 0, pas = 2, tmp, limit = 7;

	while(t1 <= 7-1-pas){
		liste * l = NULL;
		for(int i = t1; i <= (t1 + pas-1); i++){
			l = ajoutEnQueue(l, tab[i]);
		}
		for(int i = (t1+pas); i <= limit - 1; i++){
			l = ajoutEnQueue(l, tab[i]);
			printf("\n");
			afficheListe(l);
			//printf("suppression de l'élément %d\n", tab[i]);
			l = supprElt(l, tab[i]);
			//printf("l'élément %d a été supprimé\n", tab[i]);
		}
		t1++;
		//printf("voici l'état de la liste avant suppression : ");
		//afficheListe(l);
		//printf("\n");
		//printf("suppression de la liste car t1 s'incrémente de 1\n");
		supprimeListe(l);
	}
	printf("\n");
	return 0;
}