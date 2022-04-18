#include <stdio.h>
#include <stdlib.h>
#include "64structure.h"

irractionnel * createIrrationnel(int racine, int suppl){
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

int egaliteIrrationnel(irrationnel a, irrationnel b){
	if (a.racine == b.racine && a.suppl == b.suppl){ return 0;}
	else return 1;
}

int egaliteFractir(fractir a, fractir b){
	if (egaliteIrrationnel(a.num, b.num) == 0 && a.deno == b.deno){ return 0;}
	else return 1;
}

int egaliteCfrac(cfrac a, cfrac b){
	if (egaliteFractir(a.frac, b.frac) == 0 && a.an == b.an){ return 0;}
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

int nearestRoot(irrationel * a){
	int i = 1;
	while ((i*i) <= a->racine){++i;}
	--i;
	return i;
}
