#include<stdio.h>
#include<stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"
/* génération des combinaisons ok */

liste * combinaisonDe2(int * tab, int taille){
    int i, j;
    liste * lst = NULL;
    for(i=0; i<=taille-2; i++){
        for(j=i+1; j<taille; j++){
            lst = ajoutEnTete(lst, tab[i]*10+tab[j]);
        }
    }
    return lst;
}


liste * combinaison(int * tab, liste * combi, int len, int comb){
    if(comb == 2){return combinaisonDe2(tab, len);}
    int max, i;
    if(combi == NULL){for(i=0; i<6; i++){ combi = ajoutEnTete(combi, i+1);} }
    
    //On suppose qu'*il y a de la cohérence dans les variables.
    liste * res = NULL, *pcr = combi;
    if(calculTailleEntier(pcr->value) == comb){return combi;}
    while(pcr!=NULL){
        max = pcr->value % 10;
        for(i=max; i<len; i++){
            res = ajoutEnTete(res, 10*pcr->value+tab[i]);
        }
        pcr=pcr->l;
    }
    supprimeListe(combi);
    return combinaison(tab, res, len, comb);
}


liste ** genCombinaison(int tab[]){
    liste ** res = malloc(5*sizeof(liste*)), * wrk;
    int i;
    for(i=0; i<5; i++){ 
        if(i==0) {res[i] = combinaison(tab, NULL, 6, i+1);}
        else{
            wrk = recopie(res[i-1]);
            res[i] = combinaison(tab, wrk, 6, i+1);
        }
    }
    return res;
}


int substitution51(int val, int combi, int replacementValue){
    int res, combiLen = calculTailleEntier(combi), valLen = calculTailleEntier(val);
    int * combinaison = intToTab(combi), * valTab = intToTab(val);
    /*On s'assure que ne contient pas les bornes, c-à-d le 1er digit et le 
     * le dernier digit */
    if(combinaison[0] == 1 || combinaison[combiLen-1] >= valLen){
        return -1;
    }
    for(res=0; res<combiLen; res++){valTab[combinaison[res]-1] = replacementValue;}
    res = tabToInt(valTab, valLen);
    return res;
}


liste * longestList(liste ** genCombi, int primeVal, int l_genCombi){
    liste * max = NULL, * wrk = NULL, * pcr = NULL;
    int i, j, tmp;

    for(i=0; i<l_genCombi; i++){
        pcr = genCombi[i];
        while(pcr != NULL){
            for(j = 0; j<10; j++){
                tmp = substitution51(primeVal, pcr->value, j);
                if(tmp > 0 && isPrime(tmp) == 1){wrk = ajoutEnTete(wrk, tmp);}
            }
            if(taille(max) < taille(wrk)){supprimeListe(max); max=wrk;}
            else{ supprimeListe(wrk); }
            wrk = NULL;
            pcr = pcr->l;
        }
    }
    return max;
}


int main(){
    int tab[6] = {1, 2, 3, 4, 5, 6}, tmp, val, i=0, j;
    int primeVal[100000];
    liste ** combiLists = genCombinaison(tab);
    //affichage des combinaison obtenues
    for(i=0; i<5; i++){
        printf("Combinaison de %d : ", i+1);
        afficheListe(combiLists[i]);
        printf("\n");
    }
    //faire un tableau de nombres premiers
    FILE * fp = fopen("base_nbr_premiers.dat", "r");
    i = 0;
    liste * wrk = NULL;
    while(fscanf(fp, "%d", &tmp) != EOF && i<100000){
        if(tmp >= 56003){primeVal[i]=tmp; ++i;}
    }
    //On lance les substitutions pour la liste des premiers calculés
    liste * wrk = NULL;
    for(i=0; i<100000; i++){
        wrk = longestList(combiLists, primeVal[i], 5);
        if(taille(wrk) >= 8){
            printf("la plus grande liste pour %d: ", primeVal[i]);
            afficheListe(wrk); printf("\n");
        }
        supprimeListe(wrk);
    }
    fclose(fp);
    for(i=0; i<5; i++){supprimeListe(combiLists[i]);}
    return 0;
}
