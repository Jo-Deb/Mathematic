#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "fonctionsPratiques.h"

float determineDiago(int in){
    int taille=2*in-1, liste[taille], i, pas=2, som=0, j, idx=1;
    for(i=0; i<taille; i++){liste[i]=0;}
    liste[0]=1;
    for(i=1; i<=in && idx<taille; i+=2){
       for(j=0; j<4; j++){liste[idx+j]=liste[idx+j-1]+pas;}
       idx+=4;
       pas+=2;
    }
    //for(i=0; i<taille; i++){printf("%d ", liste[i]);}
    for(i=0; i<taille; i++){ 
        if(isPrime(liste[i])>0){++som;}
    }
    return ((float)som/(float)taille)*100;
}

float determineLimit(){
    float res=300;
    int som=0, pas=2, imp=3, tmp=1, i, nbr_elt;
    while(res>=10.0){
        for(i=0; i<4; i++){
            tmp+=pas;
            if(isPrime(tmp)>0){++som;}
        }
        nbr_elt=2*imp-1;
        res=((float)som/(float)nbr_elt*100);
        printf("pour coté du carré %d et taux de premier %2.3f\n", imp, res);
        pas+=2; imp+=2;
    }
    printf("la première valeur pour laquelle res<10 %d et res vaut %2.3f\n", imp, res);
    return res;
}

float traceSpirale(int in){
   int tab[in][in], i, j, cpt = in*in;
   int l, c, pivot=in-1, pos;

   for(i=0; i<in; i++){
       for(j=0; j<in; j++){ tab[i][j]=0;}
   }
   for(i=pivot; i>=0; i--){
       pos=(pivot-i)/2;
       if(i%2==0){
           //traitement ligne
           for(l=pivot-pos; l>=pos; l--){tab[i+pos][l]=cpt; --cpt;}
           //traitement colonne
           for(c=i-1+pos; c>=pos; c--){tab[c][pivot-i-pos]=cpt; --cpt;}
       }
       if(i%2==1){
           //traitement ligne
           for(l=pivot-i-pos; l<=pivot-pos; l++){tab[pos][l]=cpt; --cpt;}
           //traitement colonne
           for(c=pos+1; c<=i+pos; ++c){tab[c][pivot-pos]=cpt; --cpt;}
       }
   }

   for(i=0; i<in; i++){
       printf("\n");
       for(j=0; j<in; j++){ printf("%5d ", tab[i][j]); }
   }
   printf("\n\n");
   cpt = 0;
   printf("calcul du taux de premier sur les diagonales: ");
   for(i=0; i<in; i++){
       printf("%d ", tab[i][i]);
       if(isPrime(tab[i][i])>0){++cpt;}
       printf("%d ", tab[i][pivot-i]);
       if(isPrime(tab[i][pivot-i])>0){++cpt;}
   }
   printf("\nLe taux de nombres premiers sur les diagonales est : %2.3f\n", ((float)cpt/(2.0*in-1))*100);
   printf("Voici les diagonales trouvées par calcul: ");
   printf(" et le taux de premier est : %2.3f\n", determineDiago(in));
   return ((float)cpt/(2.0*in-1))*100;
}

int main(){
    int dep = 9;
    float res;
    determineLimit();
    //while((res=traceSpirale(dep))>=10.0){dep+=2; printf("dep=%d\n", dep);}
    //while((res=determineDiago(dep))>=10.0){dep+=2; printf("dep=%d et taux=%2.3f\n", dep, res);}
    char tab[256];
    int input;
    printf("Merci de rentrer un nombre\n");
    while(fgets(tab, 255, stdin)!=NULL){
        if(0 < sscanf(tab, "%d", &input)){
            traceSpirale(input);
        }
        printf("Merci de rentrer un nombre\n");
    }
    return 0;
}
