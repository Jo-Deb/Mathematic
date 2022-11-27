#include <stdio.h>
#include <stdlib.h>


char * multiplication(int a, int b){
    char * res = malloc(201*sizeof(char));
    int c, d, ret=0;
    for(c=0; c<200; ++c){res[c]=-1;}
    res[200]='\0';
    c=199; d=a;
    while(d>0){ res[c]=d%10; d=d/10; --c;}
    for(c=0; c<b-1; ++c){
        for(d=199; d>=0; --d){
            if(res[d]>=0){ret=res[d]*a+ret; res[d]=ret%10; ret=ret/10;}
            if(res[d]<0 && ret>0){res[d]=ret%10; ret=ret/10;}
            if(res[d]<0 && ret<0){break;}
        }
        ret=0;
    }
    d=0;
    while(res[d]<0 && d<=199){res[d]=0; ++d;}
    return res;
}

void afficheRes(char * res){
    int i=0;
    while(i<=199 && res[i]==0){++i;}
    while(i<=199){printf("%d", res[i]); ++i;}
    printf("\n");
} 

int sommeDesChiffres(char * res){
    int i=0, d=0;
    for(i=0; i<=199; ++i){ d=d+res[i];}
    return d;
}

int main(){
    int i, a, b,tmp, max=0;
    char * res;
    for(a=2; a<100; a++){
        for(b=1; b<100; b++){
            res = multiplication(a,b);
            tmp = sommeDesChiffres(res);
            if(tmp>max){max = tmp;}
            printf("%d puissance %d donne :", a, b); afficheRes(res);
            printf("somme des chiffres de %d puissance %d : %d", a, b, tmp);
            printf("\n______________________________________________________\n");
            free(res);
        }
    }
    //res = multiplication(4,8);
    //afficheRes(res);
    printf("la valeur maximale pour la somme des chiffres est %d", max);
    return 0;
}
