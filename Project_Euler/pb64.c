#include <stdio.h>
#include <stdlib.h>
#include "64structure.h"
#include "genList.h"
#include "liste.h"

int pgcd(int A, int B){
    int r = 100, pg=0;
    while(r > 0){
        r = A%B;
        if(r == 0){pg=B; return pg;}
        else {A=B; B=r;}
    }
    return pg;
}

int nearestSquare(int a){
    int i = 1;
    while((i*i) <= a){i++;}
    --i;
    return i;
}

/*Si N est un carré entier alors on retourne 0 sinon la retournée est 
 * celle qu'aurait renvoyée nearestSquare */
int perfectSquare(int N){ int i = 2, tmp;
    if(i > N) {return 1;}
    tmp = i * i;
    while(tmp < N){ i++; tmp = i*i; if(tmp == N) {return 0;} }
    --i;
    return i;
}

int conjugue(irrationnel * irr){
    int racine = irr->racine;
    int suppl = abs(irr->suppl);
    return (racine - (suppl * suppl));
}

int isFormeBrute(fracB * elt){
    int num = elt->num;
    irrationnel * deno = elt->deno;
    if(deno->racine != 0 && num > 0 && deno->suppl != 0)
    {return 1;} else {return -1;}
}

fractir * formePropre(fracB * fbrut){
    if(isFormeBrute(fbrut) < 0){
        printf("l'argument de la fct n'est pas une forme brute\n");
        return NULL;
    }
    int vConjugue = conjugue(fbrut->deno);
    int Vn = fbrut->num;
    if(vConjugue%Vn > 0){
        printf("problème avec l'argument. %d ne divise pas %d\n", Vn, vConjugue);
        return NULL;
    }
    int Vv = vConjugue/Vn;
    fractir * res = createFractir(createIrrationnel(fbrut->deno->racine
                , -1*fbrut->deno->suppl), Vv);
    return res;
}

int partieEntiere(fractir * elt){
    int sqrt = elt->num->racine;
    int suppl = elt->num->suppl;
    int ns = nearestSquare(sqrt);
    if(elt->deno == 0){
        afficheFractir(elt);
        printf("\nla fractir en argument n'est pas correcte, le programme terminera en erreur \n");
    }
    int An = (ns + suppl)/elt->deno;
    if(An == 0){
        printf("problème sur cet élément. Le développement de sqrt(%d)\
                a échoué\n", sqrt);
        return -1;
    }
    elt->num->suppl = ((An * elt->deno) - elt->num->suppl) * -1;
    return An;
}

int compareReste(glist * lst, fractir * reste){
    if(lst == NULL){return 1;}
    
    glist * pcr = lst;
    while(pcr!=NULL){
        if(egaliteFractir((fractir *)(pcr->elt), reste)==0){return 0;}
        pcr=pcr->next;
    }
    return 1;
}

fracB * nextFb(fractir * fr){
    irrationnel * deno = createIrrationnel(fr->num->racine, fr->num->suppl);
    return createFracB(fr->deno, deno);
}

int checkAll(glist * lr, liste * tr, fractir * fp, int An){
    int taillePeriode = 0;
    if(compareReste(lr, fp) == 1) {return 0; /*Il faut encore développer la fraction continue*/}
    liste * pcr = tr;
    while(pcr!=NULL && taillePeriode==0){
        if(pcr->value == An){++taillePeriode;}
        pcr = pcr->l;
    }
    while(pcr!=NULL){
        ++taillePeriode;
        pcr = pcr->l;
    }
    return taillePeriode;
}

int main(){
    int i, crp, An = 0, fqr_len = 0, compteur = 0;
    glist * list_reste = NULL;
    liste * liste_terme = NULL;
    irrationnel * irra = NULL;
    fracB * fb = NULL;
    for (i=2; i < 10000; i++){
        while((crp = perfectSquare(i)) == 0 ) {++i;}
        irra = createIrrationnel(i, (-1)*crp);
        fb = createFracB(1, irra);
        fractir * fp = formePropre(fb);
        An = partieEntiere(fp); 
        printf("la valeur approchée de racine(%d) est en cours \n", i);
        while((fqr_len = checkAll(list_reste, liste_terme, fp, An)) == 0){
            list_reste = g_ajoutTete(list_reste, (void *)(fp), NULL);
            liste_terme = ajoutEnQueue(liste_terme, An);
            fp = formePropre(nextFb(fp));
            An = partieEntiere(fp);
        }
        printf("=============La fraction continue de %d est :=================\n", i);
        printf("La liste de reste a %d éléments\n", g_listLongueur(list_reste));
        g_afficheList(list_reste, showFractir);
        printf("la liste des termes est : %d (", crp);
        afficheListe(liste_terme); printf(")");
        printf("\nLa taille de la période : %d et le dernier terme est %d\n", fqr_len, An);
        if(fqr_len%2==1){++compteur;}
        printf("===============================================================\n");
        g_freeList(list_reste);
        supprimeListe(liste_terme);
        liste_terme = NULL;
        list_reste = NULL;
    }
    printf("Le nombre de fraction continue ayant une période impaire est %d\n", compteur); 
}

