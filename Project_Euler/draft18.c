#include<stdio.h>
#include<stdlib.h>

int myDB[15][15];

typedef struct pb18_elt{
	int valeur;
	int col;
	int line;
	int droite;
	int gauche;
} pb_elt;

pb_elt * createElt(int v, int c, int l){
	pb_elt * ptr = malloc(sizeof(pb_elt));
	ptr->valeur = v; ptr->col = c; ptr->line = l;
	ptr->droite = 1; ptr->gauche = 1;
	return ptr;
}

int sommeStruct(pb_elt * tab[]){
	int somme = 0, i = 0;
	while(tab[i] != NULL){somme = somme + tab[i]->valeur; ++i;}
	return somme;
}

void afficheCh(pb_elt * tab[]){
	int somme = 0, i = 0;
	while(tab[i]!=NULL && i < 15){
		//if(tab[i+1] == NULL || i == 14){printf("\033[1;31m");}
		printf("%d-", tab[i]->valeur); 
		//if(tab[i+1] == NULL || i == 14){printf("\033[0m");}
		somme = somme + tab[i]->valeur;
		++i;
	}
	printf("la somme donne : %d\n", somme);
}

int arrangeAll(pb_elt * tab[], int i, int * compteur){
	int tmp = i, precCol = 0, j = i;
	printf("j = %d\n", j);
	if(tab[j]->droite == 1 || tab[j]->gauche == 1){ 
		*compteur = sommeStruct(tab);
		printf("on retourne %d\n", j);
		return j;
	}
	if( tab[j]->droite == 0 && tab[j]->gauche == 0){
		precCol = tab[j]->col;
		free(tab[j]); 
		tab[j] = NULL;
		if (tab[j-1]->col == precCol){tab[j-1]->gauche = 0;}
		if (tab[j-1]->col + 1 == precCol){tab[j-1]->droite = 0;}
		printf("on retourne arrangeAll(tab, %d, compteur)\n", j-1);
		return arrangeAll(tab, j-1, compteur);
	}
	return j;
}

int loopStep(pb_elt * tab[], int i, int position, int * curTot, int * calTot){
	int c = 0, test = 0;
	if(position == 1 /*gauche*/){c = tab[i-1]->col;}else{ c = tab[i-1]->col+1;}	
	int tmp = myDB[i][c]; 
	afficheCh(tab);
	test = *curTot - (*calTot + tmp + (14 - i)*99);
	printf("*curTot - (*calTot + tmp + (14 - i)*99) = %d - (%d + %d + (14 - %d)*99)) = %d\n"
	, *curTot, *calTot, tmp, i, test);
	if(test < 0 && i != 14){
		tab[i] = createElt(tmp, c, i);
		printf("allocation mémoire pour tab[%d] faite.\n", i);
		*calTot = *calTot + tmp;
		printf("calTot = %d et i vaut : %d\n", *calTot, i);
		return i;
	}
	else{if (test < 0 && i == 14){
			*curTot = *calTot + tmp;
			tab[i] = createElt(tmp, c, i);
			tab[i]->droite = 0;
			tab[i]->gauche = 0;
			printf("allocation mémoire pour tab[%d] faite.\n", i);
			printf("Changement de chemin maximun. Le nouveau chemin max est: ");
			afficheCh(tab);
			return arrangeAll(tab, i, calTot);
		}
	}	if( test >= 0 && tab[i]!=NULL){
 			if (position == 1){tab[i]->gauche = 0;}else{tab[i]->droite = 0;}
 			printf("appel de la fonction arrangeAll(tab, %d, calTot)\n", i);   
			return arrangeAll(tab, i, calTot);
		}
		else {
			if(test >= 0 && tab[i] == NULL){
				if (position == 1){tab[i-1]->gauche = 0;}else{tab[i-1]->droite = 0;} 
				printf("appel de la fonction arrangeAll(tab, %d, calTot)\n", i-1);  
				return arrangeAll(tab, i-1, calTot);
			}
		}
		return i;
}

void getDatafromFile(){
	FILE *dataFile = fopen("pb18.data", "r");
	int tmp, i = 0;
	//Boucle pour récupérer les données
	for(i = 0; i < 15; i++){
		for(int j = 0; j <= i ; j++){ 
			fscanf(dataFile, "%d", &tmp); 
			myDB[i][j] = tmp; 
		} 
	}
	if(feof(dataFile)){ fclose(dataFile); }
	//On affiche les données du tablesau;
	for(int i = 0; i < 15; i++){
		for(int j = 0; j <= i ; j++){ printf("%2d ", myDB[i][j]); }
		printf("\n");
	}
}

void traitement(){
	int currentTot = 0; int computingTotal = 0; int tmp = 0; int c = 0; int test = 0;
	pb_elt * tab[15];
	for(int i = 0; i < 15; i++){tab[i] = NULL;}
	tab[0] = createElt(myDB[0][0], 0, 0);
	computingTotal += tab[0]->valeur;
	// le chemin pour initialiser currentTot sera la somme de toute les cellules
	// d'index 0;
	for(int i = 0; i < 15; i++){currentTot = currentTot + myDB[i][0];}
	printf("currentTot a été calculé et vaut : %d\n", currentTot);
	for(int i = 1; i < 15; i++){
		if(tab[i-1]->droite == 1 ){
			printf("lancement de loopStep(tab, %d, 0, %d, %d)\n", i, currentTot, computingTotal);
			i = loopStep(tab, i, 0, &currentTot, &computingTotal);
		}
		else {if(tab[i-1]->gauche == 1 ){
			printf("lancement de loopStep(tab, %d, 0, %d, %d)\n", i, currentTot, computingTotal);
			i = loopStep(tab, i, 1, &currentTot, &computingTotal);
		}}
		printf("_____________________________________________________________________________________\n\n");
	}
}

int main () {
	getDatafromFile();
	traitement();
	return 0;
}
