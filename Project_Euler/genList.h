#include <stdio.h>
#include "gestionList.h"

/*
 * la structure est à refaire car il nous faut 3 éléments.
 * un pointeur vers la valeur principale, un pointeur vers la liste 
 * associée à la valeur principale et un pointeur vers le reste de la 
 * liste résultat
 */

struct genList{
	void * elt;
	list * lst;
	struct genList * next;
};

typedef struct genList glist;

extern int g_listLongueur(glist * l);

extern void g_ajoutFin(glist * l, void * data, list * inner_list);

extern glist * g_ajoutTete(glist * l, void * data, list * inner_list);

extern glist * g_intAjoutTete(glist * l, int data, list * inner_list);

extern void g_intAjoutFin(glist * l, int data, list * inner_list);

extern void g_purgeData(void * data);

extern glist * g_supprimElt(glist * l, void * data);

extern void g_freeList(glist * l);

extern void g_afficheList(glist * l, void(* pt_show)(void *));

extern void * g_getList(glist * l, int numList);

extern void g_freeGenList(glist *l, void(* pt_freeFunction)(void *));

extern glist * g_getLastElt(glist * l);

/*cette fonction met la liste b à la suite de a */
extern glist * glistConcat(glist * a, glist * b);
