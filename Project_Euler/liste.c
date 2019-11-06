#include <stdio.h>
#include <stdlib.h>
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
	if(l->value == elt){ parcours = l->l; free(l); return parcours;}
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

int detectionDeCycle(liste * l, int elt){
	int i = 0; int compte = 0; liste * tmp = l;
	while(tmp != NULL){
		if(tmp->value == elt) {++i;}
		if(i > 1){ return compte;}
		if(i == 1) { ++compte;}
		tmp = tmp->l;
	}
	return 0;
}

void afficheCycle(liste * l, int elt, int taille){
	int i = 0; liste * tmp = l;
	while(tmp != NULL){
		if(tmp->value == elt){
			for(i=0; i <= taille; i++){
				printf("%d-", tmp->value);
				tmp = tmp->l;
			}
			return;
		}
		tmp = tmp->l;
	}
}

void afficheListe(liste * l){
	liste * tmp = l;
	while (tmp != NULL){
		printf("%d ", tmp->value);
		tmp = tmp->l;
	}
}

liste * ajoutEnQueue(liste * l, int elt){
	if(l == NULL){ return createList(elt);}

	liste * tmp = l; 
	liste * eltFinal = createList(elt);

	while(tmp->l != NULL){ tmp = tmp->l;}
	tmp->l = eltFinal;
	return l;
}

int supprimeListe(liste * l){
	//printf("dans la fonction de suppression de la liste\n");
	if(l->l == NULL){ free(l); return 0;}
	liste * tmp = l;
	liste * tmp2;
	while(tmp != NULL){
		tmp2 = tmp->l;
		free(tmp);
		tmp = tmp2;
		//printf("libération du pointeur %p\n", tmp2);
	}
	//while(tmp != NULL){ tmp = supprElt(tmp, tmp->value);}
	//printf("la fonction de suppression est fini\n");
	return 0;
}
