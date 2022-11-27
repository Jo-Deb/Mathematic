#include <stdio.h>
#include <stdlib.h>

int main(){
    int i, j, m, n, r, pgcd;
    for( i=10; i<=100; i++ ){
        for( j=1; j<10; j++ ){
            r = i; pgcd = 0; m = i; n = j;
            while( r > 0 ){
                r = m%n;
                if( r == 0 ){ pgcd = n; }
                m = n; n = r;
            }
            if(pgcd > 1){printf("pgcd(%d, %d) = %d\n", i, j, pgcd);}
        }
    }
    return 0;
}

