#include<stdio.h>
#include<stdlib.h>

int myDB[15][15];
int workDB[15][15];

void getDatafromFile(){
	FILE *dataFile = fopen("pb18.data", "r");
	int tmp, i = 0;
	//Boucle pour récupérer les données
	for(i = 0; i < 15; i++){
		for(int j = 0; j <= i ; j++){ 
			fscanf(dataFile, "%d", &tmp); 
			myDB[i][j] = tmp;
			workDB[i][j] = tmp; 
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
	for(int i = 14; i > 0; i--){
		printf("_________traitement pour la ligne %d et %d______________________\n", i, i-1);
		for(int j = 0; j < i; j++){
			if (myDB[i][j] >= myDB[i][j+1]){workDB[i-1][j] += myDB[i][j];}
			else {workDB[i-1][j] += myDB[i][j+1];}
		}
		printf("ligne 1:"); for(int j=0; j < i; j++){printf("%4d", myDB[i-1][j]);} printf("\n");
		printf("ligne 2:"); for(int j=0; j <= i; j++){printf("%4d", myDB[i][j]);} printf("\n");
		printf("ligne 3:"); for(int j=0; j < i; j++){printf("%4d", workDB[i-1][j]);} printf("\n");
		printf("_________________________________________________________________\n\n");
		for(int j=0; j < i; j++){myDB[i-1][j] = workDB[i-1][j];}
	}
}


int main(){
	getDatafromFile();
	traitement();
}