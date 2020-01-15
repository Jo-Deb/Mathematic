#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

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

int compare(void * f1, void * f2){
	fraction * tf1 = f1;
	fraction * tf2 = f2;
	if((tf1->num == tf2->num) && (tf1->den == tf2->den)){return 0;}
	return 1;
}

genList * genFraction(int num, int deno, int gen){
	genList * l = NULL;
/*Si bien codé, ici on devrait tester les valeurs données en 
 *argument et s'assurer que chaque valeur est inférieure à 9*/
	int n, d;
	int (*pf)(void *, void *) = &compare;
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
			case 	1:	d = gen*10 + deno;
						break;
			default:	break;
			}
			if(okFrac(n, d) == 1){ l = ajoutEnTete(l, createFraction(n,d));}
		}
	}
	l = enleveDoublon(l, pf);
	return l;
}

genList * testFrac(fraction * init, fraction * gen, genList * l){
	int t_pgcd = pgcd(gen->den, gen->num);
	fraction * tmp = createFraction(gen->num / t_pgcd, gen->den / t_pgcd);
	if((init->num % tmp->num) == 0 && (init->den % tmp->den) == 0){
		l = ajoutEnTete(l, gen);
		printf("la fraction %d/%d peut se réduire à %d/%d\n", gen->num, gen->den, init->num, init->den);
	}
	return l;
}

int main(){
/*******************TESTS UNITAIRES ******************************************/
//	fraction * f = createFraction(1, 2);
//	printf("la fraction définie est la suivante : %d/%d\n", f->num, f->den);
	genList * l = genFraction(4,8,9);
	fraction * f;
	fraction * init = createFraction(4, 8);
	genList * result = NULL;
	/*On devrait avoir une liste de 4 fractions 
	 *12/22, 21/22 + 2 doublons*/
	while(l != NULL){
		f = l->ptr;
		printf("la fraction %d/%d\n", f->num, f->den);
		result = testFrac(init, f, result);
		l = l->suiv;
	}
/*****************************************************************************/
	return 0;
}
