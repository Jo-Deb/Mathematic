#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

struct fraction {
    int num;
    int deno;
};
typedef struct fraction fraction;

int cube(int n){
    if (n < 1 ) {printf("échec de la fonction %d est une valeur trop petite. Donnez une valeur positive et supérieure à 1\n", n);}
    if (n==1){return 1;}
    int start = n*(n-1)-1, k=0, res=0;
    for(k=1; k <=n; k++){res = res + (start + 2*k);}
    return res;
}

fraction * clcl_terme(int n){
    fraction * res = malloc(sizeof(fraction));
    int coef = 2*n+1;
    res->num = cube(coef);
    res->deno = res->num * coef + 4;
    if (n%2==0){ return res;} else { res->num = (-1)*res->num;}
    return res;
}

int carre (int n){
    int k = 1, res = 0;
    for(k=1; k <= n; k++){ res = res + 2*k-1;}
    return res;
}

int pgcd(int a, int b){
    int n = b, r = a%b;
    if(r==0) {return n;}
    return pgcd(n, r);
}

int denominateurCommun(int a, int b){
    int max, min;
    max = (a > b) ? a : b; // si a > b alors max = a sinon max = b
    min = (a < b) ? a : b;
    if(max % min == 0){ return max; }
    int d = pgcd(a, b), qa = a/d, qb = b/d;
    return (d * qa * qb); // On retourne le PPCM
}

void simplification(fraction * fr){
    int d = pgcd(fr->deno, fr->num);
    fr->num = fr->num / d;
    fr->deno = fr->deno / d;
}

void affiche_terme(fraction * fr){ printf("%d/%d ", fr->num, fr->deno); }

void affiche_somme(glist * lst){
    glist * tmp = lst; int cpt = 0;
    while(tmp != NULL){
        fraction * fr = (fraction *)(tmp->elt);
        if(cpt == 0){printf("(%d/%d) ", fr->num, fr->deno);}
        else { printf("+ (%d/%d) ", fr->num, fr->deno);}
        ++cpt; tmp = tmp->next;
    }
    printf("\n");
}

fraction * somme_de_2(fraction * fr, fraction * fr2){
    fraction * res = malloc(sizeof(fraction));
    int denoc = denominateurCommun(fr->deno, fr2->deno);
    int coef = denoc / fr->deno, coef2 = denoc / fr2->deno;
    res->num = (fr->num * coef) + (fr2->num * coef2);
    res->deno = denoc;
    simplification(res);
    return res;
}

fraction * somme(int n){
    glist * lst = NULL; int k = 0; fraction * tmp = NULL, * stmp = NULL;
    for(k = 0; k <= n; k++){
        tmp = clcl_terme(k);
        affiche_terme(tmp); 
        lst = g_ajoutTete(lst, (void *) tmp, NULL);
    }
    fraction * res = NULL; glist * pcr = lst; int cpt = 0;
    printf("\nla somme à calculer est : "); affiche_somme(lst);
    while(pcr != NULL){
        tmp = (fraction *)(pcr->elt);
        if(cpt == 0){ 
            stmp = (fraction*)(pcr->next->elt); 
            res = somme_de_2(tmp, stmp);
        } else { res = somme_de_2(res, tmp); }
        if(cpt == 0 ){ pcr = pcr->next->next;} else { pcr = pcr->next; }
        ++cpt;
    }
    printf("Le résultat de la somme est : "); affiche_terme(res); printf("\n");
    return res;
}

int main(){
    int k;
    for(k=1; k<=10; k++){
        printf("cube(%d) = %d\n", k, cube(k));
        //affiche_terme(clcl_terme(k));
        printf("\n");
        somme(k);
        printf("\n");
    }
    return 0;
}
