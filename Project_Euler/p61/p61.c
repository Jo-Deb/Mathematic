#include <stdio.h>
#include <stdlib.h>
#include "genList.h"


int triangleNb(int n){
	if(n > 0) {return (n*(n+1))/2;}
	else {printf("triangleNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int squareNb(int n){
	if(n > 0) {return n*n;}
	else {printf("squareNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int pentagonalNb(int n){
	if(n > 0) {return n*(3*n-1)/2;}
	else {printf("pentagonalNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int hexagonalNb(int n){
	if(n > 0) {return n*(2*n-1);}
	else {printf("hexagonalNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int heptagonalNb(int n){
	if(n > 0) {return n*(5*n-3)/2;}
	else {printf("hexagonalNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int octagonalNb(int n){
	if(n > 0) {return n*(3*n-2);}
	else {printf("hexagonalNb: la valeur %d n'est pas correcte\n", n); return -1;}
}

int getFirst2(int n){return n / 100;}

int get2last(int n){return n - (n/100)*100;}

int (*tab_pf[6]) (int) = {triangleNb, squareNb, pentagonalNb, hexagonalNb, heptagonalNb, octagonalNb};

int getIdx61(int elt){ return elt%10; }

int getval61(int elt){ return elt/10; }

int testDichotomie(int n, int (*pf)(int)){
	int min = 10, max = 200, old_min=0, old_max=100, tmp, twoD;
	while(min != old_min){
		tmp = pf(min); twoD = getFirst2(tmp);
		if(twoD > n){
			old_min=min; old_max = max;
			max = min; 
			min = min/2;
		} 
		else {
			if(twoD == n && get2last(tmp)>=10) {return min;}
			old_min=min; min = min+(max-min)/2;
		}
	}
if(twoD!=n || get2last(tmp)<10){return 0;}
	return min;
}

int borneInfMin(int n, int dep, int (*pf)(int)){
	int tmp=dep, flag=0;
	while(flag==0){
		--tmp;
		if(getFirst2(pf(tmp))!=n){++tmp; flag=1;}
	}
	//printf("borneInfMin : dep=%d, n=%d\n", dep, n);
	return tmp;
}

list * listElt(int start, int n, int idx){
	list * l = NULL;
	int tmp = start, val;
	while(getFirst2(tab_pf[idx](tmp))==n && get2last(tab_pf[idx](tmp))>=10){
		val = tab_pf[idx](tmp)*10+idx; 
		l=ajoutFin(l, val); ++tmp;
	}
	return l;
}

//cette fonction doit être dûment testée
list * gatherData(int lastTwo, int fct_idx){
	int tmp;
	if((tmp=testDichotomie(lastTwo, tab_pf[fct_idx]))==0){return NULL;}
	else{
		int borneInf = borneInfMin(lastTwo, tmp, tab_pf[fct_idx]);
		list * l = listElt(borneInf, lastTwo, fct_idx);
		return l;
	}
	return NULL;
}

list * initListFunc(){
	int i; list * l = NULL;
	for(i=0; i < 6; i++){l=ajoutFin(l, i);}
	return l;
}

void afficheRacine(glist * res){
	glist * parcours = res;
	while(parcours != NULL){
		printf("%4d->[", *((int *)parcours->elt));
		afficheList(parcours->lst); printf("]");
		printf("\n  |");
        if(parcours!=NULL){printf("\tparcours:%p and parcours->elt : %p et parcours->next : %p\n", parcours, parcours->elt, parcours->next);}	
        else{printf("\n");}
		parcours = parcours->next;
    }
	printf(" /|\\\n");
}

/*
 * Générer la liste des idx qui ne doivent pas être testé lors
 * de la génération des listes
 */
list * idxToDelete(int value, glist * res){
	glist * parcours = res;
	list * idx_lst = NULL;
	int val = 0, idx = 0;
	idx_lst = ajoutFin(idx_lst, getIdx61(value));
	while(parcours != NULL){
		val = *((int *)parcours->elt);
		idx = getIdx61(val);
		idx_lst = ajoutFin(idx_lst, idx);
		parcours = parcours->next;
	}
	return idx_lst;
}


list * computeIdxList(list * lelt){
	list * tmp = initListFunc();
	list * parcours = lelt;
	while(parcours != NULL){
		tmp = supprimElt(tmp, parcours->elt);
		parcours = parcours->l;
	}
	return tmp;
}


list * genereList(int val, glist * res){
	list * lelt = idxToDelete(val, res);
	list * idxToTest = computeIdxList(lelt);
	printf("genereList: liste des indices : "); afficheList(idxToTest); printf("\n");
	int deuxPremierDigit = get2last(getval61(val));
	list * result = NULL, * cur_list = NULL, * tmp = idxToTest;
	while(tmp != NULL){
		cur_list = gatherData(deuxPremierDigit, tmp->elt);
		if(cur_list == NULL){printf("genereList: cur_list est vide pour les tmp->elt = %d et deuxPremierDigit=%d\n", tmp->elt, deuxPremierDigit);} 
		else{result = concatList(result, cur_list);} 
		tmp = tmp->l;
	}
	//suppression des listes qui ne seront pas retournées
	freeList(lelt); 
	freeList(idxToTest);
	if(result == NULL){printf("genereList: la valeur retournée res est nulle pour %d\n", getval61(val));}
	return result;
}

/*
 * Ajouter une valeur et une liste générée à partir d')elle
 * Cet ajout sera fait en tête de la liste de résultat
 */
glist * ajoutDansRes(int val, list * racine, glist * res){
    glist * head = (glist *) malloc(sizeof(glist));
    glist * tmp = res;
    head->elt = malloc(sizeof(int));
    *((int *)head->elt) = val;
    head->lst = racine;
    if(tmp==NULL){head->next = NULL;}else{head->next=tmp;}
	return head;
}

/* On suppose que la liste donnée en argument n'est pas vide. De plus
 * on retire la valeur de la liste en tête. Par conséquent cette fonction
 * aura deux objectifs, faire le ménage dans res et mettre à disposition 
 * la nouvelle valeur à partir de laquelle la construction de la liste se poursuit.
 * mettre à jour un entier pour lui assigner la valeur de tête de la liste générique
 * et retourner un pointeur qui sera le début de la liste générique, après que les
 * suppressions, si nécessaire, aient été faites.
 */
glist * getNextVal(glist * res, int flag, int headValue){
	if(res == NULL) {return 0;}
	if(res->lst == NULL){
        printf("getNextVal: valeur de res avant suppression: %p\n", res);
		res = g_supprimElt(res, res->elt);
        printf("getNextVal: valeur de res après suppression:%p\n", res);
		return getNextVal(res, 1, headValue);
	}
    if(flag==1){printf("getNextVal: valeur de res après appel récursif:%p\n", res);}
	if ((headValue = res->lst->elt) > 1000){
		res->lst = supprimElt(res->lst, res->lst->elt);
		return res;
	} else {headValue=0; return res;}
}


/*Afin de limiter la lourdeur des tests on appelle 
 * cette fonction si la liste racine n'est pas vide
 */
void deRacineAsommet(int val, list * racine, glist * res, list * idx_fct_list){
	int nextVal = 0;
	list * cur_list  = NULL;
	res = ajoutDansRes(val, racine, res);
	if(res == NULL){printf("deRacineAsommet: la liste générique res est nulle \n");}
	while(res != NULL && g_listLongueur(res) < 6){
		res = getNextVal(res, 0, nextVal);
        printf("deRacineAsommet: valeur de res après getNextVal:%p\n", res);
        afficheRacine(res);
		printf("deRacineAsommet: go pour la valeur %d\n", nextVal);
        printf("deRacineAsommet: res avant appel genereList :%p\n", res);
		cur_list = genereList(nextVal, res);
        printf("deRacineAsommet: res après appel genereList :%p\n", res);
		if(cur_list == NULL){printf("deRacineAsommet: liste nulle pour la valeur %d\n", nextVal);}
		if(cur_list != NULL){
            printf("deRacineAsommet: res avant appel ajoutDansRes :%p\n", res);
            res = ajoutDansRes(nextVal, cur_list, res);}
		afficheRacine(res);
	}
}

//Il faut écrire une fonction qui renvoie la liste
//selon les besoins de l'exercice mais l'entier donnée
//en entrée doit coder l'indice de la fonction dont il procède.

int main(){
	int i = 1, val = 0;
	list * idx_fct_list = NULL, * cur_list = NULL;
	glist * res = NULL;
//Test pour l'obtention des valeurs permises
	while( val < 10000){
		val = 0;
		while (val < 1000 || get2last(val) < 10) {val = triangleNb(i); ++i;}
		//arrivé à ce niveau, val est supposé avoir une valeur convenable pour
		//initier un run du programme, ne pas oublier que à cette valeur doit
		//être ajoutée l'index de fonction qui l'a généré
		val = val * 10 + 0; //car 0 est l'index de la fonction triangleNb
		printf("==============================================================\n");
		printf("main: Lancement d'un run avec la valeur %d\n", val);
		idx_fct_list = initListFunc();
		idx_fct_list = supprimElt(idx_fct_list, 0);
		cur_list = genereList(val, res);
		if(cur_list != NULL){
			//appel d'une fonction qui va prendre cur_list et 
			//qui va essayer de remplir res
			deRacineAsommet(val, cur_list, res, idx_fct_list);
		}
	}
}

