#include <stdio.h>
#include <stdlib.h>
#include "big_operation.h"
#include "genList.h"

int tabPrime[148934];

/*
 * Extraire les nombres premiers et les mettre dans
 * le tableau tabPrime
 * */
void primeExtract(){
    int i = 0, tmp=0;
    FILE * fd = fopen("base_nbr_premiers.dat", "r");
    
    while(fscanf(fd, "%d", &tmp)!=EOF && i < 148934){tabPrime[i]=tmp; ++i;}
}

/*
 * Déterminer la liste des facteurs premiers pour un nombre donné.
 * Le nombre donné est représenté par une chaine de caractères.
 * */
glist * facteurPremier(char * nbr){
    int i = 0, puissance = 0;
    char * tmp = NULL;
    glist * res = NULL;

    while(i < 148934 && plusGrand(nbr, intToTab(i*i))==nbr){
        tmp = intToTab(i);
        if(estDivisible(nbr, tmp)==1){ puissance = determinePuissance(nbr, tmp); }
        if(puissance % 3 != 0){
            if(tmp!=NULL){free(tmp);}
            if(res!=NULL){g_freeList(res);}
            return NULL;
        }
        else{
            int * tab = malloc(2*sizeof(int));
            tab[0]=i; tab[1]=puissance;
            res = g_ajoutTete(res, (void *)tab, NULL);
        }
        free(tmp);
        ++i;
    }
    return res;
}

/*Génerer le tableau avec les valeurs cubiques
 * on débute à 345 */
char **  tableauDoublon(int lon){
    int i = 0, depart = 345;
    char ** res = malloc(lon * sizeof(char *)), * tmp = NULL;

    for(i=0; i < lon; ++i){
        tmp = intToTab(depart + i);
        tmp = power(tmp, 3);
        triTab(tmp); 
        res[i] = tmp;
    }
    return res;
}

/*Trier le tableau de doublon pour être en mesure
 *de comptabiliser le nbr de doublon de chaque valeur
 */
void trierDoublon(char ** tab, int lon){
    char * tmp = NULL;
    int i=0, j=0;
    for(i=0; i < lon-1; ++i){
        for(j=i+1; j < lon; ++j){
            if(plusGrand(tab[i], tab[j])==tab[i]){
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

void analyseTab(char ** tab, int lon){
    int cpt = 0, i, index = 0;

    for(i=0; i<lon; ++i){
        if(egalite(tab[index], tab[i])==1){++cpt;}
        else{
            bigAffiche(tab[index]); printf(" : %d occurences\n", cpt);
            index = i, cpt=1;
        }
    }
}

void printList(char * nb, glist * fac){
    int * tab = NULL;
    glist * tmp = fac;
    bigAffiche(nb);

    while(tmp != NULL){
        tab = (int *) tmp->elt;
        if(tmp->next !=NULL){printf("power(%d, %d) * ", tab[0], tab[1]);}
        else{printf("power(%d, %d)\n", tab[0], tab[1]);}
        tmp = tmp->next;
    }
}

glist * getCubicString(char ** tab, int lon){
    int i, cpt = 0, index = 0;
    glist * res = NULL;

    for(i=0; i<lon; ++i){
        if(egalite(tab[index], tab[i])==1){++cpt;}
        else{
            if(cpt > 3){ 
                res = g_ajoutTete(res, (void *)tab[index], NULL); 
//                bigAffiche(tab[index]); printf(" : %d occurences\n", cpt);
            }
            index = i; cpt = 1;
        }
    }
    return res;
}

void getCubicPermutation(char * nb){
    /*On suppose que plusieurs permutations de nb sont cubiques*/
    glist * tmp = NULL;
    char * max = plusGrandeValeur(nb);

    while(egalite(nb, max)==0){
        permuteValeurSuperieur(nb, max);
        bigAffiche(nb); printf("\n");
        if((tmp=facteurPremier(nb)) == NULL){ printList(nb, tmp);}
    }
    printf("=================================\n");
}

int main(){
    primeExtract();
    int lon = 10000, i;
    char ** oTab = tableauDoublon(lon), *tmp=NULL, *snap=NULL, ** dTab = tableauDoublon(lon);

    trierDoublon(dTab, lon);
    //analyseTab(dTab, lon);
    glist * lst_nb = getCubicString(dTab, lon);
    while(lst_nb != NULL){
        tmp = (char *)(lst_nb->elt);
        for(i=0; i<lon; ++i){
            if(egalite(tmp, oTab[i])==1){
                snap = power(intToTab(i+345), 3);
                printf("%d est une permutation cubique de : ", i+345); bigAffiche(tmp);
                printf(" Et power(%d, 3) = ", i+345); bigAffiche(snap); printf("\n");
                free(snap);
            }
        }
        lst_nb = lst_nb->next;
        printf("===================================\n");
    }
    return 0;
}
