#include <stdio.h>

struct g_pile{
	void * data;
	struct g_pile * back;
};
typedef struct g_pile pile;

extern int Taille_p; /*utiliser cette variable pour conserver la taille
de la dernière pile*/

extern pile * empilePile(pile * p, void * donnee);

extern pile * depilePile(pile * p);

extern void   detruirePile(pile *p);

extern void * getHeadValue(pile *p);

void affichePile(pile * p);

extern int taille_pile(pile * p);

extern pile ** map_pile(pile * p);

extern void detruire_map(pile ** m, int taille);

extern pile * concatene_pile(pile * a, pile * b);
