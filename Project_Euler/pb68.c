#include <stdio.h>
#include <stdlib.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

int NumberOfNodes;
int * brancheTable = NULL;
int tailleCombi = 0;
int brnchTbl_length = 0;
void ** ListeAnalyse = NULL;
glist * context = NULL;

/*On cherche tous les triplets a,b,c tel que a+b+c = sommeVal
 * avec a = min 
 */
liste * trouveCombinaison(int sommeVal, int min){
    int i, j, a = min;
    liste * res = NULL;
    for(i = min+1; i < NumberOfNodes; ++i){
        if(a+i >= sommeVal){return res;}
        else{
            for(j=i+1; j<=NumberOfNodes; ++j){
                if(a+i+j == sommeVal){ res = ajoutEnTete(res, a*100+i*10+j); }
                else{ if(a+i+j > sommeVal) {break;} }
            }
        }
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

/*Vérifier que chaque noeud (nombre) est exprimé au moins une fois. 
 * La fonction retourne une valeur supérieure à 0 correspondant 
 * au noeud qui n'est pas représenté dans le tableau; 
 * si tous les noeuds sont présents dans le tableau elle retourne 0.
 */
int check(liste * l){
    int i/*boucle sur les noeuds*/, flag = 1/*identifie la présence d'un noeud*/;
    liste * tmp = NULL;
    for(i=1; i <= NumberOfNodes && flag == 1; ++i){
            tmp = l;
            while(tmp != NULL){
                flag = test_sous_chaine(intToString(i), intToString(tmp->value));
                if(flag == 1){break;}
                tmp = tmp->l;
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
liste * AllArrangement(int val){
    liste * res = NULL;
    int vtmp = val, a, b, c;
    char * stmp = NULL;
    a = b = c = 0;
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
    return res;
}

void afficheListe68(void * l){ afficheListe((liste *) l); }

/*Just iterate over the function AllArrangement
 * to generate all possible value for nodes*/
glist * generateAllValue(liste * l){
    printf("Voici la liste de valeurs de noeud avant le calcul de tous les arrangements:\n");
    afficheListe(l);
    glist * res = NULL;
    liste * tmp = l;
    while(tmp != NULL){
        g_ajoutFin(res, AllArrangement(tmp->value), NULL);
        tmp = tmp->l;
    }
    printf("________________________________________________________________\n\
            Voici le tableau de valeurs des noeuds après le calcul des arrangements:\n");
    g_afficheList(res, afficheListe68);
    return res;
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

/*Calcule la prochaine combinaison en fonction des arguments*/
liste * nextCombinaison(int * debut, int * tCmb, int * idxLst){
    int i, tmp[*tCmb];
    liste * res = NULL;
    for(i=0; i<(*tCmb); ++i){tmp[i] = 0;}
    if(*idxLst == (brnchTbl_length-1)){*debut += 1; *idxLst = *debut + (*tCmb - 1);}
    else { *idxLst += 1; }
    for(i=*debut; i<(*tCmb)-1; ++i){ res = ajoutEnQueue(res, tmp[i-(*debut)]); }
    res = ajoutEnQueue(res, brancheTable[*idxLst]);
    return res;
}

/*Cette fonction incrémente la recherche en mettant
 * à jour les indices dans le pointeur contexte. La valeur agrandir
 * permet de savoir s'il faut ajouter un nouvel élément ou changer
 * l'élément dernièrement inséré*/
void incrementRecherche(glist * possibleBranche, int agrandir){
    int numList, idx = NumberOfNodes, fini = 0;
    liste * res = NULL;
    /*initialisation du contexte dans le cas d'un nouveau tableau*/
    if(context == NULL){
        res = ajoutEnTete(ajoutEnTete(NULL, 1), 1);//1er élément du context
        context = g_ajoutTete(context, res, NULL);
        res = ajoutEnTete(ajoutEnTete(NULL, 1), 1);//2eme élément du context
        g_ajoutFin(context, res, NULL);
        return;
    }
    while(fini == 0){
        if(agrandir){
            int tailleContext = g_listLongueur(context);
            if(tailleContext == NumberOfNodes/2){
                printf("incrementRecherche: Agrandir est une erreur, il y a déjà %d branches indiquées dans le contexte\n",\
                        NumberOfNodes/2);
                return;
            }
            res = ajoutEnTete(ajoutEnTete(NULL, 1), 1);//2eme élément du context
            g_ajoutFin(context, res, NULL);
            fini = 1;
        }
        else{
            //On récupère les informations du dernier élément ajouté dans le contexte
            res = g_getList(context, g_listLongueur(context));
            numList = res->value; idx = res->l->value;
            //tester pour savoir si on a pris le dernier élément de la colonne
            if(idx == taille((liste *) g_getList(possibleBranche, numList))){
                if(numList == g_listLongueur(possibleBranche)){context = g_supprimElt(context, res);}
            }
            else{ res->l->value = ++idx; fini = 1;}
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
glist * gatherPotentialSolution(glist * possibleBranche){
    int i, idx;
    glist * solTab = NULL;
    liste * res = NULL;
    if(context == NULL){incrementRecherche(tab, 1);}
    while(checkContext(tab)){
        while(taille(res) < NumberOfNodes/2){
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
        printf("gatherPotentialSolution: la liste suivante est ajouté à solTab : "); afficheListe(res); printf("\n");
        solTab = g_ajoutTete(solTab, res, NULL);
        res = NULL;
        incrementRecherche(tab, 0);
    }
    return solTab;
}

int main(int argc, char ** argv){
    /*________________________________________vérification des entrées___________________________________*/
    int i, j, res;
    liste * ret = NULL, * tmp = NULL;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &NumberOfNodes) != EOF){} 
        else{printf("Mauvais argument %s\nEchec du traitement\n", argv[1]); 
            return 1;
        }
    }
    else {printf("Mauvais nombre d'argument\nUsage : ./myExe 6 ou ./myExe 10\n"); return 1;}
    /*________________________________________Début de la solution_______________________________________*/
    int max = NumberOfNodes + (NumberOfNodes -1) + (NumberOfNodes - 2); 
    /*somme des 3 noeuds les plus grands; sans solution pour le problème 68*/
    int min = NumberOfNodes + 2 + 1; /*la plus petite somme de branche que l'on puisse faire avec le sommet le grand*/
    for(i = min; i < max; ++i){
        for(j = 0; j < NumberOfNodes/2; ++j){
            tmp = trouveCombinaison(i, j+1);
            if(tmp == NULL){ printf("on ne peut pas former une branche de somme %d avec %d comme valeur max\n", i, j); }
            else {
                printf("avec %d en partant de %d on obtient : ", i, j);
                afficheListe(tmp); printf("\n");
                ret = concateneListe(ret, tmp);
            }
        }
        if((res = check(ret)) == 0){
            printf("voici la liste des valeurs pour %d:\n", i);
            generateAllValue(ret);
            //printf("ci-dessous le tableau complet pour la valeur %d\n", i);
            //afficheTab(tab);
            gatherPotentialSolution(tab);
        }
        else{printf("la valeur %i n'a pas de solution avec le noeud %d\n", i, res);}
    }
    return 0;
}
