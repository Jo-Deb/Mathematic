#include <stdio.h>
#include "liste.h"

int division(int num, int den){
	int i = 0; int reste = 1; short decimal = 0; short quotien;
	liste * l = NULL; int taille;
	if(num < den) {num = 10 * num; printf("0,"); decimal = 1;}

	while( reste != 0 ){
		if(num < den ){ 
			if(decimal == 0) {printf(","); decimal = 1; num = num * 10;}
			else{ 
				printf("0"); 
				num *= 10; 
				l = ajoutEnQueue(l, 0);
			}
		}
		else{
			reste = num % den; quotien = num / den;
			printf("%d", quotien);
			if(reste != 0 && decimal == 1){ 
				printf("dans la boucle de contrôle de liste\n");
				num = reste * 10;
				l = ajoutEnQueue(l, quotien);
				afficheListe(l);
				taille = detectionDeCycle(l, quotien);
				if( taille > 1) { 
					printf(" cycle = "); 
					afficheCycle(l, quotien, taille);
					printf(" taille = %d\n", taille-1);
					printf("\n"); return taille;
				}
			}
			if(reste != 0 && decimal == 0){ printf(","); decimal = 1; num = reste * 10;}
			if(reste == 0){ printf("\n"); return 0;}
		}
		i++;
	}
	printf("\n");
	return 0;
}


int main(int argc, char * argv[]){
	int num, den; int limit = 1000;
	int tab[1000]; int max = 0; int oldVal = 0; int newVal = 0; int tmp = 0;
	//Boucle de calcul
	for(int i = 0; i < 1000; i++){
		newVal = division(1, i+1);
		if(newVal > oldVal){ max = i + 1; }
		oldVal = newVal;
	}
	printf("__________________________________________________\n");
	printf("the max value is %d because 1/%d is : \n", max, max);
	division(1, max);
	/*
	//recupération des valeurs
	if( sscanf(argv[1], "%d", &num ) == EOF){ printf("echec lors de la lecture du numérateur\n"); return 1;}
	if( sscanf(argv[2], "%d", &den ) == EOF){ printf("echec lors de la lecture du dénominateur\n"); return 1;}
	
	printf("%d / %d = ", num, den);
	division(num, den);
	*/
	return 0;
}