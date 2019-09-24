/*****************************************************************************
*fichier liste.h
******************************************************************************/

typedef struct list{
	int value;
	list * l;
} liste;

extern liste * createList(int elt);

extern liste * ajoutEnTete(liste * l, int elt);

extern liste * supprElt(liste * l, int elt);

extern int EstPresent(liste * l, int elt);

extern int detectionDeCycle(liste * l, int elt);

extern void afficheCycle(liste * l, int elt, int taille);