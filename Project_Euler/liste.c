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

int taille(liste * l){
	int cpt = 0; liste * tmp = l;
	while(tmp != NULL){++cpt; tmp = tmp->l;}
	return cpt;
}

int EstPresent( liste * l, int elt ){
	liste * parcours = l;
	while( parcours != NULL && parcours->value != elt ){parcours = parcours->l;}
	if( parcours != NULL && parcours->value == elt ) { return 0; }
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
	if(l == NULL){return 0;}
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

liste * supprimeFin(liste * l, int elt){
	liste * tmp = l; liste * prec; liste * tmp2;
	if(l != NULL && l->value == elt) {supprimeListe(l); return NULL;}
	while(tmp != NULL && tmp->value != elt){ prec = tmp; tmp = tmp->l;}
	//si tmp est null alors elt n'est pas dans la liste et on renvoie l
	if(tmp == NULL){return l;}
	if(tmp->value == elt){
		prec->l = NULL;
		while(tmp != NULL){
			tmp2 = tmp->l;
			free(tmp);
			tmp = tmp2;
		}
		return l;
	}
	return l;
}

int maxListe(liste * l){
	if(l == NULL){ return 0;}
	int max = l->value;
	liste * tmp = l;
	while(tmp != NULL){
		if (max < tmp->value) {max = tmp->value;}
		tmp = tmp->l;
	}
	return max;
}

liste * copie(liste * li, int elt){
	liste * l = NULL; liste * tmp = li;
	if(li == NULL){return li;}
	while(tmp != NULL && tmp->value <= elt){
		l = ajoutEnQueue(l, tmp->value);
		tmp = tmp->l;
	}
	return l;
}

liste * inverse(liste *l){
	liste * tmp, * res = NULL; 
	tmp = l;
	while(tmp != NULL){
		res = ajoutEnTete(res, tmp->value);
		tmp = tmp->l;
	}
	return res;
}

liste * recopie(liste * l){
	if(l==NULL){return NULL;}
	liste * res = NULL; liste * ex = l;
	while(ex != NULL){
		res = ajoutEnQueue(res, ex->value);
		ex = ex->l;
	}	
	return res;
}

liste * remplace(liste * l, int t, int r){
	liste * pcr = l;
	while(pcr != NULL){
		if(pcr->value == t){ pcr->value = r; return l;}
		pcr = pcr->l;
	}
	return l;	
}

liste * supprimeDoublon(liste * l){
	liste * pcr1 = l; liste * pcr2;
	while(pcr1 != NULL){
		if(EstPresent(pcr1->l, pcr1->value) == 0){
			l = supprElt(l, pcr1->value);
			pcr1 = l;
		} else { pcr1 = pcr1->l;}
	}
	return l;
}
