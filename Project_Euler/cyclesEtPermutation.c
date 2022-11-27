#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

#define TAILLE 7

int isOnlyIncreasing(int * tab){
    int i;
    for (i = 0; i < TAILLE-1; i++) {
        if(tab[i] > tab[i+1]){return 0;}
    }
    return 1;
}

int profondPivot()

/*On suppose que le tableau est de taille 7, on permute un tableau d'entiers
 *les permutations seront ordonnées pour aller vers l'entier strictement supérieur
 *au vu des entiers en entrée*/
int * permutation(int * tab){ /*1234567 => 1234576*/
    if(isOnlyIncreasing(tab)){
        invert(int * tab, TAILLE-1, TAILLE-2);
        return tab;
    }

}

int main(){
    int test = 1234567, * tb = NULL, *depart = malloc(sizeof(int));
    *depart = 2;
    tb = intToTab(test);     
    printf("La valeur intiale est : %d\n", test);
    while(test < 7654321){
        test = pppPandigital(tb, depart, 7);
        printf("next : %d et depart vaut : %d\n", test, *depart);
        tb = intToTab(test);
    }
    
    return 0;
}

