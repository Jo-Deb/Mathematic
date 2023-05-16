#include <stdio.h>
#include <stdlib.h>


int pgcd(int a, int b){
    int res=1, quo, div1=a, div2=b;
    //div1 c'est le dividende et div2 c'est le diviseur
    while(res > 0){
        res=div1%div2; quo=div1%div2;
        //ainsi div1 = div2.quo + res
        div1 = div2; div2 = res;
    }
    return div1;
}

int main(){
    int a, b, res;
    for(b = 10; b<1000; b++){
        for(a = 11; a<1000; a++){
            res = pgcd(a,b);
            if(res > 10) {printf("pgcd(%d,%d) = %d\n", a, b, res);}
        }
    }
    return 0;
}
