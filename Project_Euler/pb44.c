#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"
#include <math.h>

int racineEntiere(int val){
    int ind=1, carre=0;
    while((carre=(ind*ind)) <= val){
        if(carre == val){return ind;}
        ++ind;
    }
    return 0;
}

int racine(int val){
    double root = sqrt(val);
    int result;
    if(round(root)==root){result = root; return result;}
    else{return 0;}
}

int isPentagon(int val){
    //int deltaRacine = racineEntiere(24*val+1);
    int deltaRacine = racine(24*val+1);
    if(deltaRacine > 0){
        if((1+deltaRacine)%6==0){return 1;}
    }
    return 0;
}

int main(){
    int lim=0, maxPos=0, cpt=1, distance, max=0, testAddition=0, testSoustraction=0;
    liste * l = NULL, * pcr = NULL;
    while(cpt < 3000){
        l = ajoutEnQueue(l, cpt*(3*cpt-1)/2);
        ++cpt;
    }
    liste * tmp = l;
    while(tmp!=NULL){
        pcr = l;
        while(pcr != tmp){
            testAddition = isPentagon(tmp->value + pcr->value);
            testSoustraction = isPentagon(tmp->value - pcr->value);
           // if(testAddition > 0) {printf("on a deux valeurs pour l'addition, %d, %d\n",tmp->value, pcr->value); }
           // if(testSoustraction > 0) {printf("on a deux valeurs pour la soustraction, %d, %d\n",tmp->value, pcr->value); }
            if(testAddition > 0 && testSoustraction > 0){
                distance = tmp->value - pcr->value;
                printf("On a un couple qui respecte les conditions: %d et %d et la distance est : %d\n"\
                        , tmp->value, pcr->value, distance);
            }
            pcr = pcr->l;
        }
        tmp = tmp->l;
    }
    return 0;
    
    l = ajoutEnQueue(l, 1); l = ajoutEnQueue(l, 5);
    lim = maxListe(l); max = lim;
    maxPos = getPosition(l, lim); cpt = maxPos; distance=0;

    while(lim > 3 * (cpt-1) + 1 ){
        pcr = l;
        while(pcr->l != NULL){
            if(isPentagon(max + pcr->value) > 0 && isPentagon(max - pcr->value) > 0){
                distance = max - pcr->value;
                lim = distance;
                printf("On a un couple positif: %d et %d et la distance est : %d\n"\
                        , getPosition(l, max), getPosition(l, pcr->value), distance);
            }
            pcr = pcr->l;
        }
        ++cpt;
        max=cpt*(3*cpt-1)/2;
        l = ajoutEnQueue(l, max);
        if(distance != lim){lim = max;}
    }
}
