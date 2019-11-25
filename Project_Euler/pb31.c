#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

int TAB[7] = {1, 2, 5, 10, 20, 50, 100};

/*le code ci-dessous a pour objectif de générer les différentes
 *combinaisons nécessaires à la résolution du pb31
 */

int indexTab(int elt){
	for(int i = 0; i<=6; i++){
		if(TAB[i] == elt){return i;}
	}
	return -1;
}

int tailleSup(liste * tab[], liste * l, int *cpt){
	//printf("dans la fonction tailleSup\n");
	int max = maxListe(l);
	int ind = indexTab(max);
	//liste * racine = supprimeFin(l, max);
	for(int i = ind+1; i <=6; i++){
		tab[++(*cpt)] = copie(l, max);
		//tab[*cpt] = ajoutEnQueue(tab[*cpt], max);
		tab[*cpt] = ajoutEnQueue(tab[*cpt], TAB[i]);
	}
	return 0;
}

int combinaisonDe2(liste * tab[]){
	int cpt = -1;
	for(int i = 0; i <= 5; i++){
		for(int j = i+1; j<=6; j++){
			cpt++;
			tab[cpt] = ajoutEnQueue(NULL, TAB[i]);
			tab[cpt] = ajoutEnQueue(tab[cpt], TAB[j]);
		}
	}
	return cpt;
}

int combi(liste * tab[], int * cpt, int nbr_elt){
	int tNessaire = nbr_elt - 1;
	for(int i = 0; i <= *cpt; i++){
		if(taille(tab[i]) == tNessaire){ tailleSup(tab, tab[i], cpt);}
	}
	return 0;
}

int compute(liste *l, int tgt, int * nbrSol){
	int val = l->value; int limit;
	if (taille(l) == 1){
		if(val <= tgt && tgt % val == 0){ /*printf(" %d*%d = 200\n", tgt/val, val);*/ ++(*nbrSol); return 0;}
		else{ /*printf(" %d*%d != 100\n", tgt/val, val);*/ return 0;}
	}

	if(tgt >= val && tgt % val == 0){ limit = tgt/val - 1; }
	else{ if(tgt >= val){ limit = tgt/val;} else { limit = 0;} }
	for(int i = 1; i<=limit; i++){
		//printf(" %d*%d +", i,val);
		compute(l->l, tgt - i*val, nbrSol);
	}
	return 0;
}

void ex31b(int m){
    int count=0;
    int a, b, c, d, e, f, g;
    for( a=m ; a>=0 ; a -= 200 )
    for( b=a ; b>=0 ; b -= 100 )
    for( c=b ; c>=0 ; c -= 50 )
    for( d=c ; d>=0 ; d -= 20 )
    for( e=d ; e>=0 ; e -= 10 )
    for( f=e ; f>=0 ; f -= 5 )
    for( g=f ; g>=0 ; g -= 2 )
    	printf("a = %d\n", a);
    	printf("b = %d\n", b);
    	printf("c = %d\n", c);
    	printf("d = %d\n", d);
    	printf("e = %d\n", e);
    	printf("f = %d\n", f);
    	printf("g = %d\n", g);
        count++;
	printf("ex31b: count=%d\n", count);
}

int main(){
	liste * tab[127];
	int cpt = combinaisonDe2(tab);
	int compteur = 0; int tmp;
	for(int i=3; i <=7; i++){
		combi(tab, &cpt, i);
	}

	for(int i=0; i<= cpt; i++){
		tmp = compteur;
		liste * taf = inverse(tab[i]);
		compute(taf, 200, &compteur);
		supprimeListe(taf);
		printf("________________________________\tPour la liste : ");
		afficheListe(tab[i]);
		printf(" -\t %7d possibilités \n\n", compteur - tmp);
	}
	printf("________________________________\tSoit au total %7d possibilités\n", compteur + 8);

	ex31b(200);
	return 0;
}