#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "genList.h"
#include "64structure.h"
#include "big_operation.h"

#define LI  long int
#define ULI unsigned long int
#define PRINT(pt) bigAffiche(pt); printf("\n");
ULI CARRE[200000]; 
//int PREMIER[50000];
int PREMIER[100000], N;
LI  IDX_SQR = 0, N_alpha;

struct nombre_algebrique{
    long a;
    long b;
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

list * facteurPremier(int a){
    list * res = NULL;
    int i, tmp = a;
    for(i=0; PREMIER[i] <= tmp; ++i){
        if( tmp % PREMIER[i] == 0 ){ res = ajoutFin(res, PREMIER[i]); tmp = tmp/PREMIER[i];}
    }
    return res;
}

int premierAvecFacteur(list * l, int D){
    list * tmp = l;
    while(tmp->l != NULL){
        if(D%tmp->elt == 0){return 1;}
        tmp = tmp->l;
    }
    return 0;
}

//retourne a s'il est carré parmis les 100000 premiers carrés
long int estCarre(long int a){
    long int prec = 0, next = 50000, old_next = 100000;
    int cpt = 0;
    while(next - prec > 1){
        while(CARRE[prec] < a && CARRE[next] > a && next - prec > 1){ 
            old_next = next;
            next -= (next - prec)/2;
            ++cpt;
        }
        if(CARRE[prec] < a && CARRE[next] < a){
            prec = next; next = old_next; 
            ++cpt;
        }
        if(CARRE[prec] == a || CARRE[next] == a){
            if (CARRE[prec] == a){ IDX_SQR = prec; }
            if (CARRE[next] == a){ IDX_SQR = next; }
            return a; 
        }
    }
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
    list * tmp = NULL; LI res[2]; //On met 3 car ce n'est pas un carré
    res[0] = 0; res[1] = 0; 
    tmp = facteurPremier(X);
    if(premierAvecFacteur(tmp, D.valeur) > 0){return 3;} //On retourne 3 car ce n'est pas une valeur carée
    facteurDeBezout(X, D.valeur, res);
    if(res[0]==1){ return res[1]; } else { return 3; }
}

int estSolution(int D, LI X_sqr, LI nterm){
    list * res = facteurPremier(D);
    if(X_sqr - nterm == 1){
        afficheList(res);
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
        if(min > abs((int)CARRE[IDX_SQR+1] - N)){return IDX_SQR+1;} else {return IDX_SQR;}
    }
}

void calculNorme(){
    char * a = power(longToTab(Alpha.a), 2), * b = power(longToTab(Alpha.b), 2);
    char * c = bigSoustraction(a, bigMultiplication(b, intToTab(N)));
    PRINT(c);
    N_alpha = (long) tabToInt(c);
}

int check_beta(int m, int * val){
	int tmp = abs(m*m -N);
	if(tmp < *val){*val = tmp; return 1;}
	return 0;
}

void calcule_beta(){
   int m=1, keep_going = 1, pm=0, n_beta_val = INT_MAX;
   long long tmp = tabToInt( 
                        bigSomme(intToTab(Alpha.a), 
                            bigMultiplication(intToTab(Alpha.b), intToTab(m)) 
                        ) 
                    );  
	while(tmp % labs(N_alpha) != 0 || keep_going){
		if(tmp % labs(N_alpha) == 0){
			keep_going = check_beta(m, &n_beta_val);
			if(keep_going == 1){pm = m;}
		}
		++m;
      tmp = tabToInt(   bigSomme(intToTab(Alpha.a), 
                            bigMultiplication(intToTab(Alpha.b), intToTab(m)) 
                        ) 
                    ); 
	}
//    while(tmp % N_alpha != 0){++m; tmp = Alpha.a + Alpha.b*m;} 
    Beta.a = pm; Beta.b = 1;
}

void next_alpha(){
    if(Alpha.a == 1 && Alpha.b == 0){
        Alpha.b = 1; Alpha.a = nearestSqurare() + 1; 
        calculNorme(); return; 
    }
    calcule_beta();
    long tmaa = Alpha.a, tmab = Alpha.b, tmba = Beta.a;
    long num = (long)(tabToInt(bigSomme(bigMultiplication(intToTab(tmaa), intToTab(tmba)), 
                                bigMultiplication(intToTab(tmab), intToTab(N)))));
    Alpha.a = num / labs(N_alpha);
    num = (long)(tabToInt(bigSomme(intToTab(tmaa), 
                                bigMultiplication(intToTab(tmab), intToTab(tmba)))));
    Alpha.b = num / labs(N_alpha);
    calculNorme();
}

int rechercheFractir(glist * l, fractir * fr){
    glist * tmp = l;
    while(tmp != NULL){
        if(egaliteFractir((fractir *)tmp->elt, fr)==0){return 1;}
        tmp = tmp->next;
    }
    return 0;
}

list * calculListeTerme(int d){
    glist * lst_reste = NULL; list * res = NULL;
    fractir * fr = createFractir(createIrrationnel(d,0), 1);
    fracB * fb = NULL;
    res = ajoutFin(res, partieEntiere(fr));
    do {
        lst_reste = g_ajoutTete(lst_reste, (void *)fr, NULL);
        //g_ajoutFin(lst_reste, (void *)fr, NULL);
        fb = nextFb(fr);
        fr = formePropre(fb);
        res = ajoutFin(res, partieEntiere(fr));
    } while(rechercheFractir(lst_reste, fr)==0);
    return res;
}

void calculreduites(list * termes){
    list * tmp = termes;
    unsigned long p0, q0=1, p_1=1, p_2=0, q_1=0, q_2=1;
    int idx = 0;
    while(tmp != NULL){
        p0 = tmp->elt*p_1 + p_2;
        q0 = q_1*tmp->elt + q_2;
        printf("le terme %d est %lu/%lu\n", idx, p0, q0);
        p_2 = p_1; p_1 = p0; 
        q_2 = q_1; q_1 = q0; 
        ++idx;
        tmp = tmp->l;
    }
    return;
}

void testCalulListeTerme(){
    int i; list * terme = NULL;
    for(i = 2; i <= 20; ++i){
        if(estCarre(i) > 0) {++i;}
        terme = calculListeTerme(i);
        printf("la liste des termes de %d est : ", i); afficheList(terme); printf("\n");
        freeList(terme);
        terme = NULL;
    }
}

char * searchSolution(list * terme, int d, char * x){
    list * tmp = terme;
    char * p_2 = intToTab(0), * p_1 = intToTab(1), * p0 = intToTab(tmp->elt);
    char *q_2 = intToTab(1), *q_1 = intToTab(0), *q0 = intToTab(1); 
    char * X = power(p0, 2), * Y = intToTab(1), * res = bigSoustraction(X, intToTab(d));
    bigAffiche(p0); printf("/"); bigAffiche(q0); printf("\n");
    tmp = tmp->l;
    while(labs(tabToInt(res))!=1 && tmp!= NULL){
        free(X); free(Y);
        X = NULL, Y = NULL;
        free(p_2); p_2 = NULL;  p_2 = copieTab(p_1); free(p_1); p_1 = NULL; p_1 = copieTab(p0); 
        free(p0); p0 = NULL; p0 = bigAddition(bigMultiplication(intToTab(tmp->elt), p_1), p_2);
        free(q_2); q_2 = NULL; q_2 = copieTab(q_1); free(q_1); q_1 = NULL; q_1 = copieTab(q0); 
        free(q0); q0 = NULL; q0 = bigAddition(bigMultiplication(intToTab(tmp->elt), q_1), q_2);
        X = power(p0, 2), Y = power(q0, 2);
        res = bigSoustraction(X, bigMultiplication(intToTab(d), Y));
        bigAffiche(p0); printf("/"); bigAffiche(q0); printf("\n");
        tmp = tmp->l;
    }
    if(tmp == NULL){printf("pas de solution pour %d\n", d);}
    long long n = tabToInt(res);
    printf("n est égale à %lld\n", n);
    if(n == -1){
        char * tp = copieTab(p0), *tq = copieTab(q0);
        p0 = bigAddition(power(tp,2), bigMultiplication(intToTab(d),tq));
        q0 = bigMultiplication(intToTab(2), bigMultiplication(tp,tq));
    }
    x = plusGrand(x, p0);
    printf(" la solution pour %d est X = ", d); bigAffiche(p0); printf(" et Y = "); bigAffiche(q0);
    printf("\n");
    return x; 
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
    list * res = NULL;
    char * x = intToTab(0);
    for(N = 2; N <= 1000; ++N){
        while(estCarre(N) > 0){++N;}
        printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
        res = calculListeTerme(N);
        calculreduites(res);
        printf("la liste des termes pour %d est : ", N); afficheList(res); printf("\n");
        x = searchSolution(res, N, x);
        printf("###############################################################\n");
    }
    printf("la valeur max de x est "); bigAffiche(x); printf("\n");
    for(N=337; N<=5; ++N){
        while(estCarre(N) > 0){++N;}
        Alpha.a = 1, Alpha.b = 0, Beta.a = 0, Beta.b = 1;
        N_alpha = LONG_MAX;
        printf("___________________calcul des suites pour N = %d____________________\n", N);
        while(labs(N_alpha) > 4 || labs(N_alpha) == 3){
            next_alpha();
            printf("Apha = %ld + %ld x sqrt(%d), Beta = %ld + sqrt(%d) et N_alpha = %ld\n", 
                    Alpha.a, Alpha.b, N, Beta.a, N, N_alpha);
        }
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
