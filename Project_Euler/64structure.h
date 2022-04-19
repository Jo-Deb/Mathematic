#include <stdio.h>

struct irrationnel {
	int racine;
	int suppl;
} 
typedef struct irrationnel irrationnel;

struct fractir {
	irrationnel * num;
 	int 	deno;
}
typedef struct fractir fractir;

struct fractionContinue {
	int an;
	fractir * frac;
}
typedef struct fractionContinue cfrac;

/*Définition des fonctions pour l'utilisation des types*/

irrationnel * createIrrationnel(int racine, int suppl);
fractir * createFractir(irrationnel * num, int deno);
cfrac * createCFrac(int an, fractir * frac);
int egaliteIrrationnel(irrationnel a, irrationnel b);
int egaliteFractir(fractir a, fractir b);
int egaliteCfrac(cfrac a, cfrac b);
void freeIrrationnel(irrationnel * a);
void freeFractir(fractir * a);
void freecFrac(cfrac * a);
int nearestRoot(irrationnel * a);
fractir * irraToFractir(irrationnel * a);
cfrac * fractirToCfrac(fractir * a);
