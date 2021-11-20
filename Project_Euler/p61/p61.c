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
		printf("\n  |\n");
		parcours = parcours->next;
	}
	printf(" /|\\\n");
}

list * genereList(int val, list * idx_fct_list){
	int n = getval61(val);
	int idx = getIdx61(val);
	int deuxPremierDigit = get2last(n);
	//Pour faire la boucle il faut uniquement incrémenter les listes
	list * tmp = idx_fct_list;
	list * res = NULL, * cur_list = NULL;
	printf("genereList: les indices de fonctions suivants seront essayés: ");
	afficheList(idx_fct_list); printf("\n");
	while(tmp != NULL){
		cur_list = gatherData(deuxPremierDigit, tmp->elt);
		if(cur_list == NULL){printf("genereList: cur_list est vide pour les tmp->elt = %d et deuxPremierDigit=%d\n", tmp->elt, deuxPremierDigit);} 
		res = concatList(res, cur_list); 
		tmp = tmp->l;
	}
	//suppression de l'idx dans la liste d'index de fonction
	printf("genereList: suppression de la valeur %d dans : ", idx);
	afficheList(idx_fct_list); printf("\n");
	idx_fct_list = supprimElt(idx_fct_list, idx);
	if(res == NULL){printf("genereList: la valeur retournée res est nulle\n");}
	return res;
}

/*
 * Ajouter une valeur et une liste générée à partir d'elle
 * Cet ajout sera fait en tête de la liste de résultat
 */
glist * ajoutDansRes(int val, list * racine, glist * res){
	int * pt = malloc(sizeof(int)); 
	*pt = val;
	res = g_ajoutTete(res, (void *)pt, racine);
	return res;
}

/*On suppose que la liste donnée en argument n'est pas vide. De plus
 * on retire la valeur de la liste en tête.
 */
int getNextVal(glist * res){
	glist * head = res;
	if(head->lst == NULL){
		res = g_supprimElt(res, head->elt);
		return getNextVal(res);
	}
	int result = 0;
	if ((result = head->lst->elt) > 1000){
		head->lst = supprimElt(head->lst, head->lst->elt);
		return result;
	} else {return result;}
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
		nextVal = getNextVal(res);
		printf("deRacineAsommet: go pour la valeur %d\n", nextVal);
		cur_list = genereList(nextVal, idx_fct_list);
		if(cur_list == NULL){printf("deRacineAsommet: liste nulle pour la valeur %d\n", nextVal);}
		if(cur_list != NULL){res = ajoutDansRes(nextVal, cur_list, res);}
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
		cur_list = genereList(val, idx_fct_list);
		if(cur_list != NULL){
			//appel d'une fonction qui va prendre cur_list et 
			//qui va essayer de remplir res
			deRacineAsommet(val, cur_list, res, idx_fct_list);
		}
	}
}

