#include<stdio.h>
#include<stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"
#include "genList.h"

genList * patternMultiple(int val){
    int * valTab = intToTab(val), len = calculTailleEntier(val), i, j;
    genList * res = NULL;

    for(i=0; i<len; i++){
        liste * lst = ajoutEnTete(NULL, valTab[i]);
        lst = ajoutEnQueue(lst, i);
        for(j=i+1; j<len; j++){ if(valTab[j]==valTab[i]){lst = ajoutEnQueue(lst, j);}}
        if(taille(lst) <= 2){supprimeListe(lst);}
        else{ res = g_ajoutEnTete(res, lst);}
    }
    return res;
}


int digitRepeat(int val){
    int * valTab = intToTab(val), i, j;
    int taille = calculTailleEntier(val);
    for(i=0; i<taille; i++){
        for(j=i+1; j<taille; j++){ if(valTab[i]==valTab[j]){return 1;}}
    }
    return 0;
}

void fileOfPrime(){
    FILE * fp = fopen("fileOfPrime.dat", "w");
    int i = 56003, cpt = 0;
    
    while(cpt<1000000){
        ++i;
        if(digitRepeat(i)==1 && isPrime(i)==1){
            fprintf(fp, "%d\n", i);
            ++cpt;
        }
    }
}

liste * travail(liste * m, int primeVal){
    liste * res = NULL;
    int j, * wrk = intToTab(primeVal), valTmp, len = calculTailleEntier(primeVal);
    for(j=0; j<10; j++){
        liste * tmp =m->l;
        valTmp = m->value;
        while(tmp!=NULL){
            wrk[tmp->value]=j;
            tmp=tmp->l;
        }
        valTmp = tabToInt(wrk, len);
        if(isPrime(valTmp)==1){ res=ajoutEnTete(res, valTmp);}
    }
    return res;
}

liste * longestList(genList * motifs, int primeVal){
    int valToReplace;
    genList * tmp = motifs;
    liste * best = NULL; 
    while(tmp != NULL){
        liste *  pcr = tmp->ptr;
        valToReplace = pcr->value;
        liste * actual = travail(pcr, primeVal);
        if(taille(best) < taille(actual)){supprimeListe(best); best = actual;}
        else{supprimeListe(actual);}
        tmp = tmp->suiv;
        supprimeListe(pcr);
    }
    g_supprimeListe(motifs);
    return best;
}

int main(){
    printf("début du calcul des PREMIERS\n");
    fileOfPrime();
    FILE * fp = fopen("fileOfPrime.dat", "r");
    int prime;
    genList * gl = NULL, * gtmp = NULL; 
    liste * lst = NULL;
    printf("début du calcul des listes\n");
    while(fscanf(fp, "%d", &prime) != EOF ){
        gl = patternMultiple(prime);
        gtmp = gl;
        lst = longestList(gl, prime);
        if(lst != NULL && taille(lst) >= 8){afficheListe(lst); printf(": for the primeValue: %d\n", prime);}
    }
    return 0;
}
