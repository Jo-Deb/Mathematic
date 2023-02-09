#include <stdio.h>
#include <stdlib.h>
#include "big_operation.h"

int integerSum(unsigned long long int input){
    unsigned long long int oignon = input, tmp;
    int res = 0;
    while(oignon > 0){
        tmp = oignon  % 10;
        res = res + tmp;
        oignon = oignon / 10;
    }
    return res;
}


int main(int argc, char ** argv){
    int idx, i;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &idx) > 0){}
        else{ printf("Mauvais argument, échec\n"); return 1;}
    }
    else{ printf("un argument attendu en entrée, échec\n"); return 1; }

    //unsigned long long int deno = 1, tmp,  num = 1;
    char *deno = NULL, *tmp = NULL,  *num = NULL;
    deno = intToTab(1); num = intToTab(1); 
    if(idx == 1) {
        printf("l'approximation de e à la réduite %d est : 2\n", idx);
        return 0;
    }
    if(idx == 2) {
        printf("l'approximation de e à la réduite %d est : 3\n", idx);
        return 0;
    }
    if(idx % 3 == 0){free(num); num = intToTab(2*(idx/3));}
    for(i=idx-1; i>=1; --i){
        if(tmp != NULL){free(tmp);} tmp = copieTab(num); 
        if(num != NULL){free(num);} num = copieTab(deno); 
        if(num != NULL){free(deno);} deno = copieTab(tmp);
        
        //printf("\ndébut étape %d num = ", i); bigAffiche(num); printf("\n");
        //printf("\ndébut étape %d deno = ", i); bigAffiche(deno); printf("\n");
        //printf("\ndébut étape %d tmp = ", i); bigAffiche(tmp); printf("\n");
        
        if(i==1){ num = bigSomme(bigMultiplication(deno, intToTab(2)), num ); /*num += 2*deno;*/}
        else{
            if(i % 3 == 0){num = bigSomme(bigMultiplication(deno, intToTab(2*(i/3)) ), num);/*num += 2*(i/3)*deno;*/}
            else {num = bigSomme(deno, num);/*num += deno;*/ }
        }
        printf("\nfin étape %d num = ", i); bigAffiche(num); printf("\n");
        printf("\nfin étape %d deno = ", i); bigAffiche(deno); printf("\n");
    }
    printf("l'approximation de e à la réduite %d est : ", idx); bigAffiche(num); printf("/ "); bigAffiche(deno);
    printf("\net la somme des chiffres du numérateur est %d \n", sommePositifChriffe(num));
    return 0;
}
