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
	if(l==NULL){inst->next = NULL;} else {inst->next = l;} 
	return inst;
}


glist * g_intAjoutTete(glist * l, int data, list * inner_list){
    glist * head = (glist *) malloc(sizeof(glist));
    head->elt = malloc(sizeof(int));
    *((int *)head->elt) = data;
    head->lst = inner_list;
    if(l==NULL){head->next = NULL;}else{head->next=l;}
    return head;
}  


//On suppose que les listes n'ont pas de doublons
//Le 1er élément trouvé sera le seul supprimé
glist * g_supprimElt(glist * l, void * data){
	glist * tmp = l, * prec = NULL, * suiv = NULL, * cibl = NULL;
	while(tmp!=NULL){
		if(tmp->elt == data){
            //printf("g_supprimElt: suppression du pointeur : %p\n", tmp);
			cibl = tmp;
			if(prec !=NULL){prec->next = tmp->next;}
			else{suiv = tmp->next;}
			free(cibl->elt); cibl->elt = NULL;
			freeList(cibl->lst); cibl->lst = NULL;
 			free(cibl); cibl = NULL;
            //printf("g_supprimElt: tous les pointeurs supprimés ont été mis à NULL\n");
			if(prec!=NULL){
            //printf("g_supprimElt: prec retournée : %p\n", prec);
            return prec;
        }
			else{
            //printf("g_supprimElt: suiv retournée : %p\n", suiv);
            return suiv;
         }
		}
		prec = tmp; tmp=tmp->next;
	}
	return tmp;
}


void g_freeList(glist * l){
	glist * tmp = l;
	while(tmp!=NULL){tmp = g_supprimElt(tmp, tmp->elt);}
}

void g_afficheList(glist * l, void (* pt_show)(void *)){
    if(l==NULL){printf("La liste en argument est nulle\n"); return;}
    glist * tmp = l;
    while(tmp!=NULL){
       if(tmp->next != NULL){
           pt_show(tmp->elt);
           printf(" -> ");
       } else {pt_show(tmp->elt);}
       tmp = tmp->next;
    }
    printf("\n");
}

