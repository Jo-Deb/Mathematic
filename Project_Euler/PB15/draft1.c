#include <stdio.h>
#include <stdlib.h>

/*structure pour les noeuds des arbres binaires */

struct node {
	short  value;
	struct node *genitrice;
	struct node *bas;
	struct node *droit;
};

struct node* createNode (short value, struct node* genit, struct node* b, struct node* d){
	//Allocation mémoire pour le nouveau noeud
	struct node* noeud = (struct node*)malloc(sizeof(struct node));
	noeud->value = 1;
	noeud->genitrice = genit;
	noeud->bas = b;
	noeud->droit = d;
	return(noeud);
}

int constructionArbre(){
	

}

int main(){
	struct node* noeud = createNode(1, NULL, NULL, NULL);
	printf("Voici la structure du noeud créé\n");
	printf("valeur du noeud: %10d\n", noeud->value);
	printf("adresse du noeud géniteur: %p\n", noeud->genitrice);
	printf("adresse du fils bas: %p\n", noeud->bas);
	printf("adresse du fils droit: %p\n", noeud->droit);
}
