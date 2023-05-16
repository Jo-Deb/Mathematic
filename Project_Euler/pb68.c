#include <stdio.h>
#include <stdlib.h>
#include "genList.h"
#include "fonctionsPratiques.h"

glist * combinaison(int valNode, int somme){
    if(valNode <= 0 || valNode > 10){ printf("Mauvais argument pour la valeur du noeud : %d\n", valNode); return NULL; }
    if(somme >= 27 ){ printf("Mauvais argument pour la somme : %d\n", somme); return NULL; }
    
    int e, i, j; glist * res = NULL;
    for(i = 1; i <= 10; ++i){
        if(valNode + i > somme){ return res; }
        e = i;
        for(j = 1; j <= 10; ++j){
            if(j == e){++j;}
            if(valNode + e + j > somme){break;}
            if(valNode + e + j == somme){ 
                char ** tab = malloc(sizeof(char *) * 3);
                tab[0] = intToString(valNode), tab[1] = intToString(e), tab[2] = intToString(j);
                res = g_ajoutTete(res, (void *)concatString(tab, 3), NULL);
            }
        }
    }
    return res;
}

void showElt(void * pt){ printf(" %s ", (char*)pt); }

int main(){
    int i, j;
    for(i = 13; i < 27; ++i){
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        printf("Éléments de combinaison pour la somme %d\n", i);
        for(j = 1; j <= 10; ++j){
            printf("Les combinaisons possibles pour %d contenant %d : ", i, j);
            //afficheListe(combinaison(j, i));
            g_afficheList(combinaison(j, i), showElt);
            printf("\n");
        } 
        printf("=======================================================================================\n");
    }
    return 0;
}
