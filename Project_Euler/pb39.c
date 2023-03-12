#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int * millecarre(){
	int i;
	int * tab = malloc(1000*sizeof(int));
	for(i=0; i<1000; i++){ tab[i] = (i+1)*(i+1);}
	return tab;
}

int suisJeCarre(int val, int * tab, int start){
	int incr = 1, i;
	for(i=start+1; i<1000; i++){
		if(tab[i] == val){ return i+1;}
	}
	return 0;
	while(incr < val){ 
		if(incr * incr == val){return incr;} 
		++incr;
	}
	return 0;
}

liste * sommeDesCarre(int * tab, int taille){
	liste * lst = NULL; int i, j, res, tmp;
	for(i=0; i<taille; i++){
		for(j=i+1; j<taille && i<taille; j++){
			res = suisJeCarre(tab[i]+tab[j], tab, j);
			if(res > 0 && (tmp = res+(i+1)+(j+1)) <= 1000){ 
				lst = ajoutEnTete(lst, tmp); 
			}
		}
	}
	return lst;
}

int main(){
	int nbr_p = 0, nbr_c = 0, max = 0;
	int * tmp = millecarre();
	liste * lst = sommeDesCarre(tmp, 1000);
	liste * pcr = lst, * pcr2 = pcr;
	while(pcr!=NULL){
		nbr_c = 0; pcr2 = pcr->l;
		++nbr_c;
		while(pcr2 != NULL){
			if(pcr2->value == pcr->value){++nbr_c;}
			pcr2 = pcr2->l;
		}
		if(nbr_c > nbr_p){ max = pcr->value; nbr_p = nbr_c;}
		pcr = pcr->l;
	}
	printf("le nombre p ayant le plus de solution représentant un triangle rectangle est %d\n", max);
	free(tmp);
return EXIT_SUCCESS;
}
