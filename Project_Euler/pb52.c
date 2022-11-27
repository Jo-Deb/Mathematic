#include<stdio.h>
#include<stdlib.h>
#include "fonctionsPratiques.h"

int minValFromDigit(int val){
    int * wrk = intToTab(val), taille = calculTailleEntier(val);
    triTab(wrk, taille);
    return tabToInt(wrk, taille);
}


int pb52(int val){
    int i = 2, tmp = minValFromDigit(val);
    for(i=2; i<7; i++){
        if(minValFromDigit(val*i)!=tmp){return i-1;}
    }
    return i;
}

int main(){
    int depart = 25, res = 0;
    while(res!= 6){
        res = pb52(depart);
        if(res >=3){printf("pour %d res = %d\n", depart, res);}
        ++depart;
    }
    return 0;
}
