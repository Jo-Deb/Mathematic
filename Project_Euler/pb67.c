#include<stdio.h>
#include<stdlib.h>

int myDB[100][100];

int max(int a, int b){
    if(a >= b){return a;}
    return b;
}

void getDataFromFile(){
    FILE * dataFile = fopen("p067_triangle.txt", "r");
    int tmp, i = 0, j;
    //Transfert des données du fichier dans myDB
    for(i = 0; i < 100; ++i){
        for(j = 0; j <= i; j++){
            fscanf(dataFile, "%d", &tmp);
            myDB[i][j] = tmp;
        }
    }
}

int plusGrandChemin(){
    int i, j;
    for(i = 98; i >= 0; i--){
        for(j = 0; j <= i; j++){
            myDB[i][j] += max(myDB[i+1][j], myDB[i+1][j+1]);
        }
    }
    return myDB[0][0];
}

int main(){
    getDataFromFile();
    int x = plusGrandChemin();
    printf("La valeur du plus grand chemin est %d\n", x);
    return x;
}
