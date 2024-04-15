#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genList.h"
#include "fonctionsPratiques.h"
#include "liste.h"

int NumberOfNodes;
int * brancheTable = NULL;
int tailleCombi = 0;
int brnchTbl_length = 0;
int limitCombinaison = 0;
int combinaisonEnCours = 0;
void ** ListeAnalyse = NULL;


/*Calcul inVal+1 dans une base 6 et s'assure que inVal+1 est inférieur ou égale limite
 * On renvoie le résultat dans un tableau pour représenter les unités, les dizaines et les centaines*/
int * nextValueBase6(int inVal, int limite){
    int * tb1 = intToTab(inVal);
    if(inVal >= limite){
        printf("nextCombinaison: signature : (int inVal, int limite) et inVal < limite. Et maintenant on a inVal >= limite. Echec\n");
        return NULL;
    }
    int i, d, len = calculTailleEntier(limite), ajout = 1, retenue = 0, lenLimite = calculTailleEntier(inVal);
    int * res = malloc(len * sizeof(int));
    for(i=0; i<len; ++i){ res[i] = 0;}
    d = lenLimite - 1;
    for(i=len-1; i>=0; --i){
        if(d>=0){
            if ((tb1[d] + ajout + retenue) > 5){ res[i] = 0; ajout = 0; retenue = 1; --d;}
            else { res[i] = tb1[d] + ajout + retenue; --d; ajout = 0; retenue = 0;}
        }
        else{ res[i] = ajout + retenue; ajout = 0; retenue = 0; }
    }
    return res;
}

int power(int base, int exposant){
    int i, res = base;
    for(i = 1; i < exposant; ++i){res = res * base;}
    return res;
}

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
                if(a+i+j == sommeVal){ 
                    res = ajoutEnTete(res, 
                            a*power(10, calculTailleEntier(i)+calculTailleEntier(j))
                            +
                            i*power(10, calculTailleEntier(j))
                            +
                            j
                        ); 
                }
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
        if(taille(ListeAnalyse[i]) > 3){return i+1;}
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
        for(i=0; i < 3; ++i){ ListeAnalyse[tab[i] - 1] = concateneListe(ListeAnalyse[(tab[i]-1)], analyse(tab[i], tab)); }
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

/*retourne -1 si val_noeud n'est pas un noeud externe*/
int estNoeudExterne(int val_noeud, liste * externeNoeud){return getPosition(externeNoeud, val_noeud);}

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
    printf("generateAllValue: Voici la liste de valeurs de noeud avant le calcul de tous les arrangements:\n");
    afficheListe(l); printf("\n");
    glist * res = NULL;
    liste * tmp = l, * generatedListe = NULL;
    while(tmp != NULL){
        generatedListe = AllArrangement(tmp->value);
        if(res == NULL) {res = g_ajoutTete(res, generatedListe, NULL);}
        else{ g_ajoutFin(res, generatedListe, NULL); }
        tmp = tmp->l;
    }
    printf("________________________________________________________________\n\
            Voici le tableau de valeurs des noeuds après le calcul des arrangements:\n");
    g_afficheList(res, afficheListe68);
    printf("generateAllValue: fin de la fonction\n");
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

/*Mettre en tableau toutes les branches. Chaque branche est une valeur entière*/
void mettreEnTableau(glist * possibleBranche){
    brnchTbl_length = g_listLongueur(possibleBranche);
    if(brnchTbl_length == 0) {printf("mettreEnTableau: la liste en entrée est vide, sortie en échec."); return;}
    /*Chaque élément de possibleBranche contient une liste d'entier de 6 éléments*/
    brnchTbl_length *= 6;
    if(brancheTable != NULL) {free(brancheTable);}
    brancheTable = malloc(brnchTbl_length * sizeof(int));
    glist * pcr = possibleBranche;
    liste * tmp = NULL;
    int i = 0, j;
    for(i=0; i < brnchTbl_length; ++i){ brancheTable[i] = 0; }
    i = 0;
    while(pcr != NULL){
        tmp = (liste *)pcr->elt;
        while(tmp!=NULL){
            brancheTable[i] = tmp->value;
            tmp = tmp->l; ++i;
        }
        //printf("mettreEnTableau: brancheTable = ");
        for(j=0; j<i; ++j){printf("%d ", brancheTable[j]);}
        printf("\n");
        pcr = pcr->next;
    }
}

/*2ème tri qui vérifie que le 1er digit de chaque branche est son noeud externe
 * si la fonction retourne 1*/
int firstDigitIsExtern(liste * lst, liste * nxtrn){
    liste * prcr = lst;
    int * tmp = NULL;
    while(prcr != NULL){
        tmp = decompose_node(prcr->value);
        if(EstPresent(nxtrn, tmp[0]) != 0){
            //printf("firstDigitIsExtern: le noeud %d n'est pas le noeud externe de %d\n", tmp[0], prcr->value);
            //printf("firstDigitIsExtern: echec de la liste : "); afficheListe(lst); printf("\n");
            free(tmp); tmp = NULL;
            return 1;
        } 
        free(tmp); tmp = NULL;
        prcr = prcr->l;
    } 
    return 0;
}

/*Génère toutes les solutions potentielles du problème*/
glist * gatherPotentialSolution(glist * possibleBranche){
    glist * solTab = NULL;
    int passIt = 0, i, limitNextValue = 0, solLen = 0;
    if(NumberOfNodes == 6) {limitNextValue = 555; solLen = 3;} else {limitNextValue = 55555; solLen = 5;}
    //la variable res permet d'encoder un index afin de récupérer chaque branche du magic gong
    int * res = malloc(solLen*sizeof(int));
    for(i=0; i<solLen; ++i){res[i]=0;}
    liste * etudeSol = NULL, * extNode = NULL;

    mettreEnTableau(possibleBranche);
    do{
        freeListeAnalyse();
        /*res <= 555; brancheTable a 18 éléments donc res[i] + i*6 < 18 
         * puisque max(res[i] + i*6) = 17*/
        for(i=0; i<solLen; ++i){ etudeSol = ajoutEnQueue(etudeSol, brancheTable[(res[i]+i*6)]); }
        construireListeAnalyse(etudeSol);
        passIt = tabToInt(res, solLen);
        if(saturationNoeud() == 0){ 
            extNode = noeudsExternes();
            if(taille(etudeSol) != taille(extNode)){
                supprimeListe(etudeSol); etudeSol = NULL; 
                supprimeListe(extNode); extNode = NULL; 
            }
            else{
                if(firstDigitIsExtern(etudeSol, extNode) == 0){
                    solTab = g_ajoutTete(solTab, etudeSol, NULL);
                    printf("gatherPotentialSolution: la liste "); afficheListe(etudeSol);
                    printf("a été ajouté à la liste de solution\n");
                    etudeSol = NULL; 
                    supprimeListe(extNode); extNode = NULL; 
                }
                else{
                    printf("gatherPotentialSolution : la liste "); afficheListe(etudeSol);
                    printf(" n'a pas les noeuds externes en 1ère position\n");
                    etudeSol = NULL; 
                    supprimeListe(extNode); extNode = NULL; 
                }
            }        
        } 
        else{
           // printf("gatherPotentialSolution: La liste : "); 
           // afficheListe(etudeSol);  printf(" est saturée et passIt = %d \n", passIt);
            supprimeListe(etudeSol); etudeSol = NULL; 
        }
    }while((res = nextValueBase6(passIt, limitNextValue)) != NULL);
    
    return solTab;
}

/*Hypothèse : on suppose que la 1ere valeur de chaque branches est un noeud externe
*On retourne la position de la branche ayant le plus petit noeud externe*/
int positionMinExterne(liste * lst){ 
	int * tmp = NULL, val = lst->value, pos=0, firstNode = 0;
   tmp = decompose_node(val);
   firstNode = tmp[0];
	liste * lt = lst;
	while(lt != NULL){
      val = lt->value;
		tmp = decompose_node(val);
		if(firstNode >= tmp[0]) {firstNode = tmp[0]; pos = getPosition(lst, val);}
		free(tmp); tmp = NULL;
		lt = lt->l;
	}
   return pos;
}

/*Cette fonction nous permet de voir si la valeur en 1er argument
 * est en 2ème position de la branche indiqué par le 2ème argument
 * retourne 1 si v1 est en 2ème position dans la branche, sinon 0*/
int isValScdPos(int v1, int branche){
    int * tb = decompose_node(branche);
    if(v1 == tb[1]){free(tb); return 1;}
    free(tb);
    return 0;
}

/*Cherche la branche de la liste qui aura val comme 2ème valeur*/
int findElement(int val, liste * lst){
    liste * tmp = lst;
    while(tmp != NULL){
        if(isValScdPos(val, tmp->value)){return tmp->value;}
        tmp = tmp->l;
    }
    printf("findElement: comportement inattendu, la valeur -1 est retournée.\n");
    return -1;
}

/*générer les bonnes combinaisons pour avoir des magicGongRing.
 * Afin que le sens des aiguilles d'une montre soit respecté, il faut : 
 * que la dernière valeur d'une branche soit la 2ème valeur de la branche suivante*/
glist * magicGongRing(glist * solTab){
    glist * tmp = solTab, * res = NULL;
    int pos, *tb = NULL, tval = 0;
    liste * lst = NULL, *wrklst = NULL;
    //cette boucle sert construire les magicGong
    while (tmp != NULL){
        wrklst = (liste*)tmp->elt;
        //On récupère la place de la branche à mettre en 1er
        pos = positionMinExterne(wrklst);
        //Construit la 1ère branche
        tval = getValue(wrklst, pos);
        lst = ajoutEnTete(lst, getValue(wrklst, pos));
        //Construit la 2ème branche
        tb = decompose_node(tval);
        tval = findElement(tb[2], wrklst);
        lst = ajoutEnQueue(lst, tval);
        //Construction de la 3ème branche
        free(tb); tb = NULL;
        tb = decompose_node(tval);
        tval = findElement(tb[2], wrklst);
        lst = ajoutEnQueue(lst, tval);
        free(tb);
        res = g_ajoutTete(res, (void *) lst, NULL);
        lst = NULL;
        tmp = tmp->next;
    }
    return res;
}

char * brancheTochar(liste * lst){
//On doit d'abord calculer la taille de la branche
    liste * tmp = lst;
    int tl = 0;
    while(tmp != NULL){ tl += calculTailleEntier(tmp->value); tmp = tmp->l; }
    char * res = malloc((tl+1)*sizeof(char));
    res[0]='\0';
    tmp = lst;
    while(tmp != NULL){ res = strcat(res, intToString(tmp->value)); tmp = tmp->l;}
    printf("brancheTochar: voici la chaine de caractère obtenu : %s\n", res);
    return res;
}

/*On compare b1 à b2. Si b1 est plus grand on renvoie 1 si plus petit -1
 * si égalité 0*/
int compareString(char * b1, char * b2){
   int tb1 = strlen(b1), tb2 = strlen(b2);
   if(tb1 > tb2){return 1;}
   if(tb1 < tb2){return -1;}
   if(tb1 == tb2){
       if(strncmp(b1, b2, tb1) > 0){return 1;}
       if(strncmp(b1, b2, tb1) < 0){return -1;}
   }
   return strncmp(b1, b2, tb2);
}

liste * trouveMax(glist * allSol){
    char *smax = NULL, *sanalyse = NULL;
    glist * tmp = allSol->next;
    liste * lmax = (liste *) allSol->elt;
    while(tmp != NULL){
        smax = brancheTochar(lmax); sanalyse = brancheTochar((liste *)tmp->elt);
        if(compareString(smax, sanalyse) <= 0){ lmax = (liste *)tmp->elt;}
        tmp = tmp->next;
        free(smax); free(sanalyse);
        smax = NULL; sanalyse = NULL;
    }
    return lmax;
}

/*allvalues est une liste de listes, chacune de ces listes est de taille 6
 * En fonction de ces informations on récupère l'élément adéquat*/
int getElement68(glist * allvalues, int next_elt){
    int numListe = next_elt/6, placeGlist = next_elt%6;
    glist * tmp = allvalues; liste * lst = NULL;
    int cpt = 0;
    while(cpt < numListe){tmp = tmp->next; ++cpt;}
    lst = (liste *)tmp->elt;
    return getValue(lst, placeGlist);
}

/*Fonction pour permettre d'identifier un cycle dans une solution
 * arguments: la liste qu'on souhaite étendre et l'élément à partir duquel vérifier les cycles
 * si retour 1 alors au moins un cycle est présent, si retour 0 pas de cycle*/
int cyclePresent(glist * allvalues, liste * etud, int next_elt){
    int j, * tb = NULL, brch = 0;
    liste * tmp = etud, * tr = NULL;
    while(tmp != NULL){
        brch = getElement68(allvalues, tmp->value);
        tb = decompose_node(brch);
        for(j=0; j<3; j++){tr = ajoutEnTete(tr, tb[j]);}
        tmp = tmp->l;
    }
    brch = getElement68(allvalues, next_elt);
    tb = decompose_node(brch);
    //on vérifie si le 1er terme et le dernier terme de la branche next_elt 
    //sont bien absents des autres branches de etud
    if(EstPresent(tr, tb[0]) == 0 || EstPresent(tr, tb[2]) == 0){ return 1; }
    return 0;
}

/*déterminer si le dernier terme de la dernière branche est bien présente
 * dans un groupe de branches 
 * lstBrch : le dernier nombre de la dernière branche
 * grpBrch : les nombres qui composent chaque branche du groupe
 * si retour 1 alors il y a discrimination, sinon 0*/
int discrimination(int lstBrch, int grpBrch){
   int * tb = decompose_node(grpBrch);
   if(tb[0] == lstBrch || tb[1] == lstBrch || tb[2] == lstBrch) {return 0;}
   return 1;
}

/*Lien de branchement : 
* 1 - il y a lien de branchement si le dernier nombre de la dernière branche 
* est égale au 2ème nombre de la branche qu'on veut ajouter. Si retour 1 alors il y a branchement
* si retour 0 il n'y a pas de lien de branchement*/
int lienBranchement(int lstBrch, int middleNumber){
    int * tb = decompose_node(lstBrch);
    if(tb[2] == middleNumber){free(tb); return 1;}
    return 0;
}

/*Return l'indice du 1er élément de l'étage suivant*/
int etage_plus_1(int next_elt){
    if(next_elt%6 == 0){return (next_elt + 6);}
    else { return (next_elt += 6 - (next_elt%6)); }
}

/*calculer l'étage de l'élément*/
int getEtage(int next_elt){return (next_elt/6)+1;}

/*Une fonction qui renvoie une valeur next_elt pour une branche donnée dans allvalues*/
int pb68_getPosition(int branchVal, glist * allvalues){
    int res = 0, posLg = 0;
    glist * tmp = allvalues;
    while(tmp != NULL){
        if(EstPresent((liste*)tmp->elt, branchVal) == 0){
            res = posLg*6 + getPosition((liste*)tmp->elt, branchVal);
            return res ; 
        } 
        tmp = tmp->next;
        ++posLg;
    }
    return res;
}

/*la fonction est récursive, elle s'appelle quand elle a ajouté ou retirer un élément à la liste
 * allvalues : la totalité des branches possibles, 
 * etud : la solution en cours de calcul, les éléments de la liste sont de type next_elt (une valeur
 * entière permettant d'identifier un élément dans allvalues) 
 * next_elt : la place à partir d'où commencer les tests. Attention next_elt correspond à la position
 * de la branche si elles étaient toutes rangées dans un tableau à une dimension*/
glist * getPotentialSolution(glist * allvalues, liste * etud, glist * potentialSolution, int next_elt){
    int tAllValue = g_listLongueur(allvalues), tetud = taille(etud), lim = tAllValue*6 - 1, debut = 0, parcours; 
    short int tmp;
    etud = NULL; //la liste de solution contient l'emplacement des branches

    while(tAllValue - getEtage(debut) >= 4){//condition d'arrêt, quand il reste moins de 5 groupes de branches pas encore analysés 
        etud = ajoutEnQueue(NULL, getElement68(allvalues, debut));//On considère que toutes les solutions ont été vérifiées. On est un peu fébrile encore dessus
        parcours = 0;
        while(parcours <= lim && tetud < 5){
            if(cyclePresent(allvalues, etud, parcours)){ 
                if(parcours == lim){
                    parcours = (lastElement(etud) == lim) ? 0 : lastElement(etud) + 1; 
                    etud = supprElt(etud, lastElement(etud));
                    if(taille(etud) == 0){ break;}
                }
                else {parcours = etage_plus_1(parcours);}
            } 
            else {
                if(discrimination(getElement68(allvalues, lastElement(etud)), getElement68(allvalues, parcours))){
                    parcours = etage_plus_1(parcours);
                }
                else {
                    tmp = decompose_node(getElement68(allvalues, parcours))[1];
                    if(lienBranchement(getElement68(allvalues, lastElement(etud)), tmp)){
                        etud = ajoutEnQueue(etud, parcours);
                        parcours = 0;
                        if(taille(etud) == 5){ 
                            potentialSolution = g_ajoutTete(potentialSolution, (void*)recopie(etud), NULL); 
                            parcours = (lastElement(etud) == lim) ? 0 : lastElement(etud) + 1; 
                            etud = supprElt(etud, lastElement(etud)); 
                        }
                    }
                    else {
                        if(parcours == lim){
                        parcours = lastElement(etud) + 1; 
                        etud = supprElt(etud, lastElement(etud));
                        }
                        else {++parcours;}
                    }
                }
            }
        }
        ++debut;
        etud = NULL;
    }
    return potentialSolution;
}    

int main(int argc, char ** argv){
    /*________________________________________vérification des entrées___________________________________*/
    int i, j, res;
    liste * ret = NULL, * tmp = NULL, * lmax = NULL, * lwork = NULL;
    char * smax = NULL, * sanalyse = NULL;
    glist * possibleBranche = NULL, * solTab = NULL, * allSol = NULL, * allMax = NULL;
    if(argc == 2){
        if(sscanf(argv[1], "%d", &NumberOfNodes) != EOF){} 
        else{printf("Mauvais argument %s\nEchec du traitement\n", argv[1]); 
            return 1;
        }
    }
    else {printf("Mauvais nombre d'argument\nUsage : ./myExe 6 ou ./myExe 10\n"); return 1;}
    /*____________________________tests d'une des fonctions majeures pour l'arrangement__________________*/
    i = 123;
    //while(i < 321){ printf("nextGreaterValSameDigit(%d) = %d\n", i, nextGreaterValSameDigit(i)); i=nextGreaterValSameDigit(i);}
    /*________________________________________Début de la solution_______________________________________*/
    int max = NumberOfNodes + (NumberOfNodes -1) + (NumberOfNodes - 2); 
    /*somme des 2 noeuds les plus grands; sans solution pour le problème 68*/
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
            possibleBranche = generateAllValue(ret);
            printf("ci-dessous le tableau complet pour la valeur %d\n", i);
            //afficheTab(tab);
            solTab=gatherPotentialSolution(possibleBranche);
            solTab=getPotentialSolution(possibleBranche, lwork, allSol, 0);
            printf("___________________Solutions potentielle pour %d________________________\n", i);
            g_afficheList(solTab, afficheListe68);
            printf("_____________Solutions avec bon ordre des branches %d___________________\n", i);
            allSol = magicGongRing(solTab);
            g_afficheList(allSol, afficheListe68);
            if(allSol != NULL){
                lmax = trouveMax(allSol);
                allMax = g_ajoutTete(allMax, (void*) recopie(lmax), NULL);
            }
            g_freeGenList(solTab, vfreeListe);
            g_freeGenList(allSol, vfreeListe);
            printf("__________________________Fin pour valeur de branche %d___________________________________________\n",i);
        }
        else{printf("la valeur %i n'a pas de solution avec le noeud %d\n", i, res);}
        supprimeListe(ret); ret = NULL;
        g_freeGenList(possibleBranche, vfreeListe);
        possibleBranche = NULL;
    }
    if(allMax != NULL){
        printf("Voici la solution max : "); afficheListe(trouveMax(allMax)); printf("\n");
        g_freeGenList(allMax, vfreeListe);
    }
    return 0;
}
