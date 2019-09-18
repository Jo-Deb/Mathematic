#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

/*typedef struct tableau{
	int * tab;
	int taille;
} table;
*/

 table * createStruct(int taille){
 	table * ptr = malloc(sizeof(table));
 	ptr->tab = malloc(sizeof(int)*taille);
 	ptr->taille = taille;
 	return ptr;
 }

 table * additionLongue(table * elt1, table * elt2){
 	int max, min, taille, tmp; 
 	int retenu = 0;
 	int * pelt1 = elt1->tab; int *pelt2 = elt2->tab;
 	int taille1 = elt1->taille; int taille2 = elt2->taille;
	if( taille1 > taille2 ){ max = taille1; min = taille2;}
 	else{ max = taille2; min = taille1;}
 	taille = max + 1;
	table * result = createStruct(taille);
	int * tResult = result->tab;

 	for(int i = 0; i <= max; i++){
 		while(i < min){
 			tmp = pelt1[taille1 - (i+1)] + pelt2[taille2 - (i+1)] + retenu;
 			if(tmp >= 10){ tResult[taille - (i+1)] = tmp % 10; retenu = 1;}
 			else { tResult[taille - (i+1)] = tmp; retenu = 0;}
 			++i;
 		}
 		while(i < max){
 			if( max == taille1){ tmp = pelt1[taille1 - (i+1)] + retenu; }
 			else { tmp = pelt2[taille2 - (i+1)] + retenu; }
 			if(tmp >= 10){ tResult[taille - (i+1)] = tmp % 10; retenu = 1;}
 			else { tResult[taille - (i+1)] = tmp; retenu = 0;}
 			++i;
 		}
 		if(i == max) {tResult[taille - (i+1)] = retenu;}
 	}
 	return resize(result);
 }

table * resize(table * to_resize){
	int taille = to_resize->taille;
	int * tab = to_resize->tab;
	int i = 0;

	while(tab[i]==0){--taille; ++i;}
	table * result = createStruct(taille);
	for(int j = i; j < to_resize->taille; j++){result->tab[j-i] = tab[j];}
	free(to_resize);
	return result;
}

int * addition_demesurer(int * elt1, int * elt2){
	int taille = 0, taille1 = 0, taille2 = 0, i = 0, tmp, retenu = 0;
	
	while(elt1[i] != '\0'){ if(elt1[i] != '#') {taille1++; } i++; }
	i = 0; int min, max;
	while(elt2[i] != '\0'){ if(elt2[i] != '#') {taille2++; } i++; }
	if(taille1 > taille2){ max = taille1; min = taille2;}
	else{ max = taille2; min = taille1;}
	taille = max + 2;
	int * result = malloc(sizeof(int)*taille);

	printf("debut de la boucle de d'addition\n");

	for(int i = 0; i < taille; i++){
		printf("taille - (i+1) = %d\n", taille - (i+1));
		printf("taille1 - (i+1) = %d\n", taille - (i+1));
		printf("taille2 - (i+1) = %d\n", taille - (i+1));
		if(i == 0){ result[taille - (i+1)] = '\0';}
		if(i > 0 && i <= min - 1){
			tmp = elt1[taille1 - (i+1)] + elt2[taille2 - (i+1)];
			if(tmp+retenu >= 10){ result[taille - (i+1)] = (tmp + retenu) % 10; retenu = 1; }
			else{ result[taille - (i+1)] = tmp + retenu; retenu = 0;}
			printf("On boucle dans la somme\n");	
		}
		if( i > 0 && i > min - 1){
			if( i < max - 1){
				printf("On boucle dans la somme\n");
				if( max == taille1){ result[taille - (i+1)] = elt1[taille1 - (i+1)] + retenu; retenu = 0;}
				if( max == taille2){ result[taille - (i+1)] = elt2[taille2 - (i+1)] + retenu; retenu = 0;}
			}
			else{ if(retenu > 0){result[taille - (i+1)] = retenu; retenu = 0;}
				  else{ printf("La boucle d'addition est fini;"); result[taille - (i+1)] = '#'; }
			}
		}
	}
	printf("Début de l'affichage du résultat\n");
	for (int i = 0; i < taille; i++) { printf("%d", result[i]); }
	printf("\n");
	return result;
}
