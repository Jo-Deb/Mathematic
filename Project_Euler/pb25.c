#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

/*The Fibonacci sequence is defined by recurrence relation:
Fn= Fn-1 + Fn-2, where F1 = 1 and F2 = 1
The 12th term, F12 is the first term to contain three digits.
What is the index of the first term in the Fibonacci sequence to contain 1000 digits

Pour la résolution de ce problème on passe par changement de base, car on constate en base 2 que:
quand la taille en digit de l'elt est pair en base alors : 
	soit l'elt précédent à aussi la même taille et alors l'elt suivant aura la taille + 1
	soit l'elt précédent à une taille impaire et alors l'elt suivant aura la même taille paire

	Si l'élément actuel a une taille impaire alors l'elt suivant aura une taille paire car taille précédente + 1
	Si l'élément actuel a une taille paire alors il faut se référer au paragraphe ci-dessous
*/
void afficheGrandNombre(int * elt){
	printf("dans afficheGrandNombre\n");
	int i = 0;
	while(elt[i] != '\0'){
		if(elt[i] != '#'){printf("%d", elt[i]);}
		i++;
	}
	printf("\n");
}

void afficheGrandNombre2(table * ptr){
	int * tab = ptr->tab; int taille = ptr->taille;
	printf("taille %d : ", ptr->taille);
	for(int i = 0; i < taille; i++){ printf("%d", tab[i]); }
	printf("\n");
}

void suiteDeFibonacci(int index){
	int * p1 = malloc(sizeof(int)*2);
	int * p2 = malloc(sizeof(int)*2);
	int * result; int * tmp;
	p1[0]=1; p2[0]=1;
	result = p2;

	result = addition_demesurer(p1, result);
	printf("3: "); //afficheGrandNombre(result);
	
	for(int i = 3; i <= index; i++){
		tmp = result;
		result = addition_demesurer(p1, result);
		//afficheGrandNombre(result);
		free(p1);
		p1 = tmp;
	}
}

void suiteDeFibonacci2(int index){
	table * p1 = createStruct(1);
	table * p2 = createStruct(1);
	(p1->tab)[0] = 1;
	(p2->tab)[0] = 1;
	table * result; table * tmp;
	result = p2;

	result = additionLongue(p1, result);
	printf("3: "); afficheGrandNombre2(result);
	
	for(int i = 4; i <= index; i++){
		tmp = result;
		result = additionLongue(p1, result);
		printf("index %d : ", i); afficheGrandNombre2(result);
		free(p1);
		p1 = tmp;
		if(result->taille == 1000) {return; }
	}
}

int main(){
/*	
	int tab[1000000];
	//Initialisation
	for(int i = 0; i < 1000000; i++){ tab[i] = 0;}
	tab[0] = 1; tab[1] = 1; // Les éléments initiaux F1 et F2 valent 1 donc sont composé d'un digit
	tab[2] = 2; tab[3] = 2; // Les éléments 3 et 4 valent 10 et 11, c'est à dire 2 et 3 en base 10
	//, ils sont donc chacun composés de deux digits.

	for(int i = 4; i < 1000000; i++){
		if(tab[i-1] % 2 == 1){ tab[i] = tab[i-1] + 1;}
		if(tab[i-1] % 2 == 0){
			if(tab[i-2] % 2 == 0) {tab[i] = tab[i-1]+1;}
			if(tab[i-2] % 2 != 0) {tab[i] = tab[i-1];}
		}
		if( tab[i] >= 3325){printf("l'élément d'index %d a une taille de %d\n", i+1, tab[i]);}
		if(tab[i] > 3340 ){return 0;}
	}
*/	
	printf("debut de la chaine\n");
	/*
	table * p1 = createStruct(2);
	table * p2 = createStruct(2);
	p1->tab[0] = 9; p1->tab[1] = 2;
	p2->tab[0] = 9; p2->tab[1] = 2;
	afficheGrandNombre2(additionLongue(p1, p2));
	*/
	suiteDeFibonacci2(5000);
	
/*	
	//Fibbo 50 premier
	unsigned long int F1 = 1, F2 = 1; unsigned long int tmp;
	for(int i = 0; i <= 90; i++){ 
		tmp = F1 + F2;
		printf("%d eme terme = %ld\n", i+3, tmp);
		F1 = F2;
		F2 = tmp;
	}
*/
	return 0;
}