#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"

liste * conversionBinaire(int val){
	liste * tmp = NULL;
	int reste, dividende = val;
	while(dividende > 0){
		reste = dividende % 2;
		tmp = ajoutEnTete(tmp, reste);
		dividende = dividende / 2;
	}
	return tmp;
}

int * listeToTab(liste * l){
	int lon = taille(l);
	int i; liste * tmp = l;
	int * tab = malloc(lon * sizeof(int));
	for(i=0; i<lon && tmp!=NULL; i++){ tab[i] = tmp->value; tmp = tmp->l; }
	return tab;
}

int verifPalindrome(int * tab, int taille){
	int moitie = taille/2, i, is_ok = 1;
	for(i = 0; i < moitie; i++){
		if(tab[i] != tab[taille - (i+1)]){is_ok = 0; free(tab); return 0;}
	}
	free(tab);
	return 1;
}

int main(){
	int somme = 0, i, tempTaille, len;
	liste * tmp = NULL;
	for(i=1; i < 1000000; i++){
		len = calculTailleEntier(i);
		if(len == 1){
			tmp = conversionBinaire(i);
			tempTaille = taille(tmp);
			if(verifPalindrome(listeToTab(tmp), tempTaille) == 1){
				somme += i;
				printf("%d est un palindrome décimal et binaire :", i);
				afficheListe(tmp);
				printf("\n");
			}
		}
		else{
			tmp = conversionBinaire(i);
			tempTaille = taille(tmp);
			if( verifPalindrome(intToTab(i), len) == 1 && 
				 verifPalindrome(listeToTab(tmp), tempTaille) == 1 ){
				somme += i;
				printf("%d est un palindrome décimal et binaire :", i);
				afficheListe(tmp);
				printf("\n");
			} 
		}
	}
	printf("la somme des nombres palindromes décimaux et binaires est : %d\n", somme);
	return EXIT_SUCCESS;
}
