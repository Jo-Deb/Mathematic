#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

/*typedef struct tableau{
	int * tab;
	int taille;
} table;
*/

/*Cette méthode de conversion implémente l'algorithme d'Euclide*/

int calculTailleEntier(int val){
	int taille = 0, reste = 0, tmp = val;
	while(tmp > 0){
		reste = tmp % 10;
		tmp = tmp/10;
		++taille;
	}
	return taille;
}

int l_calculTailleEntier(unsigned long int val){
	int taille = 0, reste = 0; 
    unsigned long int tmp = val;
	while(tmp > 0){
		reste = tmp % 10;
		tmp = tmp/10;
		++taille;
	}
	return taille;
}

int * intToTab(int val){
	int taille = calculTailleEntier(val);
	int * res = malloc(taille * sizeof(int)); 
	int i, tmp = val;
	for(i=taille-1; i>=0; i--){ res[i] = tmp % 10; tmp = tmp/10;}
	return res;
}

int * l_intToTab(unsigned long val){
	int taille = calculTailleEntier(val);
	int * res = malloc(taille * sizeof(int)); 
	int i, tmp = val;
	for(i=taille-1; i>=0; i--){ res[i] = tmp % 10; tmp = tmp/10;}
	return res;
}

 table * createStruct(int taille){
 	table * ptr = malloc(sizeof(table));
 	ptr->tab = malloc(sizeof(int)*taille);
 	ptr->taille = taille;
 	return ptr;
 }

 table * additionLongue(table * elt1, table * elt2){
 	int max, min, taille, tmp; 
 	int retenu = 0;
 	int * pelt1 = elt1->tab; int *pelt2 = elt2->tab;
 	int taille1 = elt1->taille; int taille2 = elt2->taille;
	if( taille1 > taille2 ){ max = taille1; min = taille2;}
 	else{ max = taille2; min = taille1;}
 	taille = max + 1;
	table * result = createStruct(taille);
	int * tResult = result->tab;

 	for(int i = 0; i <= max; i++){
 		while(i < min){
 			tmp = pelt1[taille1 - (i+1)] + pelt2[taille2 - (i+1)] + retenu;
 			if(tmp >= 10){ tResult[taille - (i+1)] = tmp % 10; retenu = 1;}
 			else { tResult[taille - (i+1)] = tmp; retenu = 0;}
 			++i;
 		}
 		while(i < max){
 			if( max == taille1){ tmp = pelt1[taille1 - (i+1)] + retenu; }
 			else { tmp = pelt2[taille2 - (i+1)] + retenu; }
 			if(tmp >= 10){ tResult[taille - (i+1)] = tmp % 10; retenu = 1;}
 			else { tResult[taille - (i+1)] = tmp; retenu = 0;}
 			++i;
 		}
 		if(i == max) {tResult[taille - (i+1)] = retenu;}
 	}
 	return resize(result);
 }

table * resize(table * to_resize){
	int taille = to_resize->taille;
	int * tab = to_resize->tab;
	int i = 0;

	while(tab[i]==0){--taille; ++i;}
	table * result = createStruct(taille);
	for(int j = i; j < to_resize->taille; j++){result->tab[j-i] = tab[j];}
	free(to_resize);
	return result;
}

int * addition_demesurer(int * elt1, int * elt2){
	int taille = 0, taille1 = 0, taille2 = 0, i = 0, tmp, retenu = 0;
	
	while(elt1[i] != '\0'){ if(elt1[i] != '#') {taille1++; } i++; }
	i = 0; int min, max;
	while(elt2[i] != '\0'){ if(elt2[i] != '#') {taille2++; } i++; }
	if(taille1 > taille2){ max = taille1; min = taille2;}
	else{ max = taille2; min = taille1;}
	taille = max + 2;
	int * result = malloc(sizeof(int)*taille);

	printf("debut de la boucle de d'addition\n");

	for(int i = 0; i < taille; i++){
		printf("taille - (i+1) = %d\n", taille - (i+1));
		printf("taille1 - (i+1) = %d\n", taille - (i+1));
		printf("taille2 - (i+1) = %d\n", taille - (i+1));
		if(i == 0){ result[taille - (i+1)] = '\0';}
		if(i > 0 && i <= min - 1){
			tmp = elt1[taille1 - (i+1)] + elt2[taille2 - (i+1)];
			if(tmp+retenu >= 10){ result[taille - (i+1)] = (tmp + retenu) % 10; retenu = 1; }
			else{ result[taille - (i+1)] = tmp + retenu; retenu = 0;}
			printf("On boucle dans la somme\n");	
		}
		if( i > 0 && i > min - 1){
			if( i < max - 1){
				printf("On boucle dans la somme\n");
				if( max == taille1){ result[taille - (i+1)] = elt1[taille1 - (i+1)] + retenu; retenu = 0;}
				if( max == taille2){ result[taille - (i+1)] = elt2[taille2 - (i+1)] + retenu; retenu = 0;}
			}
			else{ if(retenu > 0){result[taille - (i+1)] = retenu; retenu = 0;}
				  else{ printf("La boucle d'addition est fini;"); result[taille - (i+1)] = '#'; }
			}
		}
	}
	printf("Début de l'affichage du résultat\n");
	for (int i = 0; i < taille; i++) { printf("%d", result[i]); }
	printf("\n");
	return result;
}

int isPrime(int val){
	if(val == 1){return 0;}
	if(val == 2){return 1;}
	int limite = 2;
	while (limite * limite <= val){
		if(val % limite == 0){ return 0;}
		++limite;
	}
	return 1;
}

int tabToInt(int * tab, int taille){
	int res = 0, i;
	for(i=0; i<taille; i++){ res = res * 10 + tab[i]; }
	return res;
}

unsigned long int l_tabToInt(int * tab, int taille){
	unsigned long res = 0;
    int i;
    //for(i=0; i<taille; i++){printf("%d ", tab[i]);}
	for(i=0; i<taille; i++){ res = res * 10 + tab[i]; }
    //printf(" res = %lu\n", res);
	return res;
}

/*Il s'agit d'un tri croissant */
void triTab(int * tab, int taille){
	int i, j, tmp;
	for(i=0; i<taille-1; i++){
		for(j=i+1; j<taille; j++){
			if(tab[i]>tab[j]){ 
				tmp=tab[i];
				tab[i]=tab[j];
				tab[j]=tmp; 
			}
		}
	}
}

/*Il s'agit d'un tri croissant */
void triSousTab(int * tab, int taille, int start){
	int i, tmp, j;
	for(i=start; i<taille-1; i++){
		for(j=i+1; j<taille; j++){
			if(tab[i]>tab[j]){tmp=tab[i]; tab[i]=tab[j]; tab[j]=tmp;}
		}
	}
}

/*Il s'agit d'un tri décroissant */
void inverseTriTab(int * tab, int taille){
	int i, j, tmp;
	for(i=0; i<taille-1; i++){
		for(j=i+1; j<taille; j++){
			if(tab[i]<tab[j]){ 
				tmp=tab[i];
				tab[i]=tab[j];
				tab[j]=tmp; 
			}
		}
	}
}

/*Il s'agit d'un tri décroissant */
void inverseTriSousTab(int * tab, int taille, int start){
	int i, tmp, j;
	for(i=start; i<taille-1; i++){
		for(j=i+1; j<taille; j++){
			if(tab[i]<tab[j]){tmp=tab[i]; tab[i]=tab[j]; tab[j]=tmp;}
		}
	}
}

int estCroissant(int * tab, int depart, int taille){
    int i, croit = 1;
    for(i=depart+1; i<taille; ++i){ if(tab[i-1] > tab[i]){croit=0;} }
    return croit;
}

int estDecroissant(int * tab, int depart, int taille){
    int i, decroit = 1;
    for(i=depart+1; i< taille; ++i){ if(tab[i-1] < tab[i]){decroit=0;} }
    return decroit;
}

int getMinTab(int * tab, int depart, int taille){
	int i, pos=depart;
	for(i=depart; i<taille; i++){
		if(tab[i]<tab[pos]){ pos = i;}
	}
	return pos;
}

void invert(int * tab, int taille1, int taille2){
	int tmp;
	tmp = tab[taille1]; 
	tab[taille1]=tab[taille2];
	tab[taille2]=tmp;
}

int positionPivot(int * tab, int depart, int taille){
	int i, posPivot = depart;
	for(i=depart; i<taille-1; i++){ 
		if(tab[i]<tab[i+1] && tab[i] < tab[posPivot]){posPivot = i;} 
	}
	if(posPivot==0){return taille-1;}
	return posPivot;
}

int positionPivot2(int * tab, int taille){
    int i, posPivot = -1;
    for(i=1; i < taille-1; ++i){
        if(tab[i-1] < tab[i] && tab[i] > tab[i+1]){ posPivot = i; }
        if(tab[i-1] > tab[i] && tab[i] < tab[i+1]){ posPivot = i; }
    }
    return posPivot;
}

int plusPetitMajorant(int * tab, int val, int depart, int taille){
   int i, tmaj = 0;
   for(i=depart; i < taille; ++i){
       if(tab[i] > val && tmaj == 0){tmaj = i; }
       if(tab[i] > val && tab[i] < tab[tmaj]){tmaj = i; }
   }
   return tmaj;
}

int getPositionMin(int * tab, int start, int taille){
	int i, min=start;
	for(i=start; i<taille; i++){
		if(tab[i] < tab[min]){ min = i;}
	}
	return min;
}

/*chercher le Plus Grand Nombre Inférieur à tab[depart-1]*/
int positionPgnf(int * tab, int depart, int taille){
	int etalon=depart-1, res=depart, i;
	for(i=depart; i<taille; i++){ if(tab[i] > tab[res] && tab[i] < tab[etalon]){res=i;} }
	if(tab[res]>=tab[etalon]){ return -1; }
	return res;
}

int sousTabtoInt(int * tab, int depart, int taille){
    int i, res = 0;
    for(i=depart; i<taille; i++){ res = res*10+tab[i];}
    return res;
}

unsigned long int l_sousTabtoInt(int * tab, int depart, int taille){
    int i;
    unsigned long res = 0;
    for(i=depart; i<taille; i++){ res = res*10+tab[i];}
    return res;
}

int pppPandigital(int * tab, int * depart, int taille){
	int i, positionMin = getPositionMin(tab, *depart, taille);
	if(positionMin == taille-1){ 
		invert(tab, taille-2, taille-1);
		if(taille - *depart == 2){ --(*depart);}
		return tabToInt(tab, taille);
	}
	if((taille - *depart)==2){
		triSousTab(tab, taille, *depart); 
		--(*depart);
		return tabToInt(tab, taille);
	}
	int posPivot = positionPivot(tab, *depart, taille);
	int posPgnf = positionPgnf(tab, posPivot, taille);
	if(posPgnf==-1){ --(*depart); return pppPandigital(tab, depart, taille);}
	invert(tab, posPivot-1, posPgnf);
	inverseTriSousTab(tab, taille, posPivot);
	*depart = posPivot;
	return tabToInt(tab,taille);
}

int nextGreaterValSameDigit(int val){
    int res = 0;
    int * tab = intToTab(val), tabLen = calculTailleEntier(val);
    if(estDecroissant(tab, 0, tabLen) == 1) {return val;}
    if(estCroissant(tab, 0, tabLen) == 1){
        invert(tab, tabLen-1, tabLen-2);
        res = tabToInt(tab, tabLen); free(tab);
        return res;
    }
    int posPivot = positionPivot2(tab, tabLen), depart, swtch, ppm;
    if(tab[posPivot-1] < tab[posPivot] && tab[posPivot+1] < tab[posPivot]){
        depart = posPivot; swtch = posPivot-1; 
        ppm = plusPetitMajorant(tab, tab[swtch], depart, tabLen);
        invert(tab, swtch, ppm);
        triSousTab(tab, tabLen, depart);
        res = tabToInt(tab, tabLen); free(tab);
        return res;
    }
    if(tab[posPivot-1] > tab[posPivot] && tab[posPivot+1] > tab[posPivot]){
        invert(tab, tabLen-1, tabLen-2);
    }
    res = tabToInt(tab, tabLen); free(tab);
    return res;
}

int * generatePrimes(){
    int * tab = malloc(10000 * sizeof(int));
    int i=2, tmp=5;
    tab[0] = 2; tab[1]=3;
    while(i<10000){
        if(isPrime(tmp)==1){tab[i]=tmp; ++i;}
        tmp += 2;
    }
    return tab;
}

void supprimeDoublon(int * tab, int taille, int sub){
    int i;
    triTab(tab, taille);
    for(i=0; i<taille; ++i){ if(tab[i+1]==tab[i]){tab[i]=sub;} }
    triTab(tab, taille);
}

int factoriel(int n){
    if (n==1 || n==0){ return 1;}
    else{return n*factoriel(n-1);}
}

int getMax(int * tab, int len){
    int i, max=tab[0];
    for(i=0; i<len; i++){if(tab[i]>max){max=tab[i];}}
    return max;
}

char * concatString(char ** tab, int tailleTab){
    int i, lres = 0, j, k=0;
    //calcul de la longueur de la chaine finale.
    for(i = 0; i < tailleTab; i++){
        j = 0;
        while(tab[i][j] != '\0'){++lres; ++j;}
    }
    char * res = malloc((lres+1)*sizeof(char));
    res[lres]='\0';
    for(i = 0; i < tailleTab; i++){
        j = 0;
        while(tab[i][j] != '\0'){res[k]=tab[i][j]; ++j; ++k;}
    } 
    return res;
}

char * intToString(int n){
    int t = calculTailleEntier(n), tmp = n, k = 1;
    char * res = malloc(sizeof(char)*(t+1));
    res[t] = '\0';
    while(tmp > 0){ res[t-k]=(tmp%10)+48; tmp = tmp/10; ++k; } 
    return res;
}

/*
*si e est dans tab retourne 1 sinon 0
*/
int isPresent(int * tab, int len, int e){
	int i = 0;
	for(i=0; i<len; ++i){ if(tab[i] == e) {return 1;} }
	return 0;
}
