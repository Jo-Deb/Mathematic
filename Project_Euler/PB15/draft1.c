#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIGNE 20
#define COLONNE 20


/*structure pour les noeuds des arbres binaires */

struct node {
	short  value;
	struct node *genitrice;
	struct node *bas;
	struct node *droit;
};

struct node* createNode (short val, struct node* genit, struct node* b, struct node* d){
	//Allocation mémoire pour le nouveau noeud
	struct node* noeud = (struct node*)malloc(sizeof(struct node));
	noeud->value = val;
	noeud->genitrice = genit;
	noeud->bas = b;
	noeud->droit = d;
	return(noeud);
}

void createTable(int tab[][COLONNE]){
	for (int i=0; i<20; i++){ 
		for (int j=0; j<20; j++){ tab[i][j]=20*i+j+1; printf("%3d ", tab[i][j]);}
		printf("\n");
	}
}

void chemin(char* str, int tab[][COLONNE], short int line , short int col, int* compteur){
	char val[4]; /*espace pour caster la valeur entière avec sprintf*/
	sprintf(val, "%d", tab[line][col]);
	str = strcat(str, val); /*on concatene val avec str afin de construire tout le chemin*/
	
	if (tab[line][col] == 400) { 
		(*compteur)++; 
		printf("chemin %d: %s\n", *compteur, str); 
		return;
	}

	if ((tab[line][col] % 20) == 0){return chemin(str, &tab[COLONNE], line+1, col, compteur);}
	if (tab[line][col] >= 380){return chemin(str, &tab[COLONNE], line, col+1, compteur);}
	chemin(str, &tab[COLONNE], line, col+1, compteur);
	chemin(str, &tab[COLONNE], line+1, col, compteur);
}

int main(){
	int tab[LIGNE][COLONNE];
	char* str = (char*) malloc(400*sizeof(char));
	int* compteur = (int*) malloc(sizeof(int));
	createTable(tab);
	chemin(str, &tab[COLONNE], 0, 0, compteur);
//	printf("sizeof(char) = %lu\n", sizeof(char));
 //  printf("sizeof(short) = %lu\n", sizeof(short));
 //  printf("sizeof(int) = %lu\n", sizeof(int));
 //  printf("sizeof(long) = %lu\n", sizeof(long));
 //  printf("sizeof(long long) = %lu\n", sizeof(long long));
 //  printf("sizeof(float) = %lu\n", sizeof(float));
  // printf("sizeof(double) = %lu\n", sizeof(double));
  // printf("sizeof(long double) = %lu\n", sizeof(long double));
	return 0;
}
