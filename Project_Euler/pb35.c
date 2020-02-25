#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include "genList.h"

int main(int argc, char ** argv){
	int in1, in2;
	if(argc != 3){ 
		printf("Vous devez donner deux valeurs entières; le programme va s'arrêter en échec\n"); 
		exit(EXIT_FAILURE);
	}
	sscanf(argv[1], "%d", &in1);
	sscanf(argv[2], "%d", &in2);
	
	liste * l1 = split(in1);
	liste * l2 = split(in2);	
	l1 = listTrie(l1);
	l2 = listTrie(l2);
	afficheListe(l1); printf("\n");
	afficheListe(l2); printf("\n");	
	return EXIT_SUCCESS;
}
