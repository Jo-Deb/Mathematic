/****************************************************
*fichier genList.h
*****************************************************/

typedef struct genListe{
	void * ptr;
	struct genListe * suiv;
} genList;

extern genList * g_createList(void * elt);

extern genList * g_ajoutEnTete(genList * l, void * elt);

extern genList * g_ajoutEnQueue(genList * l, void * elt);

extern genList * g_supprElt(genList * l, void * elt);

extern void g_supprimeListe (genList * l);

extern genList * g_supprimeFin(genList * l, void * elt);

extern int g_taille(genList * l);

extern genList * g_enleveDoublon(genList * l, int (* func_tri)(void *, void *));
