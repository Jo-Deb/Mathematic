#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

genList * g_createList(void * elt){
	genList * l = malloc(sizeof(genList));
	l->ptr = elt; 
	l->suiv = NULL;
	return l; 	
}

genList * g_ajoutEnTete(genList * l, void * elt){
	genList * tmp = g_createList(elt);
	tmp->suiv = l;
	return tmp;
}

genList * g_ajoutEnQueue(genList * l, void * elt){
	if(l == NULL){return g_createList(elt);}
	genList * end = g_createList(elt); 
	genList * tmp = l;
	
	while(tmp->suiv != NULL){ tmp = tmp->suiv;}
	tmp->suiv = end;
	return l;
}

genList * g_supprElt(genList * l, void * elt){
	genList * tmp = l; 
	genList * prec = tmp;
	if(l->ptr == elt){tmp = l->suiv; free(l); return tmp;}	
	while(tmp != NULL){
		if(tmp->ptr == elt){
			prec->suiv = tmp->suiv;
			free(tmp);
			return l;
		}
		prec = tmp;
		tmp = tmp->suiv;
	}
	return l;
}

void g_supprimeListe(genList * l){
	if( l == NULL){ return; }
	genList * tmp = l; 
	genList * prec = tmp;
	
	while(tmp != NULL){
		prec =  tmp;
		tmp = tmp->suiv;
		free(prec);
	}
}

genList * g_supprimeFin(genList * l, void * elt){
	if(l == NULL){return NULL;}
	genList * tmp = l; 
	genList * prec = tmp;

	while(tmp != NULL){
		if(tmp->ptr == elt){
			prec->suiv = NULL;
			g_supprimeListe(tmp);
			return l;
		}
		prec = tmp;
		tmp = tmp->suiv;
	}
	return l;
} 

int g_taille(genList * l){
	if(l == NULL){return 0;}
	int len = 0;
	genList * tmp = l;
	while( tmp != NULL){++len; tmp = tmp->suiv;}
	return len;
}

genList * g_enleveDoublon(genList * l, int (*func_tri)(void *, void *)){
	genList * tmp = l; genList * tp;
	
	while(tmp!=NULL && tmp->suiv != NULL){
		tp = tmp->suiv;
		while(tp != NULL){
			if((*func_tri)(tp->ptr, tmp->ptr) == 0){ l = g_supprElt(l, tmp->ptr);}
			tp = tp->suiv;
		}
		tmp = tmp->suiv;
	}
	return l;
}



