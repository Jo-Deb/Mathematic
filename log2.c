#include <stdio.h>
#include <math.h>

double mylog2(int A, int precision){
    int n=0, k = 0;
    while(pow(2,n) <= A){++n;}
    --n;
    /*calcul de la partie décimale*/
    double X = (A*1.0)/(pow(2,n)), res = n * 1.0;
    while(k <= 20){
        X *= X; ++k;
        if(X > 2){ X /= 2; res += (1/pow(2, k)); }
    }
    return res;
}

int main(int argc, char ** argv){
    int m = 0;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &m) != EOF){}
        else{printf("Mauvais argument en entrée, il faut donner un entier en entrée\n"); return 0;}
    }
    double res = mylog2(m,4);
    printf("mylog2(%d) = %lf et log2(%d) = %lf\n", m, res, m, log2(m));
    return 0;
} 
