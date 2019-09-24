#include <stdio.h>
#include "liste.h"

liste * createList( int elt){
	liste * l = malloc(sizeof(liste));
	l->value = elt; l->l = NULL;
	return l;
}

liste * ajoutEnTete(liste * l, int elt){
	liste * j = malloc(sizeof(liste));
	j->value = elt; j->l = l;
	return j;
}

liste * supprElt(liste * l, int elt){
	liste * prec; liste * suiv; liste * parcours = l;
	if(l->value == elt){ return l->l;}
	else {
		while(parcours->value != elt){ prec = parcours; parcours = parcours->l; }
		prec->l = parcours->l;
		free(parcours);
		return l;
	}
	return l;
}

int EstPresent( liste * l, int elt ){
	liste * parcours;
	while( parcours->value != elt ){parcours = parcours->l;}
	if( parcours->value == elt ) { return 0; }
	return 1;
}