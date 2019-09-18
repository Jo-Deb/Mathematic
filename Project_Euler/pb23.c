#include <stdio.h>
#include <math.h>

//tableau des nombres abondants:

int tab[5000];

int crible(int parm1){
	int mol = (int) floor(sqrt(parm1 * 1.0)); //ceil(sqrt(parm1 * 1.0));
	int sd = 1; int quotien;
	//printf("calcul des diviseurs pour %d: ", parm1);
	for (int i = 2; i <= mol; i++){
		if((parm1 % i ) == 0){ quotien = parm1 / i;
			if(i != quotien && i!= parm1){ sd += i + quotien; /*printf("%d, %d, ", i, quotien);*/}
			else{ sd += i; /*printf(", %d", i);*/}
		}
	}
	//printf("\n la somme des diviseurs donne : %d\n", sd);
	return sd;
}

int combinaison_abondante(int parm1){
	int j = 0; int limite = parm1/2 + 1; int elt;
	for(j = 0; tab[j] <= limite; j++){
		elt = parm1 - tab[j];
		if(crible(elt) > elt){ 
			//printf("%d + %d = %d\n", elt, tab[j], parm1 );
			return 1;
		}
	}
	//printf("pas de combinaison pour %d\n", parm1);
	return 0;
}

int main(){
	int i = 12;
	int j = 0;
	int somme = (23 * 24)/2;
	for(int i = 12; j < 5000; i++){
		if(crible(i) > i) { 
			//printf("%d est un nombre abondant \n", i);
			tab[j] = i; j++;
		}
	}

	for(i = 25; i < 28122; i++){ if(combinaison_abondante(i) == 0) { somme += i;} }
	printf("le total des nombres qui ne sont pas somme de deux nombres abondants est : %d\n", somme);
	return 0;
}
