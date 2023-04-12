#include <stdio.h>

#define LIMIT 10000
int SQUARE[LIMIT];
int PENTAGON[LIMIT];

void fillSquare(){
    int i;
    for(i=0; i<LIMIT; ++i){ SQUARE[i] = ((i+1)*(i+1)); }
}

void fillPentagon(){
    int i;
    for(i=0; i<LIMIT; ++i){ PENTAGON[i] = (i+1)*(3*(i+1) - 1)/2; }
}

int main(){
    //L'objectif est d'afficher l'indice et les valeurs carrées qui sont pentagonales
    int i, j, flag;
    fillSquare();
    fillPentagon();
    for(i=1; i < LIMIT; ++i){
        j = 0, flag = 0;
        while(flag == 0){
            if(SQUARE[i] > PENTAGON[j]){++j;}
            else{
                if(SQUARE[i] == PENTAGON[j]){printf("i = %d, j = %d et leur valeur est %d\n", i, j, SQUARE[i]);}
                flag = 1;
            }
        }
    }
}
