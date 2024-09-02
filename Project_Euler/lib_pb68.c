#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

#define LIBERE_LISTE(x) \
    freeListe(x); \
    x = NULL

/*Une petite fonction pour afficher des tableaux d'entier*/
void afficheTableau(int * tab, int ttab){
    int i;
    for(i=0; i < ttab; ++i){printf(" %d ", tab[i]);}
    printf("\n");
}

/*On sait faire la différence entre 2 listes. On fait cette petite fonction pour pouvoir gérer
 * le cas ou la et lb sont des tableaux*/
liste * retire_a_dans_b(int * ta, int tta, int * tb, int ttb){
    liste * la = tab_to_liste(ta, tta), * lb = tab_to_liste(tb, ttb); 
    liste * res = soustrait_a_de_b(la, lb);
    freeListe(la); freeListe(lb);
    return res;
}

/*Ecrire une fonction pour générer les combinaisons d'une taille donnée et pris dans un ensemble
 * dont la taille est donnée. Des combinaisons d'entiers seront calculées et chaque entier pourra
 * être assimilé à un élément de l'ensemble cible.
 * t_comb : la taille de la combinaison
 * t_set : la taille de l'ensemble dans lequel sont pris les éléments*/
liste * computeComb(int t_comb, int t_set){
    int set[t_set], i, tmp, comb[t_comb], compteur = 0, lim = 1, max;
    //On calcule le nombre de combinaison à faire
    for(i=0; i<t_set; ++i){ set[i]=i+1; }
    for(i=0; i<t_comb; ++i){ lim *= set[7-i]; }
    for(i=0; i<t_comb; ++i){ comb[i] = set[i]; }
    liste * liste_diff = retire_a_dans_b(comb, t_comb, set, t_set);
    liste * res = NULL;

    while(compteur < lim){
        max = maxListe(liste_diff);
        res = ajoutEnTete(res, tabToInt(comb, t_comb)); ++compteur;
        while(comb[t_comb - 1] < max){
            comb[t_comb-1] = best_majorant(comb[t_comb-1], liste_diff);
            res = ajoutEnTete(res, tabToInt(comb, t_comb));
            ++compteur;
        }

        i = t_comb - 1;
        while(comb[i] >= max) {
            comb[i]=0; 
            LIBERE_LISTE(liste_diff);
            liste_diff = retire_a_dans_b(comb, t_comb, set, t_set);
            max = maxListe(liste_diff);
            --i;
        }
        comb[i] = best_majorant(comb[i], liste_diff);
        tmp = i;
        for(i=tmp+1; i<t_comb; ++i){ 
            LIBERE_LISTE(liste_diff);
            liste_diff = retire_a_dans_b(comb, t_comb, set, t_set);
            comb[i] = minListe(liste_diff);
        }
    }
    return res;
}

int main(int argc, char ** argv){
    int taille_set, taille_comb, return_scanf = 0;
    if(argc != 3){ 
        printf("lib_pb68.c : mauvais usage. Donner la taille de l'ensemble puis la taille de  la combinaison\n"); 
        return 1;
    }
    return_scanf = sscanf(argv[1], "%d", &taille_set); 
    if(return_scanf <= 0){
        printf("la conversion de l'argument %s a échoué\n", argv[1]);
        return 0;
    }
    return_scanf = sscanf(argv[2], "%d", &taille_comb); 
    if(return_scanf <= 0){ 
        printf("la conversion de l'argument %s a échoué\n", argv[2]); 
        return 0;
    }
    liste * res = computeComb(taille_comb, taille_set);
    afficheListe(res);
    return 0;
}
