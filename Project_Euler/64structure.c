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

int norme(irrationnel * irr){
	int racine = irr->racine, suppl = abs(irr->suppl);
	return (racine - (suppl*suppl));
}

int isFormeBrute(fracB * elt){
	int num = elt->num;
	irrationnel * deno = elt->deno;
	if(deno->racine != 0 && num > 0 && deno->suppl !=0){return 1;} else {return -1;}
}

fractir * formePropre(fracB * fbrut){
	if(isFormeBrute(fbrut) < 0){printf("formePropre: l'argument en entrée n'est pas une forme brute\n"); return NULL;}
	int Vnorme = norme(fbrut->deno), Vnum = fbrut->num;
	if(Vnorme % Vnum > 0){printf("formePropre: l'argument %d ne divise pas %d\n", Vnum, Vnorme); return NULL;}
	int k = Vnorme/Vnum;
	fractir * res = createFractir(createIrrationnel(fbrut->deno->racine, -1*fbrut->deno->suppl), k);	
	return res;
}

int partieEntiere(fractir * elt){
	int sqrt = elt->num->racine, suppl = elt->num->suppl, ns = nearestRoot(elt->num->racine);
	if(elt->deno == 0){printf("partieEntiere: denominateur = 0, erreur!\n"); return -1;}	 
	int An = (ns + suppl)/elt->deno;
	if(An == 0){printf("partieEntiere: la partie est nulle, erreur!"); return -1;}
	elt->num->suppl = ((An * elt->deno) - elt->num->suppl) * -1;
	return An;
}

fracB * nextFb(fractir *fr){
	irrationnel * deno = createIrrationnel(fr->num->racine, fr->num->suppl);
	return createFracB(fr->deno, deno);
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

