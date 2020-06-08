#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"
#include <limits.h>

int * intToTab10(int  val){
    int taille = calculTailleEntier(val);
    int * tmp = intToTab(val);
    int * res = malloc(10 * sizeof(int));
    int i, tp = 1;
    for(i=0; i<=9; i++){res[i] = 0;}
    for(i=9; i>=0; i--){
        if(taille - tp < 0){res[i]=0;}
        else{res[i] = tmp[taille-tp];}
        ++tp;
    }
    return res;
}

int * addition10(int * tab1, int * tab2){
    int i, ret=0, tmp;
    int * res = malloc(10*sizeof(int));
    for(i=9; i>=0; i--){
        tmp = tab1[i] + tab2[i] + ret;
        res[i] = tmp % 10;
        ret = tmp / 10;
    }
    free(tab1);
    free(tab2);
    return res;
}

int * multiplication(int * tab, int puis){
    if(puis == 1){return tab;}
    int i, ret, j, tmp;
    for(i=1; i<puis; i++){
        ret = 0;
        for(j=9; j>=0; j--){
            tmp = tab[j] * puis + ret;
            tab[j] = tmp % 10;
            ret = tmp / 10;
        }
    }
    return tab;
}

/*
unsigned long dixDernier(int val){
    unsigned long res = val;
    int i, *tab, tll;
    if(val == 1) {return res;}

    for(i=1; i<val; ++i){
        res *= res;
        if((tll=calculTailleEntier(res)) > 10){
           tab = l_intToTab(res);
           res = l_sousTabtoInt(tab, tll-10, tll); 
        }
    }
}
*/

int main(){
    printf("The maximum value of INT = %d\n", INT_MAX);
    int val, i, *tab1, *tab2;
    int nt, sum=0;
    tab2 = intToTab10(sum);

    for(val=1; val<=1000; val++){
        if(val%10 == 0 && val>10){++val;}
        nt = val;
        printf("nt vaut: %d ", nt);
        tab1 = intToTab10(nt);
        printf("avant multiplication: ");
        for(i=0; i<10; i++){printf("%d ", tab1[i]);}
        tab1 = multiplication(tab1, val);
        printf("\naprès multiplication: ");
        for(i=0; i<10; i++){printf("%d ", tab1[i]);}
        tab2 = addition10(tab1, tab2);
        printf("\n somme de tab1 et tab2 ");
        for(i=0; i<10; i++){printf("%d ", tab2[i]);}
        printf("\n");
    }
    printf("le résultat final est %d\n", tabToInt(tab2, 10));
    return EXIT_SUCCESS;
}
