#include <stdio.h>

typedef struct number{
    char * ipar;
    char * mpar;
} number;

extern void bigAffiche(char * a); 

extern long long tabToInt(char * a); 

extern char * int_To_Tab(int a);

extern char * longToTab(long a);

extern char * copieTab(char * a);

extern int estNegatif(char * a);

extern char * plusGrand(char * a, char * b);

extern char * bigSomme(char * a, char *b);

extern char * bigAddition(char * a, char *b);

extern char * bigMultiplication(char * a, char *b);

extern int sommePositifChriffe(char * a);

extern char * rendNegatif(char * a);

extern char * bigSoustraction(char * a1, char * b1);

extern void triTab(char * a);

extern void inverseTri(char *a);

extern int debutPermutation(char *a);

extern void sortSubString(char *a, int place);

extern void findAndPlacePivot(char *a, int place);

extern char * plusGrandeValeur(char * a);

extern int egalite(char *a, char *b);

extern void permuteValeurSuperieur(char *a, char * max);

extern char * incremente(char * a);

extern char * division(char * a, char * b);

extern char * power(char * b, int c);

extern int estDivisible(char * m, char * d);

extern char * quotient(char * m, char * div);

extern char * reste(char * a, char * b);

extern int determinePuissance(char * nbr, char * tmp);

extern int tailleChaine(char * a);

extern int how_many_dec(double r);
