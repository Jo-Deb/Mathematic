#include <stdio.h>

struct g_pile{
	void * data;
	struct g_pile * back;
};
typedef struct g_pile pile;

extern pile * empilePile(pile * p, void * donnee);

extern pile * depilePile(pile * p);

extern void   detruirePile(pile *p);

extern void * getHeadValue(pile *p);

void affichePile(pile * p);

