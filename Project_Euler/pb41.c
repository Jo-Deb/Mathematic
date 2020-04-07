#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"


int doublon(int * tab, int taille){
	int i, j;
	for(i=0; i<taille-1; i++){
		if(tab[i]==0){ return 0;}
		for(j=i+1; j<taille; j++){ if(tab[i]==tab[j] || tab[j]==0){ return 0;} }
	}
	return 1;
}

int pandigital(int * tab, int taille){
	triTab(tab, taille);
	int i;
	for(i=0; i<taille-1; i++){
		if(tab[i+1]!=(tab[i]+1)){ return 0;}
	}
	return 1;
}

int pandigitalPrime(int val){
	int * tmp = intToTab(val);
	int taille = calculTailleEntier(val);
//	if(doublon(tmp, taille) == 0){ free(tmp); return 0;}
//	if(pandigital(tmp, taille) == 0){free(tmp); return 0;}
	if(isPrime(val) == 0){ free(tmp); return 0;}
	free(tmp);
	return 1;
}

/*Prochain plus petit pandigital*/
int pppPandigital(int * tab, int * depart, int taille){
	int i, positionMin = getPositionMin(tab, *depart, taille);
	if(positionMin == taille-1){ 
		invert(tab, taille-2, taille-1);
		if(taille - *depart == 2){ *depart = 0;}
		return tabToInt(tab, taille);
	}
	if((taille - *depart)==2){
		triSousTab(tab, taille, *depart); 
		*depart = 0;
		return tabToInt(tab, taille);
	}
	int posPivot = positionPivot(tab, *depart, taille);
//	printf("positionPivot:%d\t",posPivot);
	int posPgnf = positionPgnf(tab, posPivot, taille);
//	printf("posPgnf:%d\t",posPgnf);
	if(posPgnf==-1){ ++(*depart); return pppPandigital(tab, depart, taille);}
	invert(tab, posPivot-1, posPgnf);
	inverseTriSousTab(tab, taille, posPivot);
	*depart = posPivot;
	return tabToInt(tab,taille);
}

int main(){
	int i=54321;
	int dcpt = 0, taille=calculTailleEntier(i), depart=0;
	int * tab = intToTab(i);
	
	while(i > 12345){
		i = pppPandigital(tab, &depart, taille);
		printf("%d\t taille: %d\n",i, depart);
		++dcpt;
	}
/*
	while(i>=123456789){
			i = pppPandigital(tab, &depart, 9);
		printf("scan de %d\n", i);
		if(pandigitalPrime(i)==1){
			printf("le nombre pandigital premier le plus grand est : %d\n", i);
			return EXIT_SUCCESS;
		}
	//	--i;
	} */
	return EXIT_SUCCESS;
}
