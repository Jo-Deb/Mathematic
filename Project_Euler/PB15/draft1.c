#include <stdio.h>
#include <stdlib.h>

/*structure pour les noeuds des arbres binaires */

struct node {
	short  value;
	struct node *genitrice;
	struct node *bas;
	struct node *droit;
};

node* createNode (short value, node* genet, node* b, node* d){
	//Allocation mémoire pour le nouveau noeud
	struct node* noeud = (struct node*)malloc(sizeof(struct node));
	noeud->value = 1;
	noeud->genetrice = genet;
	noeud->bas = b;
	noeud->droit = d;
}
