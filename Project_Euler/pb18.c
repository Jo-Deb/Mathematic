#include<stdio.h>
#include<stdlib.h>

int myDB[15][15];
int tabDesMax[15];

typedef struct pb18_elt{
	int valeur;
	int col;
	int line;
	int droite;
	int gauche;
} pb_elt;

pb_elt * createElt(int v, int c, int l){
	pb_elt * ptr = malloc(sizeof pb_elt);
	ptr.valeur = v; ptr.col = c; ptr.line = l;
	ptr.droite = 1; ptr.gauche = 1;
	return ptr;
}

int sommeStruct(pb_elt tab[], int s){
	int decompte = 0;
	for(int i = 0; i <= s; i++){decompte = decompte + tab[i].valeur;}
}

void traitement(){
	int currentTot = 0; int computingTotal = 0; int tmp = 0; int c = 0; int test = 0;
	pb_elt * tab[15];
	for(int i = 0; i < 15; i++){tab[i] = NULL;}
	// le chemin pour initialiser currentTot sera la somme de toute les cellules
	// d'index 0;
	for(int i = 0; i < 15; i++){currentTot = currentTot + myDB[i][0];}
	for(int i = 0; i < 15; i++){
		if(i==0){
			tab[i]=createElt(myDB[i][i], i, i); 
			computingTotal = computingTotal + tab[i].valeur;
		}else{
			if(tab[i-1].droite == 1){
				c = tab[i-1].col; tmp=myDB[i][c];
				test = computingTotal + tmp + (14 - i)*99 - currentTot;
				if (test > 0)
			}
		}	
	}
}

void indiceMax(int ligne){
	int maxIndex = 0;
	for(int i = 0; i <= ligne; i++){ 
		printf("\n ligne vaut %d\n", ligne);
		if(myDB[ligne][i] > myDB[ligne][maxIndex]){maxIndex = i;} 
		printf("i vaut %d, myDB[ligne][i] vaut %d, maxIndex vaut %d et myDB[ligne][maxIndex] vaut %d\n",
		i, myDB[ligne][i], maxIndex, myDB[ligne][maxIndex]);
	}
	tabDesMax[ligne]=maxIndex;
}


int somme(int* tab){
	int somme = 0; 
	for (int i = 0; i < 15; i++){ somme = somme + tab[i]; }
	return somme;
}

void afficheCh(int * tab){
	int somme = 0;
	for(int i=0; i<15; i++){ printf("%d-", tab[i]); somme = somme + tab[i]; }
	printf("la somme donne : %d\n", somme);
}


int * cheminConcurrent(int l, int c){
	//printf("\n###############################################################################\n");
	//printf("ligne = %d et colonne = %d\n", l, c);
	int* tab = malloc(15 * sizeof(int)); 
	for(int a = 0; a < 15; a++){ tab[a] = 0;}
	tab[l] = myDB[l][c];
	//printf("tab[%d] = %d\n", l, tab[l]);
	int adj1=0, adj2=0, col=c;
	for(int j = l-1; j>=0; j--){
		adj1 = myDB[j][col - 1]; adj2 = myDB[j][col];
		if (adj1 >= adj2){/*printf("%d-", adj1);*/ col--; tab[j]=adj1;} else {/*printf("%d-", adj2);*/ tab[j]=adj2;}
	}
	col=c;
	for(int j = l+1; j < 15; j++){
		adj1 = myDB[j][col]; adj2 = myDB[j][col + 1];
		if (adj1 >= adj2){/*printf("%d-", adj1);*/ tab[j]=adj1;} else {/*printf("%d-", adj2);*/ tab[j]=adj2; ++col;}
	}

	//printf("\n la somme de ce chemin donne %d", somme(tab));
	//printf("\n###############################################################################\n");
	return tab;
}


int plusGrandChemin(){
	int etl = 0, col=0, sommeVs=0, sommeCh=0, adj1=0, adj2=0, nbr_calcule=0;
	int * ch = cheminConcurrent(0,0); nbr_calcule++;
	//int* ch=malloc(15 * sizeof(int)); 
	//ch[0]=myDB[0][0];
	for(int a = 1; a < 15; a++){ ch[a] = 0;}

	for(int i = 1; i < 15; i++){
		//adj1=myDB[i][col]; adj2=myDB[i][col+1];
		//if (adj1 >= adj2){ch[i]=adj1;} else { ch[i]=adj2; col = col + 1;}
		//Boucle pour voir les concurrents
		for(int j = 0; j <= i; j++){ 
			if (1==1/*j!=col && myDB[i][j] > ch[i]*/){
				int* vs = cheminConcurrent(i, j); 
				nbr_calcule++;
				sommeVs=somme(vs); sommeCh=somme(ch);
				printf("###############################################################\n");
				printf("vs:");afficheCh(vs);
				printf("vs\n");
				printf("ch:");afficheCh(ch);
				printf("###############################################################\n\n");
				if(sommeVs > sommeCh){ free(ch); ch = vs; col = j;}
				else{free(vs);}
			}
		}
	}
	printf("le plus grand chemin est:");
	for(int a = 0; a < 15; a++){ printf("%d-", ch[a]);}
	printf("\n");
	sommeCh=somme(ch);
	printf("la somme de ce chemin fait : %d\n", sommeCh);
	printf("le nombre de chemin calculé au total est : %d\n", nbr_calcule);
	return sommeCh;
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

int main(){
	//initialisation de tabDesMax
	for(int j = 0; j < 15; j++){ tabDesMax[j] = 0; }
	for(int i=0; i<15; i++){
		for(int k=0; k<15; k++){ myDB[i][k] = 0;}
	}
	getDatafromFile();
	plusGrandChemin();	
}
