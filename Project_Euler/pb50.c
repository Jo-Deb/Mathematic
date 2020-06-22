#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

int main(){
    int tabPrime[1414], i=0, prime, sumPrime = 0, max, j, nb_elt;
    FILE * fp = fopen("base_nbr_premiers.dat", "r");

    while(fscanf(fp, "%d", &prime) != EOF && i < 1414){tabPrime[i] = prime; ++i;}

    for(i = 0; i < 1414; ++i){
        j = i;
        sumPrime = 0;
        while(sumPrime < 1000000 && j < 1414){
            sumPrime += tabPrime[j];
            if(isPrime(sumPrime) == 1){
                if(sumPrime < 1000000){
                    max = sumPrime; nb_elt = j - i + 1;
                    printf("%d premier, somme de %d\n", max, nb_elt);
                }
                if(sumPrime > 1000000){return max;}
            }
            ++j;
        }
        printf("____________________________%d premier, somme de %d____________________________\n", max, nb_elt);
    }
    return max;
}
