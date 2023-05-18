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

/*
 * A chaque ajout d'un élément on revérifie toutes les conditions, si les conditions sont
 * valides on continue, sinon on arrête et on passe à l'élément suivant
 * FAIRE UNE FONCTION QUI CALCULE LA LISTE DES NOEUDS EXTERNES ET INTERNES ET QUI ENVOIE NULL 
 * QUAND UNE CONDITION N'EST PAS RESPECTÉE.
 * On prend une somme N de nos branches, puis en partant de 10, on prend un élément contenant
 * 10 et dont la somme est égale à N, on prend un élément contenant 9 et dont la somme est 
 * égale à N et on vérifie les conditions qui sont : 
 * 1 - chaque nombre doit avoir au moins une itération et au plus 2
 *    + les nombres avec 1 itération sont les noeuds externes
 *    + les nombres avec 2 itérations sont les noeuds internes dessinant la figure centrale, 
 *      dans notre cas un pentagone
 *
 * 2 - un noeud interne est relié à un noeud externe et un noeud interne, aucune autre 
 *     combinaison n'est valable
 * 3 - Il y a 10 noeuds, on doit donc avoir 5 noeuds externes et 5 noeuds internes à la fin
 * 4 - réécriture des combinaisons*/


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
