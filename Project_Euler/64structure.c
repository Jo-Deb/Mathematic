#include <stdio.h>
#include <stdlib.h>
#include "64structure.h"

irrationnel * createIrrationnel(int racine, int suppl){
	irrationnel * res = malloc(sizeof(irrationnel));
	res->racine = racine;
	res->suppl = suppl;
	return res;
}

fractir * createFractir(irrationnel * num, int deno){
	fractir * res = malloc(sizeof(fractir));
	res->num = num;
	res->deno = deno;
	return res;
}

cfrac * createCFrac(int an, fractir * frac){
	cfrac * res = malloc(sizeof(cfrac));
	res->an = an;
	res->frac = frac;
	return res;
}

int egaliteIrrationnel(irrationnel * a, irrationnel * b){
	if (a->racine == b->racine && a->suppl == b->suppl){ return 0;}
	else return 1;
}

int egaliteFractir(fractir * a, fractir * b){
	if (egaliteIrrationnel(a->num, b->num) == 0 && a->deno == b->deno){ return 0;}
	else return 1;
}

int egaliteCfrac(cfrac * a, cfrac * b){
	if (egaliteFractir(a->frac, b->frac) == 0 && a->an == b->an){ return 0;}
	else return 1;
}

void freeIrrationnel(irrationnel * a){free(a);}

void freeFractir(fractir * a){
	freeIrrationnel(a->num);
	free(a);
}

void freecFrac(cfrac * a){
	freeFractir(a->frac);
	free(a);
}

int nearestRoot(irrationnel * a){
	int i = 1;
	while ((i*i) <= a->racine){++i;}
	--i;
	return i;
}

fractir * irraToFractir(irrationnel * a){ return createFractir(a, 1); }

cfrac * fractirToCfrac(fractir * a){return createCFrac(0, a);}

fraction * createFraction(cfrac * num, cfrac * deno){
    fraction * res = malloc(sizeof(fraction));
    if(num != NULL){ res->num = num;} else{res->num = NULL;}
    if(deno != NULL){ res->deno = deno;} else{res->deno = NULL;}
    return res;
}

fracB * createFracB(int num, irrationnel * deno){
    fracB * res = malloc(sizeof(fracB));
    res->num = num;
    res->deno = deno;
    return res;
}

/*___________Fonctions d'affichage______________________*/
void afficheIrrationnel(irrationnel * a){
    if(a->racine < 0){
        printf("%d < 0 erreur pour une racine, le programme échouera", a->racine);
        return;
    }
    if(a->racine > 0 && a->suppl > 0){
        printf("sqrt(%d)+%d", a->racine, a->suppl);
        return;
    }
    if(a->racine > 0 && a->suppl < 0){
        printf("sqrt(%d) %d", a->racine, a->suppl);
        return;
    }
    if(a->racine > 0 && a->suppl == 0){
        printf("sqrt(%d) ", a->racine);
        return;
    }
    if(a->racine == 0 ){
        printf("%d", a->suppl);
        return;
    }
}

void afficheFractir(fractir * b){
   irrationnel * a = b->num;
   printf(" %d/", b->deno);
   printf("(");
   afficheIrrationnel(a);
   printf(")");
}

void afficheCfrac(cfrac * c){
    printf("%d + (", c->an);
    afficheFractir(c->frac);
    printf(" )");
}

/*L'argument reçu doit être un pointeur de type fractir
 * car un cast est fait dans la fonction*/
void showFractir(void * pt){
    afficheFractir((fractir *)(pt));
}
/*------------fonction de libération des pointeurs---------------------*/

