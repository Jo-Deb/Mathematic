#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fonctionsPratiques.h"
#include "liste.h"

liste * primeFactors(int val, int * top){
    liste * lst = NULL;
    int quotien=val, i=0;
    while(quotien != 1 && i < 10000){
        if(quotien % top[i] == 0){
            while(quotien % top[i] == 0){quotien = quotien / top[i];}
            lst = ajoutEnTete(lst, top[i]);
        }
        ++i;
        if(i==9999){printf("i a atteint 9999\n");}
    }
    return lst;
}


int main(){
    int incr = 647, ts=0;
    int tab[4];
    int * top = generatePrimes();
    liste * l = NULL;
    while(ts<4){
        if(isPrime(incr)>0){++incr; ts=0;}
        l = primeFactors(incr, top);
        if(taille(l) == 4){tab[ts] = incr; ++ts;}
        else{ts = 0;}
        free(l); l = NULL;
        ++incr;
    }
    printf("la boucle a fini, voici les 4 nombres obtenus:\n");
    for(incr=0; incr<4; ++incr){printf("%d\n", tab[incr]);}
    return EXIT_SUCCESS;
}
