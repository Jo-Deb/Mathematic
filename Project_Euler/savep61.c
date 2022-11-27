#include <stdio.h>
#include <stdlib.h>
#include "gestionList.h"
#include "arithmetique.h"
#include "pile.h"

int TAT[100]; 

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

int getIdx61(int elt){ return elt%10; }

int getval61(int elt){ return elt/10; }

void afficheList61(list *l){
	list * tmp = l;
	if(l == NULL){printf("afficheList61: liste vide\n"); return;}
	while(tmp!=NULL){
		if(tmp->l!=NULL){ printf("%d->", getval61(tmp->elt)); tmp = tmp->l; }
		else{ printf("%d\n", getval61(tmp->elt)); tmp = tmp->l; }
	}
}

int newGround(pile * p, list * l){
	list * tmp=l, * res = NULL;
	int ret = 0;
	if(p==NULL){ return 0;}
	while(res==NULL && p!=NULL){
		res = (list *)getHeadValue(p);
		if(res==NULL){
			p = depilePile(p);
			if(l!=NULL){l = deleteLastElts(l, 1);}
		}
	}
	if(res==NULL){return 0;}
	else{
		ret=res->elt;
		res = supprimElt(res, ret);
		return ret;
	}
	return 0;
}

/*
* Description de l'algo implémenté, un essai dans tous les cas
* 1 - prendre un nombre triangulaire, une pile vide et une liste vide et un indice de fonction indiquant l'indice du prochain calcul
* 2 - récupérer les deux derniers digits
* 3 - chercher tous les nombres de la fonction donnée en paramètre dont les deux premiers digits sont égaux aux deux derniers calculés plus haut.
*	 3.1 - Si la liste renvoyée est nulle on renvoie NULL, car la pile est initialement vide; 
*	le main s'occupera de faire un autre appel avec le nombre triangulaire suivant
*	3.2 Si la liste renvoyée contient des données:
*		3.2.1 - retirer le 1er élément de la liste
*		3.2.2 - mettre la liste tronquée dans la pile
*		3.2.3 - effectuer un appel récursif avec le nombre récupéré de la liste tronquée, la nouvelle pile enrichie de la liste et l'indice de la fonction incrémentée de 1
*/
list * batir(int polynomialNb, pile * p, list * l, int fct_idx){
	int poly_idx = getIdx61(polynomialNb), val = getval61(polynomialNb);
	printf("batir: nouvel appel avec polynomialNb=%d et val=%d\n", polynomialNb, val);
	if(listLongueur(l) >= 2){afficheList61(l);}
	if(listLongueur(l) == 6){return l;}

	if(val >=10000){printf("Le nombre %d est trop grand, la fonction s'arrête\n", polynomialNb); return NULL;}

	int lastTwo = get2last(val);
	list * res_list = gatherData(lastTwo, fct_idx);
	printf("affiche de la liste res_list :"); afficheList61(res_list);

	if(res_list==NULL && p==NULL){return NULL;}
	if(res_list==NULL && p!=NULL){
		l = supprimElt(l, polynomialNb);
		polynomialNb = newGround(p, l);
		printf("la nouvelle valeur pour polynomialNb: %d\n", polynomialNb);
		if(polynomialNb == 0){return NULL;}
		l=ajoutFin(l, polynomialNb);
		fct_idx=getIdx61(polynomialNb)+1;
		return batir(polynomialNb, p, l, fct_idx);
	}
	else{
		polynomialNb = res_list->elt;
		res_list = supprimElt(res_list, polynomialNb);
		p = empilePile(p, (void*)res_list); 
		l = ajoutFin(l, polynomialNb);
		fct_idx=getIdx61(polynomialNb)+1;
		return batir(polynomialNb, p, l, fct_idx);
	}
	return NULL;
}

int main(){
	int i=18, v, (*pf)(int) = squareNb, tmp, fTwo, lTwo, borneInf; 
	pile * contexte=NULL, * current=NULL;
	list * l = NULL;
	while((v=triangleNb(i))<10000){
		if(v<1000){++i;}
		else{
				v = v * 10 + 0;
				l = ajoutFin(l, v);
				printf("main: appel de la fonction batir\n");
				l = batir(v, contexte, l, 1);
				if(listLongueur(l)<6){
					freeList(l); detruirePile(contexte);
					l = NULL; contexte = NULL;
				}
			}
			i++;
		}
	printf("\n");
	return 0;
}
