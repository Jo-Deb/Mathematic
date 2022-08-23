#include <stdio.h>

struct irrationnel {
	int racine;
	int suppl;
}; 
typedef struct irrationnel irrationnel;

struct fractir {
	irrationnel * num;
 	int 	deno;
};
typedef struct fractir fractir;

struct fractionContinue {
	int an;
	fractir * frac;
};
typedef struct fractionContinue cfrac;

struct fraction {
    cfrac * num;
    cfrac * deno;
};
typedef struct fraction fraction;

/*Définition des fonctions pour l'utilisation des types*/
/*________fonctions d'initialisation des types_______________*/
extern irrationnel * createIrrationnel(int racine, int suppl);
extern fractir * createFractir(irrationnel * num, int deno);
extern cfrac * createCFrac(int an, fractir * frac);
extern int egaliteIrrationnel(irrationnel * a, irrationnel * b);
extern int egaliteFractir(fractir * a, fractir * b);
extern int egaliteCfrac(cfrac * a, cfrac b);
extern void freeIrrationnel(irrationnel * a);
extern void freeFractir(fractir * a);
extern void freecFrac(cfrac * a);
extern int nearestRoot(irrationnel * a);
extern fractir * irraToFractir(irrationnel * a);
extern cfrac * fractirToCfrac(fractir * a);
extern fraction * createFraction(cfrac * num, cfrac * deno);
/*____________________________________________________________*/

/*___________fonctions d'affichage des structures_____________*/
extern void afficheIrrationnel(irrationnel * a);
extern void afficheFractir(fractir * b);
extern void afficheCfrac(cfrac * c);
