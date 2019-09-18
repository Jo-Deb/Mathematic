/* Fichier d'entête */

typedef struct table{
	int * tab;
	int taille;
} table;

extern table * createStruct(int taille);

extern table * additionLongue(table * elt1, table * elt2);

extern table * resize(table * to_resize);

extern int * addition_demesurer(int * arg1, int * arg2);