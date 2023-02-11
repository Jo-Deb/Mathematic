#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

unsigned long int CARRE[100000], PREMIER[50000];

void fillCarre(){
    printf("début de fillCarre\n");
    int i;
    for(i=0; i<100000; ++i){ CARRE[i]=(i+1)*(i+1); }
    printf("fin de fillCarre\n");
}

void fillPremier(){
   int i = 0, tmp = 0;
   FILE * fd = fopen("base_nbr_premiers.dat", "r");
   while(fscanf(fd, "%d", &tmp)!=EOF && i < 50000){PREMIER[i]=tmp; ++i;}
}

liste * facteurPremier(int a){
    liste * res = NULL;
    int i;
    for(i=0; (PREMIER[i]*PREMIER[i]) <= a; ++i){
        if( a % PREMIER[i] == 0 ){ res = ajoutEnTete(res, PREMIER[i]); }
    }
    return res;
}

//retourne a s'il est carré parmis les 100000 premiers carrés
long int estCarre(long int a){
    printf("calcul pour %ld\n", a);
    long int prec = 0, next = 99999, tmp, old_prec, old_next;
    while(next - prec > 1){
        while(CARRE[prec] < a && CARRE[next] > a && next - prec > 1){ 
            old_prec = prec, old_next = next;
            next -= (next - prec)/2; prec +=(next - prec)/2;
            printf("boucle while: prec = %ld et next = %ld, CARRE[prec] = %lu, CARRE[next] = %lu\n", prec, next, CARRE[prec], CARRE[next]);
        }
        if(CARRE[prec] > a && CARRE[next] > a){
            next = prec; prec = old_prec;
            printf("1er if: prec = %ld et next = %ld\n", prec, next);
        }
        if(CARRE[prec] < a && CARRE[next] < a){
            //tmp = next; next += (next - prec)/2; prec = tmp;
            next = old_next;
            printf("2ème if: prec = %ld et next = %ld\n", prec, next);
        }
        if(CARRE[prec] == a || CARRE[next] == a){ return a; }
    }
    return 0;
}

int main(){
    fillCarre();
    long int i;
    //for(i=0; i <= 99999; ++i){printf("CARRE[%ld] = %ld\n", i, CARRE[i]);}
    char o[20] = "n'est pas un carré", n[13] = "est un carré";
    for(i = 1; i<10000; ++i){
        printf(" %ld %ld\n", i, estCarre(i));
    }
    return 0;
}
