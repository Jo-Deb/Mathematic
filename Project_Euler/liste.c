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
	liste * prec; liste * parcours = l;
	if(l->value == elt){ parcours = l->l; free(l);return parcours;}
	else {
		while(parcours->value != elt){ prec = parcours; parcours = parcours->l; }
		prec->l = parcours->l;
		free(parcours);
		return l;
	}
	return l;
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
    if(l == NULL){printf("la liste %p est vide\n", l); return;}
	 liste * tmp = l;
	 while (tmp != NULL){
		printf("%d ", tmp->value);
		tmp = tmp->l;
	 }
}

int taille(liste * l){
    if(l == NULL){return 0;}
	 int cpt = 0; liste * tmp = l;
	 while(tmp != NULL){
        ++cpt; 
        tmp = tmp->l;
    }
	 return cpt;
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
	if(l == NULL){return 0;}
	if(l->l == NULL){ free(l); return 0;}
	liste * tmp = l;
	liste * tmp2;
	while(tmp != NULL){
		tmp2 = tmp->l;
		free(tmp);
		tmp = tmp2;
	}
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

int minListe(liste * l){
    int min = l->value;
    liste * tmp = l;
    while(tmp != NULL){ 
        if(tmp->value < min){ min = tmp->value; } 
        tmp = tmp->l;
    }
    return min;
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

liste * ListeSupprimeDoublon(liste * l){
	liste * pcr1 = l; liste * pcr2;
	while(pcr1 != NULL){
		if(EstPresent(pcr1->l, pcr1->value) == 0){
			l = supprElt(l, pcr1->value);
			pcr1 = l;
		} else { pcr1 = pcr1->l;}
	}
	return l;
}

liste * split(int elt){
	int tmp = elt; liste * sortie=NULL;
	while(tmp > 0){sortie = ajoutEnTete(sortie, tmp%10); tmp = tmp / 10;}
	return sortie;
}

int compareList(liste * l1, liste * l2){
	
	liste * cp=recopie(l1); liste * cp1 = recopie(l2);
	liste * tmp = cp; liste * tmp1 = cp1;
	while(tmp!=NULL){
		if(EstPresent(tmp1, tmp->value) == 0){
			cp1=remplace(cp1, tmp->value, 0);
			tmp->value=0; tmp = tmp->l;
		}else{tmp=tmp->l;}
	}
	int somme = 0; int somme1 = 0;
	tmp = cp;
	while(tmp1!=NULL){somme1 += tmp1->value; tmp1 = tmp1->l;}
	while(tmp!=NULL){somme += tmp->value; tmp = tmp->l;}
	if(somme1 > 0 || somme > 0){return 1;}else{return 0;}
}

liste * listTrie(liste * l){
	/*On va au plus simple et on commence par un tri à bulle*/
	liste * l1 = l; liste * l2 = NULL;
	int tmp;
	while(l1 != NULL && l1->l != NULL){
		l2 = l1->l;
		while(l2!=NULL){
			if(l2->value < l1->value){
				tmp = l2->value; 
				l2->value = l1->value;
				l1->value = tmp;
			}
			l2 = l2->l;
		}
		l1 = l1->l;
	}
	return l;
}

liste * sousListe(liste * l, int start, int end){
	liste * pcr = l; liste * res = NULL;
	if(end > taille(l) || start > taille(l) || end <= 0 || start <= 0) {
		printf("l'intervalle demandé n'existe pas \n");
		return NULL;
	}
	int position = 1;
	while(position < start){++position; pcr = pcr->l;}
	if(start == end){ return ajoutEnQueue(res, pcr->value); }
	while(position <= end){
		  res = ajoutEnQueue(res, pcr->value);
		  if(pcr->l != NULL){pcr = pcr->l;}
        ++position;
	}
	return res;
}

int getPosition(liste * l, int elt){
	liste * pcr = l; int position = 1;
	while(pcr != NULL){
		if(pcr->value == elt){ return position;}
      else{
		  if(pcr->l != NULL){ pcr = pcr->l; ++position;}
        else{pcr = pcr->l;}
	   }
   }
	printf("la valeur %d n'a pas été retrouvé dans la liste :", elt);
	afficheListe(l);
	printf("\n La valeur -1 sera retournée\n");
	return -1;
}

liste * setPosition(liste *l, int pos, int elt){
	liste * pcr = l; int position = 1;
	while(position < pos){ pcr = pcr->l; ++position;}
	pcr->value = elt;
	return l;
}

int getValue(liste * l, int pos){
	liste * pcr = l; int position = 1;
	while(position < pos){pcr = pcr->l; ++position;}
	return pcr->value;
}

liste * inversePosition(liste * l, int pos1, int pos2){
	int pos1Value = getValue(l, pos1);
	int pos2Value = getValue(l, pos2);
	l = setPosition(l, pos2, pos1Value);
	l = setPosition(l, pos1, pos2Value);
	return l;
}

liste * triInverse(liste * l){
	/*On va au plus simple et on commence par un tri à bulle*/
	liste * l1 = l; liste * l2 = NULL;
	int tmp;
	while(l1 != NULL && l1->l != NULL){
		l2 = l1->l;
		while(l2!=NULL){
			if(l2->value > l1->value){
				tmp = l2->value; 
				l2->value = l1->value;
				l1->value = tmp;
			}
			l2 = l2->l;
		}
		l1 = l1->l;
	}
	return l;
}

int listeToInt(liste * l){
	int res = 0;
	liste * pcr = l;
	while(pcr != NULL){ res = res * 10 + pcr->value; pcr = pcr->l;}
	return res;
}

int precedent(liste * l, int elt){
	liste * prec = NULL; liste * pcr = l;
	while(pcr!=NULL && pcr->value != elt){ prec = pcr; pcr = pcr->l;}
	if(pcr->value == elt) {return prec->value;}
	else{ printf("la valeur %d n'est pas présente dans la liste, échec\n", elt); return -1;}
}

int suivant(liste * l, int elt){
	liste * pcr = l;
	while(pcr!=NULL && pcr->value!=elt){ pcr = pcr->l;}
	if(pcr->value == elt){ return pcr->l->value;}
	else{printf("la valeur %d n'est pas présente dans la liste, échec\n", elt); return -1;}
}

liste * trieSousListe(liste * l, int start){
	liste * pcr = l; liste * taf = NULL;
	int posi = 1; int tmp;
	/*Permet de se positionner*/
	while(posi < start){ pcr = pcr->l; ++posi;}
	while(pcr!=NULL){
		taf = pcr->l;
		while(taf != NULL){
			if(taf->value < pcr->value){ 
				tmp = pcr->value; 
				pcr->value = taf->value; 
				taf->value = tmp;
			}
			taf = taf->l;
		}
		pcr = pcr->l;
	}
	return l;
}

/*ajoute la liste lb à la suite de la liste la
 * si une des 2 listes est nulle, l'autre est retournée
 * si les 2 listes sont nulles, à la fin de la fonction
 * la liste lb est libérée*/
liste * concateneListe(liste * la, liste * lb){
    if(la == NULL){return lb;}
    if(lb == NULL){return la;}
    liste * tmp = lb;
    while(tmp != NULL){ 
        la = ajoutEnQueue(la, tmp->value); 
        tmp = tmp->l;
    }
    supprimeListe(lb);
    return la;
}

void freeListe(liste * la){
    liste * suiv = la, * current = NULL;
    while(suiv != NULL){
        current = suiv;
        suiv = suiv->l;
        free(current);
    }
}

void vfreeListe(void * l){ freeListe((liste *) l); }

int lastElement(liste * l){ return getValue(l, taille(l)); }

extern liste * liste_diff(liste * la, liste * lb){
    liste * tmp = la, * res = NULL;
    while(tmp != NULL){
       if(EstPresent(lb, tmp->value) == 1){ res = ajoutEnTete(res, tmp->value);} 
       tmp = tmp->l;
    }
    tmp = lb;
    while(tmp != NULL){
       if(EstPresent(la, tmp->value) == 1){ res = ajoutEnTete(res, tmp->value);} 
       tmp = tmp->l;
    }
    return res;
}

/*Prend la liste a et soustrait les éléments de cette liste à la liste b*/
liste * soustrait_a_de_b(liste * la, liste * lb){
    liste * tmp = la, *res = recopie(lb);
    while(tmp != NULL){
        if(EstPresent(res, tmp->value) == 0){ res = supprElt(res, tmp->value); }
        tmp = tmp->l;
    }
    return res;
}

/*change le tableau donné en argument en liste*/
liste * tab_to_liste(int * tab, int ttab){
    liste * res = NULL;
    int i;
    for(i=0; i<ttab; ++i){ res = ajoutEnQueue(res, tab[i]); }
    return res;
}

/*Renvoyer le meilleur majorant dans une liste pour une valeur entière donnée en 
 * argument. Le meilleur majorant étant celui le plus près de la valeur donnée
 * valeur retournée : le majorant si celui-ci existe ou une valeur négative dans
 * le cas contraire*/
int best_majorant(int a, liste * l){
    liste * tmp = l;
    int bm = maxListe(l);
    if(a >= bm){ printf("best_majorant: aucune valeur dans %p ne majore %d\n", l, a); return -1; }
    while(tmp != NULL){
        if(tmp->value < bm && tmp->value > a){ bm = tmp->value; }
        tmp = tmp->l;
    }
    return bm;
}

/*retourne 0 si les listes sont identiques, sinon 1*/
int identique(liste * la, liste * lb){
    if(taille(la) != taille(lb)){return 1;}
    liste * tmp = la, * tmq = lb;
    while(tmp != NULL){
        if(tmp->value != tmq->value){return 1;}
        tmp = tmp->l; tmq = tmq->l;
    }
    return 0;
}
