#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctionsPratiques.h"

int is_desc(int * tab, int dep, int len){
    int i;
    if(dep >= len){printf("is_desc: le départ est supérieur ou égale à la longueur\n"); return -1;}
    for(i=dep; i<len-1; i++){ if(tab[i]<tab[i+1]) {return 0;} }
    return 1;
}

int is_asc(int * tab, int dep, int len){
    int i;
    if(dep >= len){printf("is_desc: le départ est supérieur ou égale à la longueur\n"); return -1;}
    for(i=dep; i<len-1; i++){ if(tab[i]>tab[i+1]) {return 0;} }
    return 1;
}

int plusPetitSuperieur(int * tab, int elt, int dep, int len){
    int i, find=0, position, tmp=getMax(tab, len);
    if(dep >= len){printf("plusPetitSuperieur: le départ est supérieur ou égale à la longueur\n"); return -1;}
    for(i=dep; i<len; i++){ 
        if(tab[i] > elt){
            find=1;
            if(tmp >= tab[i]){tmp=tab[i]; position=i;} 
        } 
    }
    if(find==1){return position;}
    else {return -1;}
}

int nbr_occu(int e, int tab[]){
    int i, occ=0;
    for(i=0; i<5000 && tab[i]!=-1; ++i){ if(tab[i]==e){++occ;} }
    return occ;
}

int position(int elt, int * ens, int t_ens){
    int i;
    for(i=0; i<t_ens; i++){
        if(ens[i]==elt){return i;}
    }
    return -1;
}

int * copie(int * combi, int t_combi){
    int * res = malloc(t_combi*sizeof(int)), i;
    for(i=0; i<t_combi; i++){ res[i]=combi[i]; }
    return res;
}

void affiche_tab(int * tab, int t){
    int i;
    for(i=0; i<t; i++){printf("%2d ", tab[i]);}
    printf("\n");
}

int * analyse_combi(int * combi, int t_combi, int * ens, int t_ens, int *f_evol){
    int i, cpos, cpr, epr,j;
    int * res = malloc(t_combi*sizeof(int));
    for(i=0; i<t_combi; i++){res[i]=combi[i];}
    *f_evol=0;
    for(i=t_combi-1; i>=0 && *f_evol==0; i--){
       cpos=position(res[i], ens, t_ens); 
       cpr=t_combi-i; epr=t_ens-cpos;
       if(epr > cpr){
           res[i]=ens[cpos+1]; *f_evol=1;
           for(j=1; j+i<t_combi; j++){res[i+j]=ens[cpos+1+j];} 
       }
    }
    return res;
} 

void combinaison(int * ens, int t_ens, int t_combi, int ** tab){
    int i, num=1, cpt=0, nb_combi, tmp, f_evol;
    for(i=t_ens; i>(t_ens-t_combi); i--){num=num*i;}
    nb_combi = num/factoriel(t_combi); //calcul du nombre de combinaison à générer
    tab[cpt]=malloc(t_combi*sizeof(int));
    for(i=0; i<t_combi; i++){tab[cpt][i]=ens[i];}
    while(cpt<nb_combi){
        tmp=position(tab[cpt][t_combi-1], ens, t_ens);
        for(i=tmp+1; i<t_ens; ++i){
            ++cpt;
            tab[cpt]=copie(tab[cpt-1], t_combi);//On copie à l'identique la combi précédente
            tab[cpt][t_combi-1]=ens[i]; //On change uniquement le dernier elt de la combi
        }
        ++cpt; f_evol=0;
        tab[cpt]=analyse_combi(tab[cpt-1], t_combi, ens, t_ens, &f_evol);
        if(f_evol==0){printf("problème avec la fonction analyse\n");}
    }
    printf("%d combinaisons ont été calculées \n", cpt);
    return;
}

int * analyse_permutation(int * comb, int len){
    int i, change=0, tmp, a = -1, *res = malloc(len*sizeof(int));
    for(i=0; i<len; i++){res[i]=comb[i];}
    //Si la permutation entrée représente déjà la valeur la plus grande, on arrête
    if(is_desc(comb, 0, len)==1){return res;}
    //on cherche les changements de croissant à décroissant ou l'inverse
    for(i=0; i<len-1; i++){ if(res[i]>res[i+1]){change=i;} }
    if(is_desc(res, change+1, len) == 1){
        a=-1, tmp=change;
        a=plusPetitSuperieur(res, res[tmp], tmp, len);
        while(a < 0){
            a=0;
            if(tmp-1 >=0){
                tmp = tmp-1;
                a = plusPetitSuperieur(res, res[tmp], tmp, len);
            }
        }
        invert(res, a, tmp);
        triSousTab(res, len, tmp+1);
        return res;
    }

    if(is_asc(res, change+1, len)==1){
        invert(res, len-1, len-2);
        return res;
    }
    return res;
}

void permutCombinaison(int * comb, int len, int ** res){
    int nb_permut = factoriel(len), cpt=0;
    //res = malloc(nb_permut*sizeof(int*));
    res[cpt]=comb;
    while(cpt < nb_permut){
        ++cpt;
        res[cpt]=analyse_permutation(res[(cpt-1)], len);
    }
    return;
}

void decrypte(int tab[], int lt,  int * comb, int lc){
    int i=0, tmp=0; int c=0;
    char st[201]; st[200]='\0';
    for(i=0; i<200; i++){st[i]=0;}
    for(i=0; i<200; ++i){
        c=(tab[i]^comb[tmp]); //Opération XOR
        if(tmp==2){tmp=0;}
        else{++tmp;}
        st[i]=c;
    }
    tmp=0;
    for(i=0; i<200; i++){
        if(st[i]>=0 && st[i]<=8){tmp=1;}    
        if(st[i]>=11 && st[i]<=31){tmp=1;}    
        if(st[i]==127 || st[i]==124 || st[i]==126) {tmp=1;}    
        //if(st[i]<0){tmp=1;}    
        //if(st[i]>122){tmp=1;}    
    }
    if(tmp==0){
        printf("%s  ", st);
        affiche_tab(comb, lc);
    }
    return;
}

void decryptAllText(int tab[], int lt,  int * comb, int lc){
    int i=0, tmp=0, c=0, res[lt];
    unsigned int sum=0;
    for(i=0; i<lt; i++){res[i]=-1;}
    for(i=0; i<lt && tab[i]!=-1; ++i){
        c=(tab[i]^comb[tmp]); //Opération XOR
        if(tmp==2){tmp=0;}
        else{++tmp;}
        res[i]=c;
        printf("%c", res[i]);
        if(i!=0 && i%100==0){printf("\n");}
    }
    for(i=0; i<lt && res[i]!=-1; i++){sum=res[i]+sum;}
    printf("\n la somme totale des éléments est : %d\n", sum);
    return;
}


void decrypte2(int tab[], int lt,  int * comb, int lc){
    printf("\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    affiche_tab(comb, lc);
    int i=0, tmp=0; int c=0;
    for(i=0; i<lt && tab[i]!=-1; ++i){
        c=(tab[i]^comb[tmp]); //Opération XOR
        if(tmp==2){tmp=0;}
        else{++tmp;}
        printf("%c", c);
    }
    return;
}


int main(){
    FILE * ptr = fopen("decrypted_file59.txt", "r");
    //FILE * ptr = fopen("p059_cipher.txt", "r");
    int  input, idx=0, tab[5000], i=0, propre[5000], nb_comb=0, cpt=0;
    for(i=-1; i<5000; ++i){tab[i]=-1; propre[i]=-1;}
    char in[3], c;
    in[2]='\0'; i=0;
    while((input=fgetc(ptr))!=EOF){
       cpt = input + cpt;
       printf("%c", input);
/*
        if(input!=','){in[idx]=input; ++idx;}
        else{
            sscanf(in, "%d", &input);
            tab[i]=input;
            propre[i]=input; ++i;
            c=input; idx=0;
        }
*/
    }
    printf("\nLa somme ascii totale du texte est %d\n", cpt);
/*
    supprimeDoublon(propre, 5000, -1);
    for(i=0; i<5000; ++i){
        if(propre[i]!=-1){
            printf("val=%d  carac=%c occ=%d\n", propre[i], propre[i], nbr_occu(propre[i], tab));
        }     
    }
*/
    /*=========================Génération des permutations====================*/
   
    int ascii[26];input=1; int ** tptr=NULL;
    for(i=0; i<26; i++){ascii[i]=97+i;}
    for(i=26; i>26-3; --i){input*=i;}
    nb_comb=(input/6);
    int ** res= malloc(nb_comb*sizeof(int *));
    combinaison(ascii, 26, 3, res);
    triTab(res[cpt], 3);
    tptr=malloc(6*sizeof(int*));
    while(cpt < nb_comb){
        permutCombinaison(res[cpt], 3, tptr); 
        for(i=0; i<6; i++){decrypte2(tab, 5000, tptr[i], 3);}
        //for(i=0; i<6; i++){affiche_tab(tptr[i], 3);}
        //for(i=0; i<6; i++){free(tptr[i]);}
        ++cpt;
    }
   // int myComb[3]={101, 120, 112};
   // decryptAllText(tab, 5000, myComb, 3);
    /*========================================================================*/
    return 0;
}
