/* Fichier d'entête */

typedef struct table{
	int * tab;
	int taille;
} table;

extern table * createStruct(int taille);

extern table * additionLongue(table * elt1, table * elt2);

extern table * resize(table * to_resize);

extern int * addition_demesurer(int * arg1, int * arg2);

extern int calculTailleEntier(int val);

extern int l_calculTailleEntier(unsigned long int val);

extern  int * intToTab(int val);

extern  int * l_intToTab(unsigned long val);

extern int isPrime(int val);

extern int tabToInt(int * tab, int taille);

extern unsigned long int l_tabToInt(int * tab, int taille);

extern void triTab(int * tab, int taille);

extern void triSousTab(int * tab, int taille,  int start);

extern void inverseTriTab(int * tab, int taille);

extern void inverseTriSousTab(int * tab, int taille,  int start);

extern int estCroissant(int * tab, int depart, int taille);

extern int estDecroissant(int * tab, int depart, int taille);

extern int getPositionMin(int * tab, int  depart, int taille);

extern void invert(int * tab, int taille1, int taille2);

extern int positionPivot(int * tab, int depart, int taille);

extern int positionPivot2(int * tab, int taille);

extern int plusPetitMajorant(int * tab, int val, int depart, int taille);

/*chercher le Plus Grand Nombre Inférieur à tab[depart-1]*/
extern int positionPgnf(int * tab, int depart, int taille);

extern int sousTabtoInt(int * tab, int depart, int taille);

extern unsigned long int l_sousTabtoInt(int * tab, int depart, int taille);

extern int pppPandigital(int * tab, int * depart, int taille);

extern int nextGreaterValSameDigit(int val);

extern int * generatePrimes();
/*supprimer les doublons*/
extern void supprimeDoublon(int * tab, int taille, int sub);

extern int factoriel(int n);

extern int getMax(int * tab, int len);

extern char * concatString(char ** tab, int tailleTab);

extern char * intToString(int n);

extern int isPresent(int * tab, int len, int e);
