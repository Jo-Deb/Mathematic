#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

/*Ecrire une fonction pour générer les combinaisons d'une taille donnée et pris dans un ensemble
 * dont la taille est donnée. Des combinaisons d'entiers seront calculées et chaque entier pourra
 * être assimilé à un élément de l'ensemble cible.
 * t_comb : la taille de la combinaison
 * t_set : la taille de l'ensemble dans lequel sont pris les éléments*/
liste * computeComb(int t_comb, int t_set){
    int set[t_set], i, tmp, comb[t_comb], compteur = 0, lim = 1, max;
    //On calcule le nombre de combinaison à faire
    for(i=t_set; i>t_comb; --i){ lim *= i; }
    for(i=0; i<t_set; ++i){ set[i]=i+1; }
    for(i=0; i<t_comb; ++i){ comb[i] = set[i]; }
    liste * lc = tab_to_liste(comb, t_comb), * ls = tab_to_liste(set, t_set);
    liste * res = NULL, * liste_diff = soustrait_a_de_b(lc, ls);
    freeListe(lc); freeListe(ls);
    lc = NULL, ls = NULL;

    while(compteur < lim){
        max = maxListe(liste_diff);
        res = ajoutEnTete(res, tabToInt(comb, t_comb)); ++compteur;
        while(comb[t_comb - 1] < max){
            comb[t_comb-1] = best_majorant(comb[t_comb-1], liste_diff);
            res = ajoutEnTete(res, tabToInt(comb, t_comb));
            ++compteur;
        }
        i = t_comb - 1;
        lc = tab_to_liste(comb, t_comb); ls = tab_to_liste(set, t_set); 
        freeListe(liste_diff); liste_diff = NULL;
        liste_diff = soustrait_a_de_b(lc, ls);
        lc = NULL, ls = NULL;
        while(comb[i] >= max) {--i;}
        comb[i] = best_majorant(comb[i], liste_diff);
        tmp = i;
        for(i=tmp+1; i<t_comb; ++i){ comb[i] = 0; }
        for(i=tmp+1; i<t_comb; ++i){ 
            lc = tab_to_liste(comb, t_comb); ls = tab_to_liste(set, t_set); 
            freeListe(liste_diff); liste_diff = NULL;
            liste_diff = soustrait_a_de_b(lc, ls);
            lc = NULL, ls = NULL;
            comb[i] = minListe(liste_diff);
        }
    }
    return res;
}

