#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

int carreParfait(int val){
    int i=1, multi;
    while((multi=i*i)<=val){
        if(multi==val){return i;}
        ++i;
    }
    return 0;
}

int main(){
    int compteur=0, i, mot, delta, racine;
    char buff[255];
    FILE * ff = fopen("data_pb42.dat", "r");
    
    while(fscanf(ff, "%s", buff)!=EOF){
     //   printf("%s", buff);
        i = 0; mot = 0; racine = 0;
        while(buff[i]!='\0'){mot += (buff[i]-64); i++;}
        printf("%s vaut : %d\n", buff, mot);
        delta = 8*mot + 1;
        if( (racine = carreParfait(delta)) > 0){
            if((1+racine)%2 == 0){printf("%s vaut %d, la racine_carre %d et la racine du polynome %d\n", buff, mot, racine, (1+racine)/2); ++compteur;}
        }
    }
    printf("Le nombre total de mots triangle est : %d\n", compteur);
    return EXIT_SUCCESS;
}
