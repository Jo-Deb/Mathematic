#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MAX 200000
long int CARRE[MAX];
long int S2[MAX-1];
long int S3[MAX-2];

void fillCarre(){
    int i;
    for(i=0; i < MAX; ++i){CARRE[i] = (i+1)*(i+1);}
}

void faireLesSommes(){
    int i;
    for(i=0; i < (MAX-1); ++i){ S2[i] = (CARRE[i]+CARRE[i+1]); }
    for(i=0; i < (MAX-2); ++i){ S3[i] = (CARRE[i]+CARRE[i+1]+CARRE[i+2]); }
}

int main() {
    int i, j;
    fillCarre();
    faireLesSommes();
    for(i = 1; i <= 10; ++i){
        j = exp2(i);
        printf(" 1/%d = %lf\n", j, 1.0/j);
    }
    printf("\n");
    return 0;
}
