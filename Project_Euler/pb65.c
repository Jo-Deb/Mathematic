#include <stdio.h>
#include <stdlib.h>

int integerSum(int input){
    int oignon = input, res = 0, tmp;
    while(oignon > 0){
        tmp = oignon  % 10;
        res = res + tmp;
        oignon = oignon / 10;
    }
    return res;
}

int main(int argc, char ** argv){
    int idx, i;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &idx) > 0){}
        else{ printf("Mauvais argument, échec\n"); return 1;}
    }
    else{ printf("un argument attendu en entrée, échec\n"); return 1; }

    int deno = 1, res = 0, tmp, q, num = 1;
    if(idx == 1) {
        printf("l'approximation de e à la réduite %d est : 2\n", idx);
        return 0;
    }
    if(idx == 2) {
        printf("l'approximation de e à la réduite %d est : 3\n", idx);
        return 0;
    }

    for(i=idx; i>=1; --i){
        tmp = num; num = deno; deno = tmp;
        if(i == 1){ num += 2*deno;}
        else{
            if(i==idx){
                //On réalise les deux premières opérations du calcul soit, par exemple, 2 + 1/(1 + 1/1)
                if(i % 3 == 2){
                    q = (i - 2) / 3; num += deno;
                    tmp = num; num = 2*q*num + 1;
                    deno = num; i = i - 1;
                }
                else{
                    if(i % 3 == 1){ q = (i-1)/3; } else{ q = i/3; }
                    num = 2*q + deno; tmp = num;
                    num += 1; deno = tmp;
                    i = i - 1;
                }
            }
            else{
                if(i % 3 != 0){num += deno;}else{ q = i / 3; num += 2*q*deno;}
            }
        }
    }
    printf("l'approximation de e à la réduite %d est : %d/%d\n", idx, num, deno);
    return 0;
}
