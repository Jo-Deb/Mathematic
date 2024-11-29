#include <stdio.h>
#include <stdlib.h>

struct g_list {
	int elt; 
	struct g_list * l; 
	struct g_list * prev;
};

typedef struct g_list list;

int listLongueur(list * l){
	if(l==NULL){return 0;}
	list * tmp = l; int i=0;
	while(tmp!=NULL){++i; tmp=tmp->l;}
	return i;
}

list * ajoutFin(list *l, int n){
	list * tmp= malloc(sizeof(list));
	tmp->elt = n; tmp->l = NULL;
	if(l==NULL){tmp->prev = NULL; return tmp;}
	else{
		list * pcr = l;
		while(pcr->l!=NULL){pcr=pcr->l;}
		pcr->l=tmp; tmp->prev = pcr;
	}
	return l;
}

list * deleteLastElts(list * l, int n){
	if(listLongueur(l) < n){
		printf("%d est supérieur à la longueur de la liste: %d, abandon\n", n, listLongueur(l));
		printf("la liste, sans retrait, sera retournée\n");
		return l;
	}
	list * tmp = l, *pcr=NULL; 
	while(tmp->l!=NULL){tmp=tmp->l;}//boucle pour se mettre au bout de la liste
	int i=0;
	for(i=0; i<n; i++){
		pcr=tmp; tmp=tmp->prev; 
		if(tmp!=NULL){tmp->l=NULL;} 
		free(pcr); pcr=NULL;
	}
	return l;
}

int getElt(list * l, int n){
	if(l==NULL){printf("la liste est vide ne pas prendre en compte le retour\n"); return -1;}
	if(listLongueur(l) < n){
		printf("getElt: n=%d est trop grand, ne pas prendre en compte le retour\n", n); 
		return -1;
	}
	list * tmp = l;
	int i=1; while(i<n){tmp=tmp->l; ++i;}//On se place sur le nième élément
	return tmp->elt;
}

void afficheList(list * l){
	list * tmp = l;
	while(tmp!=NULL){
		if(tmp->l!=NULL){printf("%d->", tmp->elt);} 
		else{printf("%d", tmp->elt);}
		tmp=tmp->l;
	}
	//printf("\n");
}

list * getPartList(list * l, int n){
	if(l==NULL){ printf("La liste est nulle, la fonction retournera NULL\n"); return NULL;}
	int i=0; list * tmp=NULL, *pcr=NULL, *ll=NULL, *prev=NULL;
	pcr = l;
	if(n>0){
		while(i<n){
			prev=tmp;
			tmp=malloc(sizeof(list));
			tmp->elt = pcr->elt; tmp->l=NULL;
			tmp->prev = prev; if(prev!=NULL){prev->l=tmp;}
			if(ll==NULL){ll = tmp;}
			++i; pcr=pcr->l;
		}
		return ll;
	}
	if(n<0){
		pcr=l; prev=NULL;
		i=0; int lim=listLongueur(l); int dist=lim+n;
		while(i<dist){pcr=pcr->l; ++i;}	
		while(i<lim){
			tmp=malloc(sizeof(list)); tmp->prev=NULL; tmp->l=NULL;
			tmp->elt=pcr->elt;
			if(ll==NULL){ll=tmp; ll->prev=NULL;}
			if(prev!=NULL){tmp->prev = prev; prev->l = tmp;}
			prev = tmp; ++i;
			if(pcr->l!=NULL){pcr = pcr->l;}
		}
		return ll;
	}
	return l;
}

void freeList(list * l){
	if(l==NULL){/*printf("freeList: La liste est nulle, pas de free possible\n");*/ return;}
	list * current=NULL, *next=NULL;
	current = l; next = current->l;
	while(next!=NULL){free(current); current=next; next = next->l;}
	free(current);
}

list * supprimElt(list *l, int elt){
	list * tmp = l, *prev=l;
	if(l==NULL){return NULL;}
	if(tmp->elt==elt){
		prev = tmp->l; free(tmp);
		if(prev!=NULL && prev->prev!=NULL){prev->prev=NULL; return prev;}
		if(prev!=NULL && prev->prev==NULL){return prev;}
		if(prev==NULL){return NULL;}
	}
	else{
		while(tmp!=NULL){
			if(tmp->elt == elt){
				prev->l = tmp->l; free(tmp);
				return l;
			}
			prev=tmp; tmp=tmp->l;
		}
	}
	return l;
}

list * concatList(list *l1, list *l2){
	if(l1==NULL){return l2;}
	if(l2==NULL){return l1;}
	list * tmp = l1;
	while(tmp->l!=NULL){tmp=tmp->l;}
	tmp->l = l2; 
	return l1;
}

int getLastElt(list * l){
	list * tmp = l;
	while(tmp->l != NULL){tmp = tmp->l;}
	return tmp->elt;
}

/*Si la valeur retournée est 0 alors elt n'est pas dans la liste, 
 * si la valeur retournée est 1 c'est le contraire*/
int gl_isPresent(list * l, int elt){
    list * tmp = l;
    while(tmp->l != NULL){
        if(tmp->elt == elt) {return 1;}
        tmp = tmp->l;
    }
    return 0;
}

list * listCopie(list * l){
    list * res = NULL, * ptr = l;
    while(ptr != NULL){
        res = ajoutFin(res, ptr->elt);
        ptr = ptr->l;
    }
    return res;
}

/*int main(){
	list * l=NULL;
	int i=0, j, v;
	for(i=1; i<10; i++){
		for(j=0; j<=10; j++){l=ajoutFin(l, j*j);}
		afficheList(l);
		//v=getElt(l, i);
		l = getPartList(l, -i);
		printf("La liste partielle, constituée de %d éléments,  est : ", i); afficheList(l);
		freeList(l);
		l=NULL;
	}
	return 0;
}
*/
