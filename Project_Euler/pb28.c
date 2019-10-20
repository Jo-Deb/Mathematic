#include <stdio.h>
#include <stdlib.h>

int main(){
	int carre[1001][1001], square = 1001*1001, deb = 0, limit = 1001, somme = 0;
	//initialisation du carre
	for( int i = 0; i < limit; i++){
		for(int k = 0; k < limit; k++){carre[i][k] = 0;}
	}

	//chargement du carré
	for(int i = deb; i < limit; i++){
		//ligne haute du carré
		for(int j = limit - 1; j >= i; j--) { carre[i][j] = square; square--; }
		//Colonne de droite
		for(int k = i+1; k < limit; k++) 	{ carre[k][i] =  square; square--; }
		//ligne basse
		for(int l=i+1; l < limit; l++)		{ carre[limit-1][l] = square; square--; }
		//colonne de gauche
		for(int m = limit - 2; m > i; m--)	{ carre[m][limit - 1] = square; square--; }
		limit = limit - 1;
	}
	limit = 1001;
	printf("\n");
	//affichage
	for(int i = 0; i < limit; i++){
		printf("\t");
		for(int k=0; k < limit; k++) { printf("%6d ", carre[i][k]); } 
		printf("\n");
	}
	printf("\n");

	//calcul final
	for(int i = 0; i < limit; i++){
		if (i != (limit-1-i)){ somme = somme + carre[i][i] + carre[i][limit-1-i]; }
		else{ somme = somme + carre[i][i]; }
	}
	printf("somme des diagonales = %d\n", somme);

	return 0;
}