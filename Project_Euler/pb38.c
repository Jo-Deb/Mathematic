#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"


int doublon(int val){
	int taille = calculTailleEntier(val), *tmp = intToTab(val), i,j;
	if(tmp[0] == 0){ return 0;}
	for(i=0; i<taille-1; i++){
		for(j=i+1; j<=taille-1; j++){if(tmp[i]==tmp[j] || tmp[j]==0) {return 1;} }
	}
	return 0;
}

int multiply10(int val, int taille){
	int i;
	for(i=1; i<=taille; i++){val = 10 * val;}
	return val;
}

int test(int val){
	int i, cible = 9, res=0, taille=0, pcr;
	for(i=1; i<=9; i++){
		pcr = val * i;
		if(doublon(pcr) == 1) {return 0;}
		taille = calculTailleEntier(pcr);
		if(cible !=0 && taille > cible){ return 0;}
		if(taille <= cible){
			res = multiply10(res, taille); res += pcr;
			cible = cible - taille;
			if(doublon(res) == 1) {return 0;}
		} 
		if(cible == 0){
			printf("le nombre %d génère le pandigital : %d\n", val, res);
			return res;
		}
	}
	return res;
}


int main(){
	int max = 0, result = 0, i;
	test(192);
	for(i=1; i<=9999; i++){
		 result = test(i);
		if(result > 0){
			printf("%d donne le multiple pandigital %d\n", i, result);
			if(result > max){ max = result;}
		}
	}
	printf("le grand multiple pandigital produit est %d\n", max);
	return EXIT_SUCCESS;
}
