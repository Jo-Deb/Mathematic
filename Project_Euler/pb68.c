#include <stdio.h>
#include <stdlib.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

void ** MyLists = NULL;
liste * smallToBig = NULL;
int NumberOfNodes;

/*On cherche tous les triplets a,b,c tel que a+b+c = sommeVal
 * avec a = max
 */
liste * trouveCombinaison(int sommeVal, int max){
    int i, j, k, a = max, b, c;
    liste * res = NULL;
    if(a > sommeVal){return NULL;}
    for(i = max - 1; i > 0; --i){
       b = i;
       if(a + b >= sommeVal){}
       else {
           for(j = i-1; j > 0; --j){
               c = j;
               if(a+b+c == sommeVal){ res = ajoutEnTete(res, a*100+b*10+c); }
               else{ if(a+b+c < sommeVal){break;} }
           }
       }
    }
    return res;
}

/*conserver toutes les combinaisons pour une valeur*/
void ** tableauDesCombinaisons(int sommeVal, int nodeNumber){
    void ** res = malloc(nodeNumber*sizeof(void *));
    int i;
    for(i = nodeNumber - 1; i>=0; --i){
        res[i] = (void*)trouveCombinaison(sommeVal, i+1);
    }
    return res;
}

int stringSize(char * tab){
    int i = 0;
    while(tab[i]!='\0'){++i;}
    return i;
}

/*On recherche la  sous-chaine sc dans la chaine st
 * si la fonction retourne 1, la sous-chaine est présente, 0 sinon*/
int test_sous_chaine(char * sc, char * st){
    int i, j, tsc = stringSize(sc), tst = stringSize(st), flag = 0;

    for(i=0; i < tst; ++i){
        if(flag == 1){return 1;}
        for(j = 0; j < tsc; ++j){
            /*test pour identifier 1*/
            if(sc[j] == st[i+j] && sc[j]=='1' && tsc == 1 && st[i+j+1] != '0'){flag = 1; break;}
            if(sc[j] == st[i+j] && sc[j]=='1' && tsc == 2 && st[i+j+1] =='0' && sc[j+1]=='0'){flag = 1; break;}
            else{
                if(sc[j] == st[i+j] && tsc == 1 && sc[j] != '1'){flag = 1;} else {flag = 0; break;}
            }
        }
    }
    return flag;
}

/*Vérifier que chaque noeud (nombre) est exprimé au moins une fois 
 * dans l'ensemble du tableau de combinaison. La fonction retourne
 * une valeur supérieure à 0 correspondant au noeud qui n'est pas 
 * représenté dans le tableau; si tous les noeuds sont présents 
 * dans le tableau elle retourne 0.
 */
int check(void ** tab){
    int i/*boucle sur les noeuds*/, j/*boucle sur le tableau*/, flag = 1/*identifie la présence d'un noeud*/;
    liste * tmp = NULL;
    for(i=1; i <= NumberOfNodes && flag == 1; ++i){
        for(j = 0; j<NumberOfNodes; ++j){
            tmp = tab[j];
            while(tmp == NULL && j < NumberOfNodes){++j; tmp = tab[j];}
            while(tmp != NULL){
                flag = test_sous_chaine(intToString(i), intToString(tmp->value));
                if(flag == 1){break;}
                tmp = tmp->l;
           }
            if(flag == 1){break;}
        }
    }
    /*Après la 1ère itération, la boucle incrémente d'abord le i 
     * avant de tester la condition de passage, raison pour laquelle on
     * décremente ici, afin de récupérer la valeur de la dernière itération*/
    if(flag == 0){--i; printf("le sommet %i n'est pas représenté\n", i); return i;}
    return 0;
}

/*Affiche le tableau des différentes combinaison*/
void afficheTab(void ** tab){
    int i;
    for(i=0; i < NumberOfNodes; ++i){
        if(tab[i] != NULL){printf("case %d: ", i);afficheListe(tab[i]);printf("\n");}
    }
}

int power(int base, int exposant){
    int i, res = base;
    for(i = 1; i < exposant; ++i){res *= res;}
    return res;
}

int concateneEntier(int a1, int a2, int a3){
    return ((a1*power(10,calculTailleEntier(a2))+a2)*power(10,calculTailleEntier(a3)))+a3;
}

/*prend une liste d'entier et renvoie la liste contenant 
 * tous les arrangements de toutes les valeurs de la liste
 * d'entrée*/
liste * AllArrangement(liste * tmp){
    liste * res = NULL, * pcrs = tmp;
    int vtmp = 0, a, b, c;
    char * stmp = NULL;
    while(pcrs != NULL){
        a = b = c = 0;
        vtmp = pcrs->value;
        stmp = intToString(vtmp);
        while(stmp[0]!='\0'){
            if(a == 0 && stmp[0] == '1' && stmp[1]=='0'){ a = 10; stmp += 2; }
            else{ a = stmp[0] - 48; /*conversion de valeur ascii à entière*/ ++stmp;}
            if(b == 0 && stmp[0] == '1' && stmp[1]=='0'){ b = 10; stmp += 2; }
            else{ b = stmp[0] - 48; /*conversion de valeur ascii à entière*/ ++stmp;}
            if(c == 0 && stmp[0] == '1' && stmp[1]=='0'){ c = 10; stmp += 2; }
            else{ c = stmp[0] - 48; /*conversion de valeur ascii à entière*/ ++stmp;}
            if(stmp[0]!='\0'){ printf("les valeurs a=%d, b=%d, c=%d sont attribuées mais le reste de stmp = %s\n",a,b,c,stmp);}
        }
        /*On doit ajouter les combinaisons abc, acb, bac, bca, cab, cba à la liste résultante*/
        res = ajoutEnTete(res, concateneEntier(a, b, c));
        res = ajoutEnTete(res, concateneEntier(a, c, b));
        res = ajoutEnTete(res, concateneEntier(b, a, c));
        res = ajoutEnTete(res, concateneEntier(b, c, a));
        res = ajoutEnTete(res, concateneEntier(c, a, b));
        res = ajoutEnTete(res, concateneEntier(c, b, a));
        pcrs = pcrs->l;
    }
    return res;
}

/*Just iterate over the function AllArrangement
 * to generate all possible value for nodes*/
void generateAllValue(void ** tab){
    printf("Voici le tableau de valeurs de noeud avant le calcul de tous les arrangements:\n");
    afficheTab(tab);
    int i;
    for(i = 0; i < NumberOfNodes; ++i){
        if (tab[i] != NULL ) { tab[i] = AllArrangement(tab[i]);}
    }
    printf("________________________________________________________________\n\
            Voici le tableau de valeurs des noeuds après le calcul des arrangements:\n");
    afficheTab(tab);
}

glist * combinaison(int valNode, int somme){
    if(valNode <= 0 || valNode > 10){ printf("Mauvais argument pour la valeur du noeud : %d\n", valNode); return NULL; }
    if(somme >= 27 ){ printf("Mauvais argument pour la somme : %d\n", somme); return NULL; }
    
    int e, i, j; glist * res = NULL;
    for(i = 1; i <= 10; ++i){
        if(valNode == i){++i;}
        if(valNode + i > somme){ return res; }
        e = i;
        for(j = 1; j <= 10; ++j){
            if(j == e){++j;}
            if(valNode + e + j > somme){break;}
            if(valNode + e + j == somme){ 
                char ** tab = malloc(sizeof(char *) * 3);
                tab[0] = intToString(valNode), tab[1] = intToString(e), tab[2] = intToString(j);
                res = g_ajoutTete(res, (void *)concatString(tab, 3), NULL);
            }
        }
    }
    return res;
}

void showElt(void * pt){ printf(" %s ", (char*)pt); }

/*
 * A chaque ajout d'un élément on revérifie toutes les conditions, si les conditions sont
 * valides on continue, sinon on arrête et on passe à l'élément suivant
 * FAIRE UNE FONCTION QUI CALCULE LA LISTE DES NOEUDS EXTERNES ET INTERNES ET QUI ENVOIE NULL 
 * QUAND UNE CONDITION N'EST PAS RESPECTÉE.
 * On prend une somme N de nos branches, puis en partant de 10, on prend un élément contenant
 * 10 et dont la somme est égale à N, on prend un élément contenant 9 et dont la somme est 
 * égale à N et on vérifie les conditions qui sont : 
 * 1 - chaque nombre doit avoir au moins une itération et au plus 2
 *    + les nombres avec 1 itération sont les noeuds externes
 *    + les nombres avec 2 itérations sont les noeuds internes dessinant la figure centrale, 
 *      dans notre cas un pentagone
 *
 * 2 - un noeud interne est relié à un noeud externe et un noeud interne, aucune autre 
 *     combinaison n'est valable
 * 3 - Il y a 10 noeuds, on doit donc avoir 5 noeuds externes et 5 noeuds internes à la fin
 * 4 - réécriture des combinaisons*/


int main(int argc, char ** argv){
    /*________________________________________vérification des entrées___________________________________*/
    int i, j, res;
    liste * ret;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &NumberOfNodes) != EOF){} 
        else{printf("Mauvais argument %s\nEchec du traitement\n", argv[1]); 
            return 1;
        }
    }
    else {printf("Mauvais nombre d'argument\nUsage : ./myExe 6 ou ./myExe 10\n"); return 1;}
    /*________________________________________Début de la solution_______________________________________*/
    void ** tab = malloc(NumberOfNodes * sizeof(void *));
    int max = NumberOfNodes + (NumberOfNodes -1) + (NumberOfNodes - 2); /*somme des 3 noeuds les plus grands; sans solution pour le problème 68*/
    int min = NumberOfNodes + 2 + 1; /*la plus petite somme de branche que l'on puisse faire avec le sommet le grand*/
    for(i = min; i < max; ++i){
        for(j = NumberOfNodes; j > 0; --j){
            ret = trouveCombinaison(i, j);
            tab[j-1] = (void*) ret;
            if(ret == NULL){ printf("on ne peut pas former une branche de somme %d avec %d comme valeur max\n", i, j); }
            else {printf("avec %d en partant de %d on obtient : ", i, j);afficheListe(ret); printf("\n");}
        }
        if((res = check(tab)) == 0){
            printf("voici la liste des valeurs pour %d:\n", i);
            generateAllValue(tab);
        }
        else{printf("la valeur %i n'a pas de solution avec le noeud %d\n", i, res);}
    }
    char * chaine1 = "test pour voir l'arithmétique des pointeurs";
    printf("initialement chaine1 = %s\n", chaine1);
    for(i = 0; i < 10; ++i){
        printf("le pointeur incrémenté de %d donne : %s\n", i, ++chaine1);
    } 
    printf("la valeur %s est une string\n", intToString(1031)); 
    printf("la valeur %s est une string\n", intToString(1013)); 
    return 0;
}
