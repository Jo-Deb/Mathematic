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

extern int minListe(liste *l);

extern liste * copie(liste * l, int elt);

extern liste * inverse(liste * l);

extern liste * recopie(liste * l);

extern liste * remplace(liste *l, int t, int r);

extern liste * ListeSupprimeDoublon(liste *l);

extern liste * split(int elt);

extern int compareList(liste * l1, liste * l2);

extern liste * listTrie(liste * l);

extern liste * sousListe(liste * l, int start, int end);

extern int getPosition(liste *l, int elt);

extern int getValue(liste * l, int pos);

extern liste * setPosition(liste * l, int pos, int elt);

extern liste * inversePosition(liste * l, int pos1, int pos2);

extern liste * triInverse(liste * l);

extern int listeToInt(liste * l);

extern int precedent(liste * l, int elt);

extern int suivant(liste * l, int elt);

extern liste * trieSousListe(liste * l, int start);

extern liste * concateneListe(liste * la, liste * lb);

extern void freeListe(liste * la);

extern void vfreeListe(void * l);
