#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j, m, n, r, pgcd, cpt;
    for( i=10; i<=10000; i++ ){
        for( j=1; j<i; j++ ){
            r = i; pgcd = 0; m = i; n = j; cpt = 0;
            while( r > 0 ){
                r = m%n;
                if( r == 0 ){ pgcd = n; }
                m = n; n = r;
                ++cpt;
            }
            if(pgcd == 1 && cpt > 5 && pgcd != j){printf("pgcd(%d, %d) = %d en %d tours\n", i, j, pgcd, cpt);}
        }
    }
    return 0;
}

