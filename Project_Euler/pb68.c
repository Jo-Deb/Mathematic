#include <stdio.h>
#include <stdlib.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

void ** MyLists = NULL;
liste * smallToBig = NULL;
int NumberOfNodes;
void ** ListeAnalyse = NULL;
int * context = NULL;

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

/*Casser en une branche de sommets, représenter par un entier à 3 nombres, en une 
 * liste d'entiers qui nous permet d'identifier chaque sommet*/
int * decompose_node(int branch){
    int * res = malloc(3*sizeof(int)), i, tmp = branch;
    for(i=2; i>=0; --i){
        if(tmp%10 != 0){res[i]=tmp%10; tmp /= 10;}
        else { res[i]=tmp%100; tmp /=100;}
    }
    return res;
}

/*Recherche node_to_search dans le tableau et retourne
 * la liste des éléments qui lui sont liés à node_to_search*/
liste * analyse(int node_to_search, int tab[]){
    liste * res = NULL;
    if(tab[0] == node_to_search){res = ajoutEnQueue(res, tab[1]);}
    if(tab[1] == node_to_search){
        res = ajoutEnQueue(res, tab[0]); 
        res = ajoutEnQueue(res, tab[2]);
    }
    if(tab[2] == node_to_search){res = ajoutEnQueue(res, tab[1]);}
    return res;
}

/*calcul le nombre de noeud distints dans une liste solution*/
int nbrDistinctNodes(liste *ls){
    liste * tmp = ls, * lt = NULL;
    int res = 0, i, * tab = NULL;
    while(tmp != NULL){
        tab = decompose_node(tmp->value);
        for(i = 0; i<3; ++i){ if(EstPresent(lt, tab[i])){lt = ajoutEnTete(lt, tab[i]);} }
        free(tab);
        tab = NULL;
        tmp = tmp->l;
    }
    res = taille(lt);
    freeListe(lt);
    return res;
}

/*Identifie si dans une liste solution il y a un noeud saturé*/
int saturationNoeud(){
    int i;
    for(i=0; i < NumberOfNodes; ++i){
        if(taille(ListeAnalyse[i]) > 3){printf("saturationNoeud: noeud %d saturé\n", i+1); return i+1;}
    }
    return 0;
}

/*Fonction de libération d'espace du pointeur void ** ListeAnalyse*/
void freeListeAnalyse(){
    if(ListeAnalyse == NULL){return;}
    int i;
    for(i=NumberOfNodes; i>0; --i){ free(ListeAnalyse[i]); ListeAnalyse[i] = NULL; }
    free(ListeAnalyse);
    ListeAnalyse = NULL;
}

/*Pour une liste solution proposée, retourne un tableau ListeAnalyse
 * la fonction suppose que la liste ls est non nulle*/
void construireListeAnalyse(liste * ls){
    int * tab = NULL, i;
    liste * tmp = ls;
    freeListeAnalyse();
    ListeAnalyse = malloc(NumberOfNodes * sizeof(void *));
    for(i=0; i < NumberOfNodes; ++i){ListeAnalyse[i] = NULL;}
    while(tmp != NULL){
        tab = decompose_node(tmp->value);
        for(i=0; i < 3; ++i){ ListeAnalyse[tab[i] - 1] = analyse(tab[i], tab); }
        tmp = tmp->l;
        free(tab); 
        tab = NULL;
    }
}

/*Une fonction pour identifier les noeuds externes. 
 * Attention: il faut identifier les noeuds externes quand
 * on a une liste solution à 5 branches*/
liste * noeudsExternes(){
    int i, len = 0;
    liste * res = NULL;
    for(i = 0; i < NumberOfNodes; ++i){
        if((len=taille(ListeAnalyse[i])) == 1) { res = ajoutEnTete(res, i+1); }
    }
    return res;
}

void affiche_decomposition(int tab[]){
    int i;
    for(i=0; i<3; ++i) {printf("%d ", tab[i]);}
    printf("\n");
}

/*Regarde si un noeud est relié à plusieurs noeuds externes*/
int saturationExterne(){
    liste * externNode = noeudsExternes();
    liste * tmp = NULL;
    int i, cpt = 0;

    for(i=0; i < NumberOfNodes; ++i){
        tmp = externNode;
        cpt = 0;
        while(tmp != NULL){
           if(getPosition(ListeAnalyse[i], tmp->value) > 0){++cpt;}
           tmp = tmp->l;
        }
        if(cpt > 1){printf("saturation en noeud externe du sommet %d\n", (i+1)); return (i+1);}
    }
    return 0;
}

/*retourne -1 si val_noeud n'est pas un noeud externe*/
int estNoeudExterne(int val_noeud, liste * externeNoeud){return getPosition(externeNoeud, val_noeud);}

/*Identifier si un noeud est non-externe et lié à au moins
 * un noeud externe. Valeur de retour -1 alors val_node est un noeud externe
 * retourne une valeur entre 0 et 3 pour indiquer le nombre de noeud externe en lien*/
int testLienExterne(int val_node, liste * externNode){
    int res = 0;
    liste * tmp = NULL;
    if(estNoeudExterne(val_node, externNode) !=-1){ return -1; }
    tmp = ListeAnalyse[val_node-1];//la liste des sommets en lien direct avec val_node 
    while(tmp != NULL){
        if(estNoeudExterne(tmp->value, externNode) >= 1){++res;}
        tmp = tmp->l;
    }
    return res;
}

/*Affiche le tableau des différentes combinaison*/
void afficheTab(void ** tab){
    int i;
    liste * tmp = NULL;
    for(i=0; i < NumberOfNodes; ++i){
        if(tab[i] != NULL){printf("case %d: ", i);afficheListe(tab[i]);printf("\n");}
       tmp = tab[i];
       //while(tmp != NULL){affiche_decomposition(decompose_node(tmp->value)); tmp = tmp->l;}
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

void showElt(void * pt){ printf(" %s ", (char*)pt); }

/*Récupère prop, qu'on considère comme une liste d'une solution
 * potentielle. La fonction va parser toutes les branches de la 
 * liste et remplir ListeAnalyse pour indiquer les noeuds
 * reliés au noeud représenté par l'indice du tableau + 1
 * ListeAnalyse est un tableau à 2 dimensions, on suppose qu'il a
 * une taille de 10 NumberOfNodes*/
void parseListe(liste * prop){
    liste * tmp = prop;
    int i;
    if(ListeAnalyse != NULL){
        for(i=0; i < NumberOfNodes; ++i){free(ListeAnalyse[i]);}
        ListeAnalyse = NULL;
    }
    ListeAnalyse = malloc(NumberOfNodes*sizeof(void *));
    for(i=0; i < NumberOfNodes; ++i){
        tmp = prop;
        while(tmp != NULL){
            ListeAnalyse[i] = concateneListe(ListeAnalyse[i], analyse(i+1, decompose_node(tmp->value)) );
            tmp = tmp->l;
        }
    }
}

/*Cette fonction incrémente la recherche en mettant
 * à jour les indices dans le pointeur contexte. La valeur agrandir
 * permet de savoir s'il faut ajouter un nouvel élément ou changer
 * l'élément dernièrement inséré*/
void incrementRecherche(void ** tab, int agrandir){
    int i = NumberOfNodes, idx = NumberOfNodes, fini = 0;
    /*initialisation du contexte dans le cas d'un nouveau tableau*/
    if(context == NULL){
        context = malloc(NumberOfNodes * sizeof(int));
        for(i=NumberOfNodes-1; i>=0; --i){context[i] = 0;}
        i = NumberOfNodes - 1;
        while(tab[i] == NULL){--i;}
        if(taille(tab[i]) > 0){context[i] = 1; return;}
        if(tab[i] != NULL && taille(tab[i]) == 0){
            printf("tab[%d] est non nulle alors que la liste sur laquelle il pointe contient 0 élément\n", i); 
        }
        return;
    } 
    while(fini == 0){
        //On boucle pour avoir l'indice le plus petit
        for(i = NumberOfNodes-1; i>=0; --i){ if(context[i]!=0){idx = i;} }
        if(agrandir){
            if(idx == 0){
                printf("incrementRecherche: On est au bout du tableau context.\
                Merci de regarder la situation avec précision\n");
                return;
            }
            i = idx - 1;
            while(tab[i] == NULL){--i;}
            context[i] = 1; fini = 1;
        }
        else{
            if(context[idx] == taille(tab[idx])){context[idx] = 0;}
            else {context[idx] += 1; fini = 1;}
        }
    }
}

/*Cette fonction permet de vérifier si toutes les 
 * solutions ont été indexées dans le contexte*/
int checkContext(void ** tab){
    int i;
    for(i=0; i < NumberOfNodes; ++i){
        if(context[i] == 0 && tab[i] != NULL){return 1;}
        if(context[i] != 0 && taille(tab[i]) != context[i]){return 1;}
    }
    return 0;
}

/*Génère toutes les solutions potentielles du problème*/
glist * gatherPotentialSolution(void ** tab){
    int i, idx;
    glist * solTab = NULL;
    liste * res = NULL;
    if(context == NULL){incrementRecherche(tab, 1);}
    while(checkContext(tab)){
        while(taille(res) < 5){
            freeListeAnalyse();
            //On construit une liste à partir des index inscrits dans le contexte
            for(i = 0; i < NumberOfNodes; ++i){ if((idx = context[i])!=0){res = ajoutEnQueue(res, getValue(tab[i], idx));} }
            construireListeAnalyse(res);
            if(saturationNoeud() == 0){ incrementRecherche(tab, 1); } 
            else {
                supprimeListe(res); 
                res = NULL;
                incrementRecherche(tab, 0);
            }
        }
        printf("gatherPotentialSolution: la liste suivante est ajouté à solTab : "); afficheListe(res);
        solTab = g_ajoutTete(solTab, res, NULL);
        res = NULL;
    }
    return solTab;
}

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
    for(i=0; i < NumberOfNodes; ++i){tab[i] = NULL;}
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
            printf("ci-dessous le tableau complet pour la valeur %d\n", i);
            afficheTab(tab);
            gatherPotentialSolution(tab);
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
