#include<stdio.h>
#include<stdlib.h>
#include "liste.h"
#include "fonctionsPratiques.h"

int factoriel(int n){
    if (n==1 || n==0){ return 1;}
    else{return n*factoriel(n-1);}
}

void simplificationFactoriel(liste * num, liste * den){
    liste * t_num = num, * t_den = den;
    int tmp, arret;
    while(t_den!=NULL){
        tmp = t_den->value;
        t_num = num;
        arret = 0;
        while(t_num!=NULL && arret==0){
            if(t_num->value % tmp == 0){
                t_num->value = t_num->value/tmp;
                t_den->value = 1;
                arret = 1;
            }
            t_num = t_num->l;
        }
        t_den = t_den->l;
    }
}

long int produitList(liste * lst){
    liste * tmp = lst;
    long int res = 1;
    while(tmp!=NULL){
        res *= tmp->value;
        tmp = tmp->l;
    }
    return res;
}

long int calCombinaison(int n, int r){
    //r allant de 0 à n/2 ou (n-1)/2 en fonction de la parité, n-r sera toujours supérieur ou égal
    long int numerateur=1, denominateur;
    int j = n;
    liste * num = NULL, * den = NULL;
    while(j >= n-r+1){ num = ajoutEnTete(num, j); --j;}
    j = r;
    while(j>0){ den = ajoutEnTete(den, j); --j;}
    simplificationFactoriel(num, den);
    denominateur = produitList(den);
    numerateur = produitList(num);
    return numerateur / denominateur;
}

int main(){
    int n, r, limit, cpt = 0, arret;
    long int tmp;
    //test sur la factoriel
    for(n=3; n<=100; n++){
        arret = 0;
        if(n % 2 == 0){limit = n/2;}
        else {limit = (n-1)/2;}
        for(r=1; r<=limit && arret==0; r++){
            tmp = calCombinaison(n, r);
            if(tmp > 1000000){
                tmp = (limit - (r-1))*2;
                if(n%2==0){--tmp;}
                printf("combinaison(%d, %d), %ld valeurs au-dessus de 1,000,000\n", n, r, tmp);
                cpt += tmp;
                arret = 1;
            }
        }
    }
    printf("On dénombre %d combinaisons supérieures à 1,000,000\n", cpt);
    return 0;
}
