#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

#define	LIMIT 10
typedef struct Fraction{
	int num;
	int den;
}fraction;

fraction * createFraction(int n, int d){
	fraction * f = malloc(sizeof(fraction));
	f->num = n;
	f->den = d;
	return f;
}

int pgcd(int a, int b){
	if(b == 0){ return a;}
	return pgcd(b, a%b);
}

int okFrac(int num, int deno){
	if (num > deno){ return 0;}
	if (pgcd(deno, num) == 1) {return 0;}
	return 1;
}

liste * genFraction(int num, int deno, int gen){
	liste * l = NULL;
/*Si bien codé, ici on devrait tester les valeurs données en 
 *argument et s'assurer que chaque valeur est inférieure à 9*/
	int n, d;
	for(int i=0; i<=1; i++){
		switch(i){
			case 	0:	n = num*10 + gen;
						break;
			case 	1:	n = gen*10 + num;
						break;
			default:	break;
		}
		for(int j=0; j<=1; j++){
			switch(j){
			case 	0:	d = deno*10 + gen;
						break;
			case 	1:	n = gen*10 + deno;
						break;
			default:	break;
			}
			if(okFrac(n, d) == 1){ l = ajoutEnTete()}
		}
	}
}

int main(){
	fraction * f = createFraction(1, 2);
	printf("la fraction définie est la suivante : %d/%d\n", f->num, f->den);
	return 0;
}
