#include <stdio.h>
#include <stdlib.h>
#include <math.h>


long racine(long val){
    double root = sqrt(val);
    long result;
    if(round(root)==root){result = root; return result;}
    else{return 0;}
}

int isPentagon(long val){
    //int deltaRacine = racineEntiere(24*val+1);
    long deltaRacine = racine(24*val+1);
    if(deltaRacine > 0){
        if((1+deltaRacine)%6==0){return 1;}
    }
    return 0;
}

int triangleNumber(long val){
    long deltaRacine = racine(8*val+1);
    if(deltaRacine > 0){
        if( (deltaRacine - 1)%2 == 0){return 1;}
    }
    return 0;
}

int hexagonalNumber(long val){
    long deltaRacine = racine(8*val+1);
    if(deltaRacine > 0){
        if( (1+deltaRacine)%4 == 0){return 1;}
    }
    return 0;
}

int main(){
    long cpt = 285, next = 0, val = 0;
    val = cpt*(cpt+1)/2;
    if(triangleNumber(val)>0 && isPentagon(val)>0 && hexagonalNumber(val)>0){
        printf("%ld un nombre étant triangle, pentagonal et hexagonal\n", val);
    }
    ++cpt;
    while(next == 0){
        val = cpt*(cpt+1)/2;
            if(triangleNumber(val)>0 && isPentagon(val)>0 && hexagonalNumber(val)>0){
                next = 1;
                printf("%ld, après 285, est le prochain nombre étant triangle, pentagonal et hexagonal et n est %ld\n", val, cpt);
                return EXIT_SUCCESS;
            }
        ++cpt;
    }
    return EXIT_SUCCESS;
}
