#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"
#include "liste.h"

int sameDigits(int val1, int val2){
    int tl1 = calculTailleEntier(val1), tl2 = calculTailleEntier(val2);
    int * tab1 = intToTab(val1);
    int * tab2 = intToTab(val2);
    triTab(tab1, tl1);
    triTab(tab2, tl2);
    int tmp1 = tabToInt(tab1, tl1);
    int tmp2 = tabToInt(tab2, tl2);
    free(tab1); free(tab2);
    if(tmp1 == tmp2) {return 1;} else {return 0;}
}

int permute (int * myDigit, int * myPos, int taille){
    int i, res=0, tmp;
    for(i=0; i<taille; i++){
        tmp = myPos[i];
        res = res * 10 + myDigit[tmp-1];
    }
    return res;
}

int regularite(liste * lst){
    lst = listTrie(lst);
    liste * tmp = lst;
    int len = taille(lst);
    int ecart = 0;
    if(len >= 2){ecart = tmp->l->value - tmp->value;}

    while(tmp->l!=NULL){
        if(ecart!=(tmp->l->value - tmp->value)){return 0;}
        tmp = tmp->l;
    }
    return 1;
}


int listEcart(liste * lst){
    lst = listTrie(lst);
    int nb_elt = taille(lst); 
    int nb_l = nb_elt*(nb_elt-1)/2, i=0, j, wrk[nb_l][3], cpt = 0;
    liste *it1=lst, *it2=it1, *tmp = NULL, *all_sort = NULL, *pcr = NULL;
    
    while(i < nb_l){
        while(it2!=NULL){
            wrk[i][0]= it2->value - it1->value; //ecart
            wrk[i][1]= it2->value; //sup
            wrk[i][2]= it1->value; //min
            it2 = it2->l; ++i;
        }
        it1 = it1->l;
        if(it1!=NULL){it2 = it1->l;}
        else {it2=it1;}
    }
    
    for(i=0; i<nb_l; i++){
        tmp=ajoutEnTete(tmp, i);
        for(j=i+1; j<nb_l; j++){ if(wrk[i][0] == wrk[j][0]){tmp = ajoutEnTete(tmp, j);} }
        //On élimine les doublons, trie et on voit si on obtient une suite arithmétique
        pcr = tmp;
        while(pcr != NULL){
            all_sort = ajoutEnTete(all_sort, wrk[pcr->value][1]);
            all_sort = ajoutEnTete(all_sort, wrk[pcr->value][2]);
            pcr = pcr->l;
        }
        supprimeListe(tmp); tmp=NULL; pcr = NULL;
        all_sort = supprimeDoublon(all_sort);
        all_sort = listTrie(all_sort);
        if(regularite(all_sort) > 0 && taille(all_sort) > 2){++cpt;}
        supprimeListe(all_sort); all_sort = NULL;
    }
    return cpt;
}


int howMany (int val){
    liste * lst = ajoutEnTete(NULL,val);
    int len = calculTailleEntier(val), depart = 0, i, decompte = 1, incr = 1, tmp;
    int * tab = malloc(len*sizeof(int));
    for(i=0; i<len; i++){tab[i]=len-i;}
    tmp = len;
    int * myDigit = intToTab(val);
    int  foo = permute(myDigit, tab, len);
    if(isPrime(foo)==1 && foo > 1000){lst = ajoutEnTete(lst, foo);}
    while(tmp > 1){decompte=decompte*tmp; --tmp;}
    while(incr < decompte){
        tmp = pppPandigital(tab, &depart, len);
        free(tab); tab = intToTab(tmp);
        foo = permute(myDigit, tab, len);
        if(isPrime(foo)==1 && foo > 1000){lst=ajoutEnTete(lst, foo);}
        ++incr;
    }
    lst = supprimeDoublon(lst);
    tmp = taille(lst);
    if(tmp>2 && listEcart(lst) > 0){
        printf("suite à %d membre:", tmp);
        afficheListe(lst);
        printf("\n");
        supprimeListe(lst);
        return tmp;
    }
    supprimeListe(lst);
    return 0;
}


int main(){
    int i, cpt, prec, act;
    liste * tmp=NULL;
    for(i=1000; i<9999; i++){
        if(isPrime(i)==1){
            cpt = 1; act = i+3330; prec = i;
            while(isPrime(act)==1 && sameDigits(act, prec)==1){
                if(cpt==1){printf("\nNouvelle tentative: %d %d", prec, act);}
                if(cpt > 1){printf(" %d", act);}
                prec = act;
                act = act + 3330;
                ++cpt;
            }
            if(howMany(i)==3){tmp = ajoutEnTete(tmp, i);}
        }
    }
    printf("Voici les éléments trouvés: ");
    liste * lst = NULL; lst = tmp;
    while(lst!=NULL){
        printf("%d ", lst->value);
        lst = lst->l;
    }
    return 0;
}
