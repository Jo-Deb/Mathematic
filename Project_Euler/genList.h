/****************************************************
*fichier genList.h
*****************************************************/

typedef struct genListe{
	void * ptr;
	struct genListe * suiv;
} genList;

extern genList * createList(void * elt);

extern genList * ajoutEnTete(genList * l, void * elt);

extern genList * ajoutEnQueue(genList * l, void * elt);

extern genList * supprElt(genList * l, void * elt);

extern void supprimeListe (genList * l);

extern genList * supprimeFin(genList * l, void * elt);

extern int taille(genList * l);

extern genList * enleveDoublon(genList * l, int (* func_tri)(void *, void *));
