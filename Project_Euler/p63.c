#include <stdio.h>
#include <stdlib.h>
#include "big_operation.h"

int tailleEntier(int n){
    int len = 0, tmp = n;
    while(tmp > 0){
        tmp = tmp / 10; ++len;
    }
    return len;
}

int main(){
    int depart = 10, i, j, k, lon;
    char * tmp = NULL;

    for(i=2; i<=9; ++i){
        for(j=2; j<100; ++j){
            tmp = intToTab(i);
            tmp = power(tmp, j);
            lon = tailleChaine(tmp);
            if(lon == j){
                ++depart;
                printf("%d a la puissance %d = ", i, j); bigAffiche(tmp);
                printf(" et a %d chiffres\n", lon);
            }
        }
    }
    printf("depart = %d\n", depart);
    return 0;
}
