#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

int g_listLongueur(glist * l){
	glist * tmp = l;
	int len = 0;
	while(tmp!=NULL){++len; tmp = tmp->next;}
	return len;
}

void g_ajoutFin(glist * l, void * data, list * inner_list){
	glist * tmp = l;
	//aller à la fin de la liste
	while(tmp->next != NULL){tmp = tmp->next;}
	glist * inst = malloc(sizeof(glist));
	inst->elt = data; 
	inst->lst = inner_list;
	inst->next = NULL;
	tmp->next = inst;	
} 

glist * g_ajoutTete(glist * l, void * data, list * inner_list){
	glist * inst = malloc(sizeof(glist));
	inst->elt = data;
	inst->lst = inner_list;
	inst->next = l;
	return inst;
}

//On suppose que les listes n'ont pas de doublons
//Le 1er élément trouvé sera le seul supprimé
glist * g_supprimElt(glist * l, void * data){
	glist * tmp = l, * prec = NULL, * suiv = NULL, * cibl = NULL;
	while(tmp!=NULL){
		if(tmp->elt == data){
			cibl = tmp;
			if(prec !=NULL){prec->next = tmp->next;}
			else{suiv = tmp->next;}
			free(cibl->elt);
			freeList(cibl->lst);
 			free(cibl);
			if(prec!=NULL){return prec;}
			else{return suiv;}
		}
		prec = tmp; tmp=tmp->next;
	}
	return tmp;
}

void g_freeList(glist * l){
	glist * tmp = l;
	while(tmp!=NULL){g_supprimElt(tmp, tmp->elt); }
}
