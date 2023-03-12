#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"

int isPrime37(int val, liste * lst){
	liste * tmp = lst; int limit = 2;
	if(val == 1){return 0;}
	if(val == 2){return 1;}
	int borne = 0;
	while (tmp != NULL && tmp->value * tmp->value <= val){ 
		if(val % tmp->value == 0) {return 0;} 
		tmp = tmp->l;
	}
	lst = ajoutEnQueue(lst, val);
	return 1;
}

int circularPrimeRight(int val, int taille, liste * lst){
	int i, tmp = val, flag = 0;
	int * r = intToTab(val); int elt = r[0];
	if(elt == 4 || elt == 6 || elt == 8 || elt == 9){ free(r); return 0;}
	for(i=1; i<taille; i++){
		tmp = tmp / 10;
		//if(isPrime37(tmp, lst) == 0){return 0;}
		if(isPrime(tmp) == 0){return 0;}
	}
	printf("\n");
	return 1;
}

int circularPrimeLeft(int val, int taille, liste * lst){
	int * tmp = intToTab(val), i, flag = 0, valToTest = 0;
	int elt = tmp[taille-1];
	if(elt == 2 || elt == 4 || elt == 6 || elt == 8 || elt == 9){ return 0;}
	for(i=0; i<taille-1; i++){
		tmp[i] = 0;
		valToTest = tabToInt(tmp, taille);
		//if(isPrime37(valToTest, lst) == 0){free(tmp); return 0;}
		if(isPrime(valToTest) == 0){free(tmp); return 0;}
	}
	free(tmp);
	return 1;
}

void test(int val, int taille, liste * lst, int tab[], int * cpt, int * somme){
	int i, tmp;
	for(i = 3; i <= 9; i=i+2){
		tmp = val* 10 + i;
		//if( isPrime37(tmp, lst) == 1 && circularPrimeLeft(tmp, taille+1, lst) == 1 && circularPrimeRight(tmp, taille+1, lst) == 1){
		if( isPrime(tmp) == 1 && circularPrimeLeft(tmp, taille+1, lst) == 1 && circularPrimeRight(tmp, taille+1, lst) == 1){
			printf("%d est un nombre premier tronquable\n", tmp);
			++(*cpt); tab[*cpt] = tmp;
			*somme += tmp;
		}
	}
}

int main(){
	int i = 0, val=9, len, input = 0, cpt = 0, somme = 0, status;
	FILE * fp = fopen("base_nbr_premiers.dat", "r");
	int tab[15];
	liste * lst = NULL;
	lst = ajoutEnQueue(lst, 2);
	lst = ajoutEnQueue(lst, 3);
	lst = ajoutEnQueue(lst, 5);
	lst = ajoutEnQueue(lst, 7);
//	int tab[15] = (37, 53, 73, 137, 139, 173, 179, 373, 379, 739, 733, 1013, 1019, 1033, 1039);
//	for(i=0; i<15; i++){
//		test(input, calculTailleEntier(val), lst, tab, &cpt);
//	}
	while((status=fscanf(fp, "%d", &input)) != EOF && cpt < 11){
			  if(status != EOF){test(input, calculTailleEntier(input), lst, tab, &cpt, &somme);}
		else{
			if(isPrime(++input)==1){test(input, calculTailleEntier(input), lst, tab, &cpt, &somme);}
		}
	}
	printf("la somme des nombres tronquables à gauche et à droite est : %d\n", somme);
/*
	while(i < 11){
		len = calculTailleEntier(val);
		if(isPrime37(val, lst)==1 && circularPrimeLeft(val, len, lst) == 1 && circularPrimeRight(val, len, lst) == 1){
			printf("la valeur %d est un premier tronquable à droite et à gauche\n",val);
			i++;
		}
		++val;
	}
*/
	return EXIT_SUCCESS;
}
