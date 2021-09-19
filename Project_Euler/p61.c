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

list * initListFunc(){
	int i; list * l = NULL;
	for(i=0; i < 6; i++){l=ajoutFin(l, i);}
	return l;
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

pile * nbpile(int nb, list * index_fct){
	printf("nbpile: début de fonction avec %d\n", nb);
	int val = getval61(nb), idx = getIdx61(nb), tmp, seed = get2last(val), bi, i, * pti;
	afficheList(index_fct);
	index_fct = supprimElt(index_fct, idx);
	pile * p = NULL; list * lst = index_fct;
	pile * elt = NULL;
	while(lst != NULL){
		idx = lst->elt;
		tmp = testDichotomie(seed, tab_pf[idx]);
		if(tmp > 0){
			bi = borneInfMin(seed, tmp, tab_pf[idx]);
			for(i=bi; i<=tmp; i++){
				pti  = malloc(sizeof(int));
				*pti = tab_pf[idx](i) * 10 + idx;
				printf("la valeur %d sera rajoutée à la pile\n", *pti);
				p = empilePile(p, (void *)pti); 
			}	
		}
		lst = lst->l;
	}
	return p;
}

void afficheIntPile(pile * p){
	printf("afficheIntPile: début de fonction\n");
	pile * tmp = p;
	if(tmp == NULL){printf("la pile en entrée est nulle\n"); return;}
	while(tmp != NULL){
		if(tmp->back != NULL){printf("%d->", *((int*)(tmp->data)));}
		else {printf("%d\n", *((int*)(tmp->data)));}
		tmp = tmp->back;
	}
}

void afficheContexte(pile * ctx){
	pile * iter = ctx;
	while(iter != NULL){
		afficheIntPile(iter->data);
		printf("|\n");printf("|\n");
		iter = iter->back;
	}
}

void debbug61(list * res, pile * ctx, int val, list * idx_fct){
	printf("=======================================================\n");
	printf("Affiche de la liste de nombre : "); afficheList61(res);
	printf("Affiche de la pile de contexte ");
	if(ctx != NULL){afficheContexte(ctx);}
	/*
	while(tmp!=NULL){
		afficheIntPile((pile*)tmp->data);
		printf("====>");
		tmp = tmp->back;
	}
	*/
	printf("\n");
	printf("la valeur donnée est %d et idx=%d\n", getval61(val), getIdx61(val));
	printf("Affiche de la liste de fonction "); afficheList(idx_fct);
}

int findNextVal(pile * ctx, list * idx_fct, list * res){
	pile * tmp; int val, idx;
	tmp = (pile *)getHeadValue(ctx);
	while(tmp==NULL && ctx!=NULL){
		ctx = depilePile(ctx);
		val = getLastElt(res);
		idx = getIdx61(val);
		idx_fct = supprimElt(idx_fct, idx);
		res = supprimElt(res,val);
		tmp = (pile *)getHeadValue(ctx);
	}
	if(tmp == NULL){return -1;}
	else{
		while((val=*((int*)getHeadValue(tmp)))<1000){tmp = depilePile(tmp);}
		return val;
	}
}

void evolListPile(int pNb, pile * ctx, list * res, list * idx_fct){
	printf("evolListPile: appel avec %d\n", pNb);
	int val = getval61(pNb), idx = getIdx61(pNb), next = 0;
	pile * tmp=NULL, * ptmp = NULL; 
	if(ctx!=NULL){ptmp = (pile *)getHeadValue(ctx);}
	/*calcul de la pile de nombre qui peut être générée par pNb*/	
	idx_fct = supprimElt(idx_fct, idx);
	tmp = nbpile(pNb, idx_fct);
	debbug61(res, ctx, pNb, idx_fct);
	
	if(ctx == NULL){
		if(tmp == NULL){idx_fct = ajoutFin(idx_fct, idx); return;}
		res = ajoutFin(res, pNb);
		next = *((int*)getHeadValue(tmp));
		tmp = depilePile(tmp);
		if(tmp!=NULL){ctx = empilePile(ctx, (void*)tmp);}
		return evolListPile(next, ctx, res, idx_fct);
	}
	else{
		if(tmp!=NULL){
			res = ajoutFin(res, pNb);
			next = *((int*)getHeadValue(tmp));
			tmp = depilePile(tmp);
			if(tmp!=NULL){ctx = empilePile(ctx, (void*)tmp);}
			return evolListPile(next, ctx, res, idx_fct);
		}	
		else{
			if(ptmp == NULL){
				next = findNextVal(ctx, idx_fct, res);
				printf("appel de findNextVal, la valeur retournée est : %d\n", next);
				if(next < 0){return;} else {return evolListPile(next, ctx, res, idx_fct);}	
			}
			else {
				next = *((int *)getHeadValue(ptmp));
				if(next > 1000){
					ptmp = depilePile(ptmp);
					return evolListPile(next, ctx, res, idx_fct);
				}
				else{ return ; }
			}
		}
	}	
}

int main(){
	int i=18, v, (*pf)(int) = squareNb, tmp, fTwo, lTwo, borneInf; 
	pile * contexte=NULL, * current=NULL;
	list * l=NULL, * idx_fct = NULL, *bd_work = NULL;
	while((v=triangleNb(i))<10000){
		if(v<1000){++i;}
		else{
				v = v * 10 + 0;
				l = NULL;
				contexte = NULL;
				idx_fct = initListFunc();
				printf("main: appel de evolListPile avec %d \n", v);
				evolListPile(v, contexte, l, idx_fct);
				if(listLongueur(l)<6){freeList(l); detruirePile(contexte);}
			}
			i++;
		}
	printf("\n");
	return 0;
}
