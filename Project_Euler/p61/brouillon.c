/*Au niveau du main, il faut initier une nouvelle liste quand on se lance
avec un nouveau nombre

L'objectif est de construire une liste avec une suite de nombre 
qui répond à l'exercice 61, il faut donc que l'algorithme effectué 
par le main soit le suivant : 
	1 Obtenir un nombre triangulaire
	2 Retirer la valeur 0 de la liste d'index de fonction
	3 Si grace à la liste d'index de fonction on arrive à obtenir une liste
	non nulle, alors on ajoute le nombre triangulaire et la liste de nombre obtenu
dans la liste résultat
	4 A partir de la liste de nombre obtenu, on récupère un nombre qu'on supprime
		de la liste obtenue et on génère à partir de ce nombre, si possible, un
		nouvel élément pour la liste résultat.
	5 si un nouvel élément n'est pas possible, on en pioche un autre.
*/

/*
 *Pour ajouter une liste à une liste, il nous faut gérer une liste générique
 *et c'est cela la nouveauté, se renseigner sur le sujet.
*/

void afficheRacine(glist * res){
	glist * parcours = res;
	while(parcours != NULL){
		printf("%4d->[", *((int *)parcours->elt));
		afficheList(parcours->lst); printf("]");
		printf("\n  |\n");
		parcours = parcours->next;
	}
}


/*Au niveau de genereList il me faut calculer idx_fct_list en fonction
* de la liste générique.
*/
list * genereListe(int val, list * idx_fct_list){
	int n = getval61(val);
	int idx = getIdx61(val);
	int deuxPremierDigit = get2last(n);
	//Pour faire la boucle, il faut uniquement incrémenter les listes
	list * tmp = idx_fct_list;
	list * res = NULL;
	while(tmp!=NULL){res = concatList(res, gatherData(deuxPremierDigit, tmp->elt));}
	//suppression de l'idx dans la liste d'index de fonction
	idx_fct_list = supprimElt(idx_fct_list, idx);
	return res;
}
/* il faut refaire genereList à partir des arguments val et 
 * res (la liste générique). On parcourt res pour savoir quels id
 * doivent être éliminés de la liste
 */



list * genereList(int val, glist * res){
	list * tmp = initListFunc();
	list * lelt = idxToDelete(res);
}

//Ajouter une valeur et liste généréé à partir d'elle.
//Cette ajout sera fait en tête de la liste de résultat.
void ajoutDansRes(int val, list * racine, glist * res){
	int * pt = malloc(sizeof(int)); *pt = val;
	g_ajoutTete(res, pt, racine);
}

//On suppose que la liste donnée en argument n'est pas vide.
//De plus on retire la valeur de la liste en tête.
int getNextVal(glist * res){
	glist * head = res;
	if(head->lst == NULL){
		res = g_supprimElt(res, head->elt);
		return getNextVal(res);
	}
	int result = 0;
	if((result = head->lst->elt) > 1000) {
		head->lst = supprimElt(head->lst, head->lst->elt);
		return result;
	}else{return result;}
}


//Afin de limiter la lourdeur des tests on appelle cette fonction si 
//si la liste racine n'est pas vide.
void deRacineAsommet(int val, list * racine, glist * res, list * idx_fct_list){
		int nextVal = 0;
		list * cur_list = NULL;
		ajoutDansRes(val, racine, res);
		while(res!=NULL && g_listLongueur(res) < 6){
			nextVal = getNextVal(res);
			cur_list = genereListe(nextVal, idx_fct_list);
			if(cur_list != NULL){ajoutDansRes(nextVal, cur_list, res);}
			afficheRacine(res);
		}
}


main(){
	int i = 1, val = 0;
	list * idx_fct_list = NULL, * cur_list;
	glist * res = NULL;
	//Test pour l'obtention des valeurs OK
	while( val < 10000){
		cur_list = NULL;
		val = 0;
		while (val < 1000 || get2last(val) < 10 ) {val = triangleNb(i); i++;}
		//arrivé à ce niveau, val est supposé avoir une valeur convenable pour
		//initier un run du programme
		printf("===================================================================\n");
		printf("main: Lancement d'un run avec la valeur %d\n", val);
		idx_fct_list = initListFunc();
		idx_fct_list = supprimElt(idx_fct_list, 0);
		cur_list = genereListe(val, idx_fct_list);
		if(cur_list != NULL){
			//appel d'une fonction qui va prendre cur_list et qui va essayer de remplir res
			//à partir de ça
			deRacineAsommet(val, cur_list, res, idx_fct_list);
		}
	}
}

