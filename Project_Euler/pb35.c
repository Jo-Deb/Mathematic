#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include "genList.h"

/*Une fonction qui calcule toutes les permutations d'un entier
 *precTaf: définit la valeur qui précède dans la liste de travail
 *			  la valeur maxmimun
 *suivl: définit la valeur qui suit precTaf dans la liste triée l
*/

liste * permutation(int val){
	liste * l  = listTrie(split(val)); liste * travail = recopie(l);
	liste * tmp = recopie(l);  int lim = listeToInt(triInverse(tmp));
	supprimeListe(tmp); tmp = NULL;
	printf("Voici la liste initiale: ");
	afficheListe(l);
	printf("\n");
	
	int maxi = maxListe(travail), posiMax = 0, taille_l = taille(l), precTaf = 0, suivl = 0;
	int conver = 0, antiBoucle = 0;
	liste * res = NULL;

	while(conver < lim && antiBoucle < 100){
		antiBoucle++;
		posiMax = getPosition(travail, maxi);
		printf("#########################NEW#########################\n");
		if(posiMax == taille_l){
			travail = inversePosition(travail, posiMax, posiMax - 1);
			printf("Dans le if, voici la valeur de la liste travail après inversion et tri: ");
			afficheListe(travail);
			printf("\n");
		}
		else{
			precTaf = precedent(travail, maxi);
			suivl = suivant(l, precTaf);
			travail = inversePosition(travail, getPosition(travail, precTaf)\
						 , getPosition(travail, suivl));
			travail = trieSousListe(travail, getPosition(travail, suivl) + 1);
			printf("Dans le else, voici la valeur de la liste travail après inversion et tri: ");
			afficheListe(travail);
			printf("\n");
			conver = listeToInt(travail);
			res = ajoutEnTete(res, conver);
		}
		printf("#####################################################\n");
	}
	return res;
}

int main(int argc, char ** argv){
	int in1, in2;
	if(argc != 3){ 
		printf("Vous devez donner deux valeurs entières; le programme va s'arrêter en échec\n"); 
		exit(EXIT_FAILURE);
	}
	sscanf(argv[1], "%d", &in1);
	sscanf(argv[2], "%d", &in2);
	
	liste * l1 = split(in1);
	liste * l2 = split(in2);	
	l1 = listTrie(l1);
	l2 = listTrie(l2);
	afficheListe(l1); printf("\n");
	afficheListe(l2); printf("\n");	
	printf("____________________début des permutations : \n");
	permutation(in1);
	return EXIT_SUCCESS;
}
