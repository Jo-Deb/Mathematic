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
