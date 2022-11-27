#include <stdio.h>
#include <stdlib.h>
#include "big_operation.h"

typedef struct Fraction Fraction;
struct Fraction{
    char * num;
    char * deno;
};

Fraction * nextFraction(Fraction * prev){
    Fraction * res = malloc(sizeof(Fraction));
    //res.num = prev.num + 2*prev.deno;
    //res.deno = prev.num + prev.deno;
  //  printf("le dénominateur vaut : "); bigAffiche(prev->deno); printf("\n");
    char * tmp = bigMultiplication(prev->deno, intToTab(2));
  //  printf("le résultat de la multiplication est : "); bigAffiche(tmp); printf("\n");
  //  printf("le numérateur avant la somme vaut : "); bigAffiche(prev->num); printf("\n");
    res->num = bigSomme(prev->num, tmp); 
  //  printf("le résultat de la somme est : "); bigAffiche(res->num); printf("\n");
    res->deno =bigSomme(prev->num, prev->deno);
    return res;
}

void afficheFraction(Fraction res){
    //printf("%d/%d ", res.num, res.deno);
    bigAffiche(res.num); printf(" / "); bigAffiche(res.deno); printf(" ");
}

int calculTaille(char * a){
    int i, cpt=0;
    for(i=999; i>=0; i--){
        if(a[i]!='a' && a[i]!='-'){ ++cpt; }
    }
    return cpt;
}

int main(){
    //char * a = intToTab(1393);
    //char * b = intToTab(985);
    //char * b = bigMultiplication(intToTab(5), intToTab(2));
    //bigAffiche(bigSomme(intToTab(7), bigMultiplication(intToTab(5), intToTab(2)))); printf("\n");
    //bigAffiche(bigSomme(a, b)); printf("\n");
     
    int cpt = 0, i, max=0, tnum, tdenum;
    Fraction * first = malloc(sizeof(Fraction)); 
    first->num = intToTab(3); 
    first->deno= intToTab(2);
    Fraction * next = first;
    for(i=2; i<=1000; i++){
        next = nextFraction(next);
        tnum=calculTaille(next->num); 
        tdenum=calculTaille(next->deno);
        afficheFraction(*next); printf(" num:%d, deno:%d\n", tnum, tdenum);
        if(tnum > tdenum ){cpt++; afficheFraction(*next); printf("\n");} 
        if(tnum > max){ max=tnum; }
        if(tdenum > max){ max=tdenum; }
    }
    printf("au total, il y a %d fractions où la longueur du numérateur > longueur dénominateur\n", cpt);
    printf("la longueur maximum enregistrer est : %d\n", max);
    free(next->num); 
    free(next->deno); 
    free(next); 
    
    return 0;
}
