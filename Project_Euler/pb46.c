#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctionsPratiques.h"

int racine(int val){
    double root = sqrt(val);
    int result;
    if(round(root)==root){result = root; return result;}
    else{return 0;}
}

int * nombresPremiers(){
    int * tab = malloc(10000 * sizeof(int));
    int i=2, tmp=5;
    tab[0] = 2; tab[1]=3;
    while(i<10000){
        if(isPrime(tmp)==1){tab[i]=tmp; ++i;}
        tmp += 2;
    }
    return tab;
}

int main(){
    int i, val=35, test = 1, sol = 0, root;
    val = 35;
    int * tab = nombresPremiers();
    while(test == 1){
        if(isPrime(val)==1){val += 2;}
        i = 0; sol = 0; root = 0;
        while(tab[i] < val && sol == 0){
            if((val-tab[i])%2 == 0){
                root = racine((val-tab[i])/2);
                if(root > 0){
                    sol = 1;
                    printf("%d = 2*%d+%d = %d\n", val, root*root, tab[i], 2*root*root+tab[i]);
                }
            }
            ++i;
        }
        if(sol == 0){
            test = 0;
            printf("la valeur %d ne s'écrit pas comme la somme d'un premier et 2* un carré\n", val);
            return EXIT_SUCCESS;
        }
        val += 2;
    }
    return EXIT_SUCCESS;
}
