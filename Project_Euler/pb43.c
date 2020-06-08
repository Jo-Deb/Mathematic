#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

int * nextPermutation(int * tab, int * depart, int taille){
    int posMin = getPositionMin(tab, *depart, taille);
    if(posMin==(taille-1)) {
        invert(tab, posMin, taille-2);
        if((taille - *depart)==2){--(*depart);}
        return tab;
    }
    if((taille - *depart )==2){
        triSousTab(tab, taille, *depart);
        --(*depart);
        return tab;
    }
    int posPivot = positionPivot(tab, *depart, taille);
    int pgni = positionPgnf(tab, posPivot, taille); 
    if(pgni==-1){--(*depart); return nextPermutation(tab, depart, taille);}
    else{
        invert(tab, posPivot-1, pgni);
        inverseTriSousTab(tab, taille, posPivot);
        *depart = posPivot;
        return tab;
    }
}

unsigned long convertTabToInt(int * tab, int taille){
    unsigned long res = 0; 
    int i;
    for(i=0; i<taille; i++){res = res*10 + tab[i];}
    return res;
}

int testProperties(int * tab){
    int i, tmp = 0;
    for(i=1; i<=3; i++){tmp=tmp*10+tab[i];}
    if(tmp % 2!=0){return 0;} tmp=0;
    for(i=2; i<=4; i++){tmp=tmp*10+tab[i];}
    if(tmp % 3!=0){return 0;} tmp=0;
    for(i=3; i<=5; i++){tmp=tmp*10+tab[i];}
    if(tmp % 5!=0){return 0;} tmp=0;
    for(i=4; i<=6; i++){tmp=tmp*10+tab[i];}
    if(tmp % 7!=0){return 0;} tmp=0;
    for(i=5; i<=7; i++){tmp=tmp*10+tab[i];}
    if(tmp % 11!=0){return 0;} tmp=0;
    for(i=6; i<=8; i++){tmp=tmp*10+tab[i];}
    if(tmp % 13!=0){return 0;} tmp=0;
    for(i=7; i<=9; i++){tmp=tmp*10+tab[i];}
    if(tmp % 17!=0){return 0;} tmp=0;
    return 1;
}

int main(){
    unsigned long int res = 9786543210, sum = 0;
    int depart = 0, i, taille = 10;
    int * tab = malloc(10 * sizeof(int));   
    for(i=0; i<=9; i++){tab[i]=9-i;}
    while(res > 123456789){
        res = convertTabToInt(nextPermutation(tab, &depart, taille),taille);
        if(testProperties(tab)==1){
            printf("%ld respecte les propriétés.\n",res);
            sum += res;
        }
    }
    printf("la somme totale vaut: %ld\n", sum);
    return EXIT_SUCCESS;
}
