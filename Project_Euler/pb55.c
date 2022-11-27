#include <stdio.h>
#include <stdlib.h>
#include "fonctionsPratiques.h"

void afficheIntTab(int * tab, int taille){
    int i;
    for(i=0; i<taille; i++){ printf("%d", tab[i]);}
    printf(" ");
}

int palindrome(int * val, int taille){
   int limit, i;
   if(taille==1){return 1;}
   if(taille%2==0){limit = taille/2 - 1;}
   else{ limit = (taille-1)/2 - 1;}

   for(i=0; i<=limit; i++){
        if(val[i]!=val[taille-1-i]){return 0;}
   }
   return 1;
}

int * inverser(int * val, int *taille){
    int * bat = malloc(*taille*sizeof(int)), i;

    for(i=*taille-1; i>=0; i--){bat[*taille-1-i]=val[i];}
    return bat;
}

int * pb55_addition(int * arg1, int * arg2, int * taille){
    //printf("\nOn va inverser le tableau ");
    //afficheIntTab(arg1, *taille);
    int i, ret=0, res, deb=-1; 
    int *tmp1 = malloc(29*sizeof(int));  
    int *tmp2 = malloc(29*sizeof(int));  
    int *tmp3 = malloc(29*sizeof(int));  

    for(i=0; i<=28; i++){tmp1[i]=0; tmp2[i]=0; tmp3[i]=0;}
    /*printf("\ntmp1 vaut :");
    afficheIntTab(tmp1, 29);
    printf("\ntmp2 vaut :");
    afficheIntTab(tmp2, 29);
    printf("\ntmp3 vaut :");
    afficheIntTab(tmp3, 29);
    */
    for(i=0; i<=(*taille)-1; i++){tmp1[29-(*taille)+i]=arg1[i]; tmp2[29-(*taille)+i]=arg2[i];}
    /*printf("\ntmp1 vaut :");
    afficheIntTab(tmp1, 29);
    printf("\ntmp2 vaut :");
    afficheIntTab(tmp2, 29);
    printf("\ntmp3 vaut :");
    afficheIntTab(tmp3, 29);
    */
    for(i=28; i>=29-(*taille); i--){
        if((res=ret + tmp1[i]+tmp2[i])<=9){tmp3[i]=ret+tmp1[i]+tmp2[i]; ret=0;}
        else{tmp3[i]=res%10; ret=1;}
    }
    if (ret == 1){ tmp3[29-(*taille+1)]=ret;}
    i=0;

    while(i<29 && deb==-1){
        if(tmp3[i]!=0){deb=i; break;}
        else{++i;}
    }
    int dim = 29-deb;
   /* printf("\naprès addition tmp3 vaut :");
    afficheIntTab(tmp3, 29);
    printf("\nDim vaut %d\n", dim);
    */
    int *final=malloc(dim*sizeof(int));
    *taille=dim;
    for(i=0; i<dim; i++){final[i]=tmp3[deb+i];}
    free(tmp1); free(tmp2); free(tmp3);
    /*printf("\nVoici le résultat en inversé: ");
    afficheIntTab(final, dim);
    */
    return final;
}


int main(){
    int i=1,j, cpt=0, flag=0, taille=0;
    int * iter, *tmp, *tab;
    while(i<10000){
        taille=calculTailleEntier(i);
        tmp = intToTab(i);
        tab = inverser(tmp, &taille);
        iter = pb55_addition(tmp, tab, &taille);
        for(j=1; j<=50; j++){
            if(palindrome(iter, taille)==1){flag=1;break;}
            tab = inverser(iter, &taille);
            iter = pb55_addition(iter, tab, &taille);
            free(tab);
            tab=NULL;
        }
        if(flag==1){
            printf("\nracine %d produit le palindrone ",i);
            afficheIntTab(iter, taille);
            free(iter);
        }
        else{++cpt;}
        flag=0;
        free(tmp);
        if(tab==NULL){free(tab);}
        ++i;
    }
    printf("il y a %d nombres de Lychrel en dessous de 10000\n", cpt);
    return 0;
}
