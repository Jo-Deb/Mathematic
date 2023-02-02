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
    if(idx % 3 == 0){num = 2*(idx/3);}
    for(i=idx-1; i>=1; --i){
        tmp = num; num = deno; deno = tmp;
        if(i==1){ num += 2*deno; }
        else{
            if(i % 3 == 0){ num += 2*(i/3)*deno; } else { num += deno; }
        }
    }
    printf("l'approximation de e à la réduite %d est : %d/%d et la somme des chiffres du numérateur est : %d\n"\
            , idx, num, deno, integerSum(num));
    return 0;
}
