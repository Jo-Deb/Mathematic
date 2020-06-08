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
//		if(taille - *depart == 2){ *depart = 0;}
		if(taille - *depart == 2){ --(*depart);}
		return tabToInt(tab, taille);
	}
	if((taille - *depart)==2){
		triSousTab(tab, taille, *depart); 
//		*depart = 0;
		--(*depart);
		return tabToInt(tab, taille);
	}
	int posPivot = positionPivot(tab, *depart, taille);
//	printf("positionPivot:%d\t",posPivot);
	int posPgnf = positionPgnf(tab, posPivot, taille);
//	printf("posPgnf:%d\t",posPgnf);
//	if(posPgnf==-1){ ++(*depart); return pppPandigital(tab, depart, taille);}
	if(posPgnf==-1){ --(*depart); return pppPandigital(tab, depart, taille);}
	invert(tab, posPivot-1, posPgnf);
	inverseTriSousTab(tab, taille, posPivot);
	*depart = posPivot;
	return tabToInt(tab,taille);
}

int run_se(int val){
    printf("début des tests pour les nombres pandigitaux déduits de %d\n", val);
    int taille = calculTailleEntier(val), i, lim=1, dcp=1, res=val;
    int * tab = intToTab(val), depart=0;
    for(i=1; i<=taille; i++){lim *= i;}
    
    while(dcp <= lim){
        if(pandigitalPrime(res)==1){free(tab); printf("%d est premier\n", res); return 1;}
        res = pppPandigital(tab, &depart, taille);
        ++dcp;
    }
    free(tab);
    return 0;
}

int main(){
	int test=52314, * tb = intToTab(test), dp=0, j, tmp=0, res = 0, k;
	pppPandigital(tb, &dp, 5); 
	int i=987654321;
	int dcpt = 0, taille=calculTailleEntier(i), depart=0;
	int * tab = intToTab(i);
/*	
	while(dcpt < 362879){
		i = pppPandigital(tab, &depart, taille);
		printf("%d\t depart: %d\n",i, depart);
		++dcpt;
	}
*/
    for(j=9; j>=4; j--){
        for(k=(taille-j); k+j<=taille; k++){
            free(tab);
            tab = intToTab(i);
            res = sousTabtoInt(tab, k, taille);
            if(run_se(res)==1){ free(tab); return EXIT_SUCCESS;}
        }
    }
    /*
	while(i>=123456789){
			i = pppPandigital(tab, &depart, 9);
	//	printf("scan de %d\n", i);
		if(pandigitalPrime(i)==1){
			printf("le nombre pandigital premier le plus grand est : %d\n", i);
			return EXIT_SUCCESS;
		}
	//	--i;
	} 
    */
	return EXIT_SUCCESS;
}
