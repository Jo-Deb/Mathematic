#include <stdio.h>
#include <stdlib.h>

#define VALEUR_ARTIFICIEL 300

//int mainTab[3628800][10];
int mainTab[3628800][10];

typedef struct liste{ 
	int value;
	struct liste * ptr;
} list;

list * createlist( int val, list * pointeur){
	list * elt = malloc(sizeof(list));
	elt->value = val;
	elt->ptr = pointeur;
	return elt;
}

list * completelist(){
	list * first = createlist(9, NULL);
	list * ptr;
	for( int i = 8; i >= 0; i--){
		ptr = createlist(i, NULL);
		ptr->ptr = first;
		first = ptr;
	}
	return first;
}

void afficheliste(list * liste){
	printf("la liste est ainsi composée :");
	list * l = liste;
	while(l != NULL){
		printf("%d ", l->value);
		l = l->ptr;
	}
}

list * retirer(list * pointeur, int val){
	list * precedent = pointeur; list * suivant = NULL; list * actuel = pointeur->ptr;
	if(pointeur->value ==  val){ free(pointeur); return actuel;}
	while (actuel != NULL){
		if (actuel->value == val) {
			precedent->ptr = actuel->ptr;
			free(actuel);
		}
		precedent = actuel;
		actuel = actuel->ptr;
	}
	return pointeur;
}

int choixValeur( int mainTab[], list * l, int index){
	//reconstruction de la liste si celle-ci est vide
	int i = 0; int result; list * pt = l;
	for( int j = 0; j < index;){
		if(pt == NULL){ printf("la liste  l est nulle");}
		if(mainTab[j] == pt->value && pt->ptr != NULL){ l = retirer(l, pt->value); pt = pt->ptr; j = 0; }
		if(mainTab[j] == pt->value && pt->ptr == NULL){ l = retirer(l, pt->value); return 0;}
		else{ j++; }
	}
	result = pt->value;
	return result;
}

int main(){
	int tabtmp[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}; int limit = 3628800; int step = limit; int count = 0;
	int tmp; list * l = completelist();
	printf("#################### Début du main, avant modification du tableau voici son contenu\n");

//Boucle principale
	for( int i = 0; i < 10; i++){
		step = step / (10 - i);

		for(int j = 0; j < limit; j++){
			if(j % step == 0){
				if( l == NULL){ l = completelist(); }
				for(int k = 0; k < i; k++){ l = retirer(l, mainTab[j][k]);}
				if( l == NULL){ l = completelist(); }
				tmp = l->value;
				//tmp = choixValeur(mainTab[j], l, i);
				//if(tmp == 0){ l = completelist(); tmp = choixValeur(mainTab[j], l, i);}
				l = retirer(l, tmp);
				mainTab[j][i] = tmp;
			}
			else{ mainTab[j][i] = tmp; /*printf("step = %d, li = %d, col = %d, val =  %d\n", step, j, i, tmp);*/}
		}
	}
//Affichage du tableau
/*
 	for(int i = 0; i < limit; i++){
		printf("%d -> ", i);
		for(int j = 0; j < 10; j++){
			printf("%d ", mainTab[i][j]);
		}
		printf("\n");
	}
*/
	printf("la ligne à la position 1000 000 est : ");
	for(int i = 0; i < 10; i++){ printf("%d", mainTab[999999][i]);}
	return 0;
}