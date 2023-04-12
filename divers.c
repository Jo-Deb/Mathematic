#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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
    for(i=0; i < (MAX-1); ++i){
        for(j=0; j<=i && j < (MAX-2); ++j){
            if(S2[i]==S3[j]){
                printf("carre[%i]+carre[%i]=%li=carre[%i]+carre[%i]+carre[%i]=%li\n", (i+1), (i+2), S2[i],
                        (j+1), (j+2), (j+3), S3[j]);
            }
        }
    }
    return 0;
}
