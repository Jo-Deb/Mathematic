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

/*liste des arrangements avec répétition pour une longueur donnée
 * et une base donnée. On part de 11111 et on arrive à 66666, 
 * on a donc 6 puissance 5 valeur a calculer, soit 7776*/
liste * combinaison(int len, int base){
	int tab[len], nbr_comb = base, i, compteur = 0, ret = 0;
	//calcul du nombre de combinaisons
	for(i=1; i < len; ++i){ nbr_comb *= base; }
	for(i=0; i < len; ++i){ tab[i] = 1; }
	liste * res = ajoutEnTete(NULL, tabToInt(tab, len));
	++compteur;
	while(compteur < nbr_comb){
		i = len - 1;
	//Boucle pour incrémenter la valeur contenu dans tab
		do {
			if(tab[i] == 6){ ret = 1; tab[i] = 1; --i;}
			else {tab[i] += 1; ret = 0;}
		}while(ret == 1 && i >= 0);
		res = ajoutEnTete(res, tabToInt(tab, len));
		++compteur;
	}
	return res;
}

/*Cette fonction permet de savoir si deux branches ont un lien de branchement.
 * Avoir un lien de branchement c'est avoir en position 3 de elt la même valeur 
 * que cur en position 1. Si retour 1 alors lien de branchement, 
 * si 0 pas de lien de branchement */
int matching(glist * elt, glist * cur){
    if(elt == NULL || cur == NULL){return 0;}

    int * tab_elt = intToTab(*((int*)elt->elt));
    int * tab_cur = intToTab(*((int*)cur->elt));
    int len = calculTailleEntier(*((int*)elt->elt));
    
    if(isPresent(tab_elt, len, tab_cur[0]) == 0 &&\
       isPresent(tab_elt, len, tab_cur[2]) == 0 &&\
       tab_elt[2] == tab_cur[1]) { return 1; }
    return 0;
}

/*Une fonction qui permet de calculer la liste de valeurs 
 * ayant un lien de branchement avec chaque branche du
 * tableau allValue*/
glist * all_with_more(glist * allValue){
    glist * loop1, * loop2, * res = NULL;
    loop1 = loop2 = allValue;
    list * lst = NULL;

    while(loop1 != NULL){
        lst = NULL;
        while(loop2 != NULL){
            if(matching(loop1, loop2)){ lst = ajoutFin(lst, *((int*)loop2->elt)); }
            loop2 = loop2->next;
        }
        g_ajoutFin(res, loop1->elt, lst);
        loop2 = allValue;
        loop1 = loop1->next;
    }
    return res;
}

void see_all_with_more(glist * alv){
    if(alv == NULL) {return;}
    glist * prc = alv;
    while(prc != NULL){
        printf("%d :", *(int*)prc->elt);
        afficheList(prc->lst); printf("\n");
        prc = prc->next;
    }
}

list * get_link_values(int n, glist * alv){
    glist * prc = alv;
    if(alv == NULL){return NULL;}
    
    while(prc != NULL){
        if(n == *(int*)prc->elt){return listCopie(prc->lst);}
        prc = prc->next;
    }
    printf("%d n'est pas une branche du tableau global\n", n);
    return NULL;
}

/*
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
   // liste * res = computeComb(taille_comb, taille_set);
   // afficheListe(res);
	liste * res = combinaison(5, 6);
	afficheListe(res);
   return 0;
}
*/
