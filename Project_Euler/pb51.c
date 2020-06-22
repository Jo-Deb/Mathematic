#include<stdio.h>
#include<stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"

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
    //On suppose qu'il y a de la cohérence dans les variables.
    liste * res = NULL, *pcr = combi;
    if(calculTailleEntier(pcr->value) == comb){return combi;}
    int max, i;
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

int main(){
    int tab[6] = {1, 2, 3, 4, 5, 6};
    liste * lst = combinaisonDe2(tab, 6);
    printf("Voici les combinaisions de 2 pour {1, 2, 3, 4, 5, 6}:");
    afficheListe(lst);
    printf("\n");

    lst = combinaison(tab, lst, 6, 3);
    printf("Voici les combinaisions de 3 pour {1, 2, 3, 4, 5, 6}:");
    afficheListe(lst);
    printf("\n");
    
    lst = combinaison(tab, lst, 6, 4);
    printf("Voici les combinaisions de 4 pour {1, 2, 3, 4, 5, 6}:");
    afficheListe(lst);
    printf("\n");
    
    lst = combinaison(tab, lst, 6, 5);
    printf("Voici les combinaisions de 5 pour {1, 2, 3, 4, 5, 6}:");
    afficheListe(lst);
    printf("\n");

    return 0;
}
