#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
//#include "Project_Euler/big_operation.h"

#define MAX 200000
long int CARRE[MAX];
long int S2[MAX-1];
long int S3[MAX-2];
int MANTISSE_SIZE = 20;

void fillCarre(){
    int i;
    for(i=0; i < MAX; ++i){CARRE[i] = (i+1)*(i+1);}
}

void faireLesSommes(){
    int i;
    for(i=0; i < (MAX-1); ++i){ S2[i] = (CARRE[i]+CARRE[i+1]); }
    for(i=0; i < (MAX-2); ++i){ S3[i] = (CARRE[i]+CARRE[i+1]+CARRE[i+2]); }
}

char * approximationBinaire(double x){
    int i;
    double estimation = 0;
    int taille_p = MANTISSE_SIZE + 3; //taille totale du tableau
    char * res = malloc(taille_p*sizeof(char));
    res[taille_p-1]='\0', res[0] = '0';
    for(i=0; i<=MANTISSE_SIZE; ++i){
        if(i==0){
            if(x - (estimation + 1/pow(2,i)) >= 0){ res[i]='1'; estimation += 1/pow(2,i); }
        }
        if(i==1) {res[1] = '.';}
        if(x - (estimation + 1/pow(2,i)) >= 0){
            res[i+1] = '1'; estimation += 1/pow(2, i);
        }
        else{ if(i >= 1){res[i+1] = '0';} }
    }
    return res;
}

double approximateValue(char * tab){
    int i, taille_p = MANTISSE_SIZE + 3; //taille totale du tableau
    double res = 0.0;
    for(i=0; i < taille_p-1; ++i){
        if(tab[i]=='1'&& i>1){ res += (1.0/pow(2,i-1)); }
        if(tab[i]=='1'&& i==0){ res += (1.0/pow(2,i)); }
    }
    return res;
}

char * decalage(char * tab, int d){
    int i = 0;
    int taille_p = MANTISSE_SIZE + 3; //taille totale du tableau
    char * res = malloc(taille_p*sizeof(char));
    for(i=0; i< taille_p - 1; ++i){res[i] = '0';}
    res[taille_p-1] = '\0', res[1] = '.';

    for(i=0; i< taille_p-2; ++i){
        //si i == 0, on fait +1 pour prendre en compte la cellule utilisée pour le .
        if(i==0 && (i+d+1)<=(taille_p-2)){res[i+d+1] = tab[0];}
        //si i == 1 on n'effectue aucune action
        if(i==1){}
        //traitement de la partie décimale qui peut être décalé.
        if(i>1 && (i+d)<=(taille_p-2)){res[i+d]=tab[i];}
    }
    return res;
}

char * soustractionBinaire(char * sup, char * inf){
    //On suppose qu'on est dans le cadre de l'exercice 25 sur les logs
    int i, taille_p = MANTISSE_SIZE + 3; //taille totale du tableau
    char ret = '0',* res = malloc(taille_p*sizeof(char));
    res[taille_p-1]='\0';
    for(i = 0; i < taille_p-1; ++i){ if(i==1){res[i]='.';}else{res[i]='0';} }
    for(i = taille_p-2; i >= 0; --i){
        //printf("step %d : sup = %s et inf = %s\n", i, sup, inf);
        if(i == 0 || i>1){
            //printf("sup[%d] = %c et inf[%d] = %c et ret = %c \n", i, sup[i], i, inf[i], ret);
            if(sup[i] == '1' && inf[i] == '0' && ret == '0') { res[i] = '1'; }
            if(sup[i] == '1' && inf[i] == '0' && ret == '1') { res[i] = '0'; ret = '0'; }
            if(sup[i] == '1' && inf[i] == '1' && ret == '0') { res[i] = '0'; }
            if(sup[i] == '1' && inf[i] == '1' && ret == '1') { res[i] = '1'; }
            if(sup[i] == '0' && inf[i] == '0' && ret == '0') { res[i] = '0'; }
            if(sup[i] == '0' && inf[i] == '0' && ret == '1') { res[i] = '1'; }
            if(sup[i] == '0' && inf[i] == '1' && ret == '1') { res[i] = '0'; ret = '1';}
            if(sup[i] == '0' && inf[i] == '1' && ret == '0') { res[i] = '1'; ret = '1';}
        } 
        //printf("res = %s\n", res);
    }
    return res;
}

int equal1(char * tab){
    int i; int taille_p = MANTISSE_SIZE + 3; //taille totale du tableau
    for(i=0; i<=taille_p-2; ++i){
        if(i==0 && tab[i] != '1'){return 0;}
        if(i>1 && tab[i] == '1'){return 0;}
    }
    return 1;
}

void computeLog10(char * X){
    int k = 1, num = 1, dimene = 0, deno = 1;
    char * Z = decalage(X, 1), * tmp = NULL, tab[255]={0x0};
    double apv = approximateValue(X), y = 0.0, arg_log = 1.0;
    tab[254] = '\0';
    while(equal1(X)!=1){
        do{
            tmp = soustractionBinaire(X,Z);
            if(tmp[0] == '0'){ Z = decalage(Z, 1); k++; }
        }while(tmp[0] == '0');
        X = soustractionBinaire(X, Z); Z = decalage(X, k);
        y += log10(pow(2, k)/(pow(2,k) - 1)); arg_log *=(pow(2, k)/(pow(2,k) - 1));
        num = pow(2, k), deno = num - 1;
        if(dimene == 0){dimene = sprintf(tab+dimene, "(%d/%d)", num, deno); } 
        else {dimene = sprintf(tab+dimene, "*(%d/%d)", num, deno);}
    }
    printf("valeur approchée de apv : %s\n", tab);
    printf("valeur approchée de apv : %lf\n", arg_log);
    printf("1/2^%d = %lf\n", MANTISSE_SIZE, 1.0/pow(2, MANTISSE_SIZE));
    printf("erreur entre arg_log et apv : %lf\n", apv - arg_log);
    printf("log10(arg_log) = %lf\n", y);
}

double calculLog10(char * X){
    int k = 1, num = 1, dimene = 0, deno = 1;
    char * Z = decalage(X, 1), * tmp = NULL, tab[255]={0x0};
    double apv = approximateValue(X), y = 0.0, arg_log = 1.0;
    tab[254]='\0';
    while(equal1(X)!=1){
        do{
            tmp = soustractionBinaire(X, Z);
            if(tmp[0] == '0'){Z = decalage(Z, 1); ++k;}
        }while(tmp[0] == '0');
        X = soustractionBinaire(X, Z); Z = decalage(X, k);
        y += log10(pow(2, k)/(pow(2,k) - 1)); arg_log *=(pow(2, k)/(pow(2,k) - 1));
        num = pow(2, k), deno = num - 1;
        if(dimene == 0){dimene = sprintf(tab+dimene, "(%d/%d)", num, deno); } 
        else {dimene = sprintf(tab+dimene, "*(%d/%d)", num, deno);}
    }
//    printf("valeur approchée après transformation binaire de l'entrée : %lf\n", apv);
//    printf("valeur pour laquelle le logarithme sera calculé: %lf\n", arg_log);
//    printf("log10(arg_log) = %lf\n", y);
    return y;
}

char * representationTouteValeur(double val){
    int i_val = (int) floor(val), i;
    double d_part = val - i_val;
    char * tab = malloc(42 * sizeof(char));
    tab[41] = '\0';    
    for(i=0; i<=40; ++i){ tab[i]='0';}
    tab[20] = '.';
    //Transformation de la partie entière en binaire
    int mutukwedi = 1; i = 0;
    while(i_val > 0){
        while(i_val > mutukwedi) {mutukwedi = mutukwedi << 1; ++i;}
        if(i_val == mutukwedi) {tab[19-i] = '1'; i_val-= mutukwedi;} 
        else{ mutukwedi = mutukwedi >> 1; --i; i_val -= mutukwedi; tab[19-i] = '1';}
        i = 0; mutukwedi = 1;
    }
    //Transformation de la partie décimale en binaire;
    double powerOfTwo = 0.0; i = 1;
    while(i <= 20){
        powerOfTwo = 1.0/pow(2, i);
        if(powerOfTwo <= d_part){ tab[20+i]='1'; d_part -= powerOfTwo;}
        ++i;
    }
   return tab;
}

double mutukwediBase10(char * input){
    int i;
    double res = 0.0;
    for(i = 0; i <= 40; i++){
        if(i < 20 && input[i]=='1'){res = res + pow(2, 19-i);}
        if(i > 20 && input[i]=='1'){res = res + 1.0/pow(2,i-20);}
    }
    return res;
}

void decaler(char * input, int decal){
    int i;
    for(i = 40 - decal; i >= 0; i--){
        if(i == 20){}
        else{
            if(i < 20 && i + decal >= 20){ input[i+decal+1] = input[i]; input[i] = '0'; }
            else{ input[i+decal] = input[i]; input[i] = '0';}
        }
    }
}

/*
int main(){
	double val = 1.0;
	char * tmp; int k = 1;
	while(k <= 10){
		val = 1.0 + (1/pow(2, k));
		printf("Log(1 + 1/2^%d) = %lf\n", k, log10(val));
		++k;
	}
	return 0;
}


int main(int argc, char ** argv){
    double val_input = 0.0;
    if(argc == 2){
        if(sscanf(argv[1], "%lf", &val_input) != EOF){}
        else {printf("Mauvais argument, donner un nombre en entrée \n"); return 1;}
    }
    char * tmp = representationTouteValeur(val_input);
    printf("la valeur en entrée s'écrit en base binaire : %s\n", tmp);
    printf("la valeur binaire, traduit en base 10, donne : %lf\n", mutukwediBase10(tmp) );
    decaler(tmp, 2);
    printf("Une division par 4 soit un décalage vers la droite donne : %s et la valeur est %lf\n", tmp, mutukwediBase10(tmp) );
}

*/
