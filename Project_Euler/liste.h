/*****************************************************************************
*fichier liste.h
******************************************************************************/

typedef struct list{
	int value;
	struct list * l;
} liste;

extern liste * createList(int elt);

extern liste * ajoutEnTete(liste * l, int elt);

extern liste * supprElt(liste * l, int elt);

extern int EstPresent(liste * l, int elt);

extern int detectionDeCycle(liste * l, int elt);

extern void afficheCycle(liste * l, int elt, int taille);

extern void afficheListe(liste * l);

extern liste * ajoutEnQueue(liste * l, int elt);

extern int supprimeListe(liste * l);

extern liste * supprimeFin(liste * l, int elt);

extern int taille(liste * l);

extern int maxListe(liste * l);

extern liste * copie(liste * l, int elt);

extern liste * inverse(liste * l);
