#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "liste.h"
#include "big_operation.h"

#define LI  long int
#define ULI unsigned long int
ULI CARRE[200000]; 
//int PREMIER[50000];
int PREMIER[100000], N_alpha, N;
LI  IDX_SQR = 0;

struct nombre_algebrique{
    int a;
    int b;
} typedef nbr_alg;

nbr_alg Alpha, Beta;

struct diophante_elt{
    int valeur;
    int next_square;
} typedef dio;

void fillCarre(){
    printf("début de fillCarre\n");
    int i;
    for(i=0; i<200000; ++i){ CARRE[i]=(i+1)*(i+1); }
    printf("fin de fillCarre\n");
}

void fillPremier(){
   int i = 0; ULI tmp = 0;
   FILE * fd = fopen("base_nbr_premiers.dat", "r");
   while(fscanf(fd, "%lu", &tmp)!=EOF && i < 100000){PREMIER[i]=tmp; ++i;}
}

liste * facteurPremier(int a){
    liste * res = NULL;
    int i, tmp = a;
    for(i=0; PREMIER[i] <= tmp; ++i){
        if( tmp % PREMIER[i] == 0 ){ res = ajoutEnTete(res, PREMIER[i]); tmp = tmp/PREMIER[i];}
    }
    return res;
}

int premierAvecFacteur(liste * l, int D){
    liste * tmp = l;
    while(tmp->l != NULL){
        if(D%tmp->value == 0){return 1;}
        tmp = tmp->l;
    }
    return 0;
}

//retourne a s'il est carré parmis les 100000 premiers carrés
long int estCarre(long int a){
    //printf("calcul pour %ld\n", a);
    long int prec = 0, next = 50000, old_next = 100000;
    int cpt = 0;
    while(next - prec > 1){
        while(CARRE[prec] < a && CARRE[next] > a && next - prec > 1){ 
            old_next = next;
            next -= (next - prec)/2;
            ++cpt;
            //printf("boucle while: prec = %ld et next = %ld, CARRE[prec] = %lu, CARRE[next] = %lu\n", prec, next, CARRE[prec], CARRE[next]);
        }
        if(CARRE[prec] < a && CARRE[next] < a){
            prec = next; next = old_next; 
            ++cpt;
            //printf("1er if: prec = %ld et next = %ld\n", prec, next);
        }
        if(CARRE[prec] == a || CARRE[next] == a){
            if (CARRE[prec] == a){ IDX_SQR = prec; }
            if (CARRE[next] == a){ IDX_SQR = next; }
            //printf("%d divisions\n", cpt); 
            return a; 
        }
    }
    //printf("%d divisions\n", cpt); 
    IDX_SQR = prec;
    return 0;
}

void facteurDeBezout(LI m, LI n, LI * res){
    LI a = 1, B = 1,  A = 0, b = 0, q = m/n, r = m % n, t, c = m, d = n;
    res[0] = A, res[1] = B;
    while(r > 0){
        t = a; a = A; A = t - (q*A);
        t = b; b = B; B = t - (q*B);
        c = d; d = r; q = c/d; r = c % d;
        res[0] = A; res[1] = B;
    }
}

int isSolution(dio D, LI X){
    liste * tmp = NULL; LI res[2]; //On met 3 car ce n'est pas un carré
    res[0] = 0; res[1] = 0; 
    tmp = facteurPremier(X);
    if(premierAvecFacteur(tmp, D.valeur) > 0){return 3;} //On retourne 3 car ce n'est pas une valeur carée
    facteurDeBezout(X, D.valeur, res);
    if(res[0]==1){ return res[1]; } else { return 3; }
}

int estSolution(int D, LI X_sqr, LI nterm){
    liste * res = facteurPremier(D);
    if(X_sqr - nterm == 1){
        afficheListe(res);
        if(premierAvecFacteur(res, X_sqr)){ return 0; } // n'est pas premier
        else { return 1; }
    }
    return 0;
}

LI treat_D(int D){
    dio prtd;
    if(estCarre(D) > 0){printf("D=%d est carré, pas de solution dans les entiers naturel\n", D); return 0;}
    if(CARRE[IDX_SQR] < D && CARRE[IDX_SQR+1] > D){ prtd.valeur = D; prtd.next_square = IDX_SQR;}
    else{ printf("un problème avec IDX_SQR=%ld pour D=%d\n", IDX_SQR, D); return 0; }
    
    LI Y_sqr = 3, X_sqr;
    while(estCarre(Y_sqr) == 0){
        prtd.next_square += 1;
        X_sqr = CARRE[prtd.next_square];
        Y_sqr = isSolution(prtd, X_sqr);
    }
    printf("X=%li, Y=%li, D=%d et X -DY=%li\n", X_sqr, Y_sqr, D, X_sqr - (D*Y_sqr));
    return Y_sqr;
}

//faire des fonctions qui permettent de calculer les alpha_i, les beta_i et les N_alphai

int nearestSqurare(){
    int min, tmp;
    if(estCarre(N) > 0){ printf("N = %d est carré\n", N); return 0;}
    else {
        min = abs((int)CARRE[IDX_SQR] - N);
        if(min > abs((int)CARRE[IDX_SQR+1] - N)){return IDX_SQR;} else {return IDX_SQR+1;}
    }
}

void calculNorme(){
    char * a = power(intToTab(Alpha.a), 2), * b = power(intToTab(Alpha.b), 2);
    char * c = bigSoustraction(*a, bigMultiplication(*b, intToTab(N)));
    
}

void next(alpha){

}

int main(int argc, char ** argv){
    fillCarre();
    fillPremier();
    printf("INT_MIN        = %+d\n", INT_MIN);
    printf("INT_MAX        = %+d\n", INT_MAX);
    printf("UINT_MAX       = %u\n\n", UINT_MAX);

    printf("LONG_MIN       = %+ld\n", LONG_MIN);
    printf("LONG_MAX       = %+ld\n", LONG_MAX);
    printf("ULONG_MAX      = %lu\n\n", ULONG_MAX);

    printf("LLONG_MIN      = %+lld\n", LLONG_MIN);
    printf("LLONG_MAX      = %+lld\n", LLONG_MAX);
    printf("ULLONG_MAX     = %llu\n\n", ULLONG_MAX);

    printf("la valeur carré la plus grande est : %lu\n", CARRE[199999]);
    printf("le premier le plus grande est : %d\n", PREMIER[99999]);
    LI nterm;
    int D, result,  Y_idc = 0, X_idc = 0, X_max = 0;

    for(D=2; D<=1000; ++D){
        printf("traitement pour D = %d\n", D);
        while( estCarre((LI)D) ){
            printf("%d est carré, on va l'incrémenter\n", D); ++D;
        }
        result = 0, Y_idc = -1;
        while(result != 1){
            ++Y_idc;
            nterm = D*CARRE[Y_idc];
            if(estCarre(nterm) == 0){
                X_idc = IDX_SQR + 1;
                //printf("test pour X_carre = %lu indice %d et Y_carre = %lu indice %d et D = %d et D*Y_carre = %lu\n"
               //        , CARRE[X_idc], X_idc, CARRE[Y_idc], Y_idc,  D, nterm);
            }
            else{ printf("il y a un problème avec D=%d, Y=%li, DY_carré=%li, X_carré=%li\n", D, CARRE[Y_idc], nterm, CARRE[X_idc]); 
                return 0;
            }
            result = estSolution(D, CARRE[X_idc], nterm);
        }
        if(result == 1 && X_max > CARRE[X_idc]){X_max = CARRE[X_idc];}
        printf("solution pour D=%d, X_carré=%li et Y_carré=%li\n", D, CARRE[X_idc], CARRE[Y_idc]);
    }
    return 0;
}

/*
int main(int argc, char** argv){
    LI m, n;
    if(argc == 3){
        if(sscanf(argv[1], "%li", &m) != EOF && sscanf(argv[2], "%li", &n) != EOF ){}
        else{ printf("Mauvais arguments, échec \n"); return 1; }
    }
    LI * res = malloc(2*sizeof(LI));
    facteurDeBezout(m, n, res);
    //fillCarre();
    long int i;
    //for(i=0; i <= 99999; ++i){printf("CARRE[%ld] = %ld\n", i, CARRE[i]);}
  
    for(i = 1; i<10000; ++i){
        printf(" %ld %ld\n", i, estCarre(i));
    }
  /
    printf("les facteurs de Bezout de m=%li et n=%li sont %li pour m et %li pour n\n", m, n, res[0], res[1]);
    return 0;
}
*/
