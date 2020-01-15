#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

genList * createList(void * elt){
	genList * l = malloc(sizeof(genList));
	l->ptr = elt; 
	l->suiv = NULL;
	return l; 	
}

genList * ajoutEnTete(genList * l, void * elt){
	genList * tmp = createList(elt);
	tmp->suiv = l;
	return tmp;
}

genList * ajoutEnQueue(genList * l, void * elt){
	if(l == NULL){return createList(elt);}
	genList * end = createList(elt); 
	genList * tmp = l;
	
	while(tmp->suiv != NULL){ tmp = tmp->suiv;}
	tmp->suiv = end;
	return l;
}

genList * supprElt(genList * l, void * elt){
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

void supprimeListe(genList * l){
	if( l == NULL){ return; }
	genList * tmp = l; 
	genList * prec = tmp;
	
	while(tmp != NULL){
		prec =  tmp;
		tmp = tmp->suiv;
		free(prec);
	}
}

genList * supprimeFin(genList * l, void * elt){
	if(l == NULL){return NULL;}
	genList * tmp = l; 
	genList * prec = tmp;

	while(tmp != NULL){
		if(tmp->ptr == elt){
			prec->suiv = NULL;
			supprimeListe(tmp);
			return l;
		}
		prec = tmp;
		tmp = tmp->suiv;
	}
	return l;
} 

int taille(genList * l){
	if(l == NULL){return 0;}
	int len = 0;
	genList * tmp = l;
	while( tmp != NULL){++len; tmp = tmp->suiv;}
	return len;
}

genList * enleveDoublon(genList * l, int (*func_tri)(void *, void *)){
	genList * tmp = l; genList * tp;
	
	while(tmp->suiv != NULL){
		tp = tmp->suiv;
		while(tp != NULL){
			if((*func_tri)(tp->ptr, tmp->ptr) == 0){ l = supprElt(l, tmp->ptr);}
			tp = tp->suiv;
		}
		tmp = tmp->suiv;
	}
	return l;
}



