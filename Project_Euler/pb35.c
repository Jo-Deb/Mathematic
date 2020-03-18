#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "liste.h"
#include "genList.h"

int isPrime(int val){
	int limite = 2, i;
/*	for(i=0; primeTab[i]<=lim; i++){ if((val % primeTab[i]) == 0) {return 0;} }*/
	while((limite * limite) < val){
		if((val % limite) == 0){return 0;}
		else {++limite;}
	}
	
	return 1;
}

void triTab(int tab[], int start, int taille){
	int i, j, tmp;
	for(i=start; i<taille; i++){
		for(j=i+1; j<taille && i<taille; j++){
			if(tab[j] < tab[i]){ tmp = tab[j]; tab[j] = tab[i]; tab[i]=tmp;}
		}
	}
}

void inverseTriTab(int tab[], int start, int taille){
	int i, j, tmp;
	for(i = start; i<taille; i++){
		for(j=i+1; j<taille && i<taille; j++){
			if(tab[j] > tab[i]){ tmp = tab[j]; tab[j] = tab[i]; tab[i] = tmp;}
		}
	}
}

/*Chercher le pivot le plus éloigné*/
int pivot(int tab[], int taille, int start){
	int pos = 0, pivot = 0, find = 0, i, lim = taille - 1;
	for(i=start; i<lim; i++){
		if(tab[i] < tab[i+1]){pos = i+1; find=1;}	
	}
	if(find == 1){return pos;}
	else{/*printf("Aucun pivot trouvé, la liste est entièrement triée\n");*/ return taille-1;}
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
//	free(tab);
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

/*Il faut écrire une fonction qui génère la liste générique des permutations pour les nombres de :
 *3 chiffres (999), 4 chiffres (9 999), 5 chiffres (99 999) et 6 chiffres (999 999)*/
void **  generePermutations(){
	int i, * tmp = NULL, j, foo, depart, limite;
	void ** res = malloc(4*sizeof(void));
	for(i = 3; i<=6; i++){
		foo = 0;
		for(j=1; j<=i; j++){ foo = foo * 10 + j;}
		tmp = intToTab(foo); triTab(tmp, 0, i); depart = tabToInt(tmp, i);
		tmp = intToTab(foo); inverseTriTab(tmp, 0, i); limite = tabToInt(tmp, i);
		liste * l = NULL; l = ajoutEnQueue(l, depart); 
		while(depart < limite){depart = sup(intToTab(depart), i); l = ajoutEnQueue(l, depart);}
		res[i - 3] = (void*)l;
	}
	return res;
}

int valPermute(int depart, int ordre, int taille){
	int * tab_dep = intToTab(depart), tmp = ordre, index = taille-1;
	int * tab_permut = malloc(taille * sizeof(int));
	while(tmp > 0){
		tab_permut[index] = tab_dep[(tmp % 10) - 1];
		tmp = tmp / 10;
		--index;
	}
	free(tab_dep); // La fonction intToTab effectue une allocation mémoire.
	return tabToInt(tab_permut, taille); //La fonction tabToInt effectue un free
	//Il ne faut donc pas effectuer un free sur le pointeur tab_permut
}

int decale35(int * tab, int taille){
	int tmp = tab[0], i;
	for(i=0; i<taille-1; i++){ tab[i] = tab[i+1]; }
	tab[taille-1] = tmp;
	return tabToInt(tab, taille);
}

int isPrimeCircular(int val){
	if(isPrime(val) == 1){	
		int * tmp = intToTab(val);
		int taille = calculTailleEntier(val);
		int per = decale35(tmp, taille);
		while(per != val){
			if(isPrime(per) == 0){return 0;}
			per = decale35(tmp, taille);	
		}
		return 1;
	}
	return 0;
}


int main(int argc, char ** argv){
	int i, decompte = 0;
	for(i=100; i<1000000; i++){
		if(isPrimeCircular(i) == 1){ 
			++decompte; 
			printf("%d ", i);
			if(decompte % 10 == 0){ printf("\n");}
		}
	}	
	printf("\n\nLe nombre total de nombre premier circulaire est decompte + 13 = %d + 13 = %d\n", decompte, decompte+13);
	return EXIT_SUCCESS;
}
