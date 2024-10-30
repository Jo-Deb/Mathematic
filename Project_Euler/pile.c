#include <stdio.h>
#include <stdlib.h>
#include "pile.h"


pile * empilePile(pile * p, void * donnee){
	pile * res = malloc(sizeof(pile));
	res->data = donnee;
	res->back = NULL;
	if(p==NULL){return res;} else {res->back = p; return res;}
}

pile * depilePile(pile * p){
	if(p==NULL){return NULL;}
	pile * tmp = p;
	p = p->back;
	if(tmp->data != NULL){free(tmp->data);}
	tmp->back = NULL;
	free(tmp);
	return p;
}


void detruirePile(pile * p){
	pile * tmp = p;
	while(tmp!=NULL){tmp = depilePile(tmp);}
}


void * getHeadValue(pile *p){ return p->data;}

void affichePile(pile * p){
	pile * tmp = p; int* val;
	while(tmp!=NULL){
		val = (int *)getHeadValue(tmp);//déréférencement ou passage de void* à int*
		if(tmp->back!=NULL){printf("%d ",*val);}
		else{printf("%d\n",*val);}
		tmp = tmp->back;
	}
}

int taille_pile(pile * p){
    if(p == NULL){return 0;}
    pile * tmp = p;
    int res = 1;
    while(tmp->back != NULL){ ++res; tmp = tmp->back; }
    Taille_p = res;
    return res;
}

pile ** map_pile(pile * p){
    Taille_p = taille_pile(p); int i;
    pile ** res = malloc(Taille_p * sizeof(pile *)), * tmp = p;
    for(i=0; i<Taille_p; ++i){ res[i] = tmp; tmp = tmp->back; }
    return res;
}

void detruire_map(pile ** m, int taille){
    int i;
    for(i=0; i<taille; i++){ detruirePile(m[i]); }
    free(m);
}

/*On ajoute la pile b pardessus la pile a c'est donc la tête de b qui sera
 * le premier élément de la pile*/
pile * concatene_pile(pile * a, pile * b){
    pile ** m = map_pile(b);
    int i;
    for(i=Taille_p-1; i>= 0; --i){a = empilePile(a, m[i]->data);}
    detruire_map(m, Taille_p);
    return a;
}

/*
int main(){
	int i=0, *tmp; pile * p = NULL;
	for(i=0; i<10; ++i){
		tmp = malloc(sizeof(int));
		*tmp=i;
		p=empilePile(p, tmp);
	}
		affichePile(p); 
		detruirePile(p);
		p=NULL;
	return 0;
}
*/
