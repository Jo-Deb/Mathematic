#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

/*le code ci-dessous a pour objectif de générer les différentes
 *combinaisons nécessaires à la résolution du pb31
 */


int main(){
	int tab[7] = {1, 2, 5, 10, 20, 50, 100};
	int t1 = 0, t2 = 0, pas = 2, tmp, limit = 7;

	while(t1 <= 7-1-pas){
		liste * l = NULL;
		for(int i = t1; i <= (t1 + pas-1); i++){
			l = ajoutEnQueue(l, tab[i]);
		}
		for(int i = (t1+pas); i <= limit - 1; i++){
			l = ajoutEnQueue(l, tab[i]);
			printf("\n");
			afficheListe(l);
			//printf("suppression de l'élément %d\n", tab[i]);
			l = supprElt(l, tab[i]);
			//printf("l'élément %d a été supprimé\n", tab[i]);
		}
		t1++;
		//printf("voici l'état de la liste avant suppression : ");
		//afficheListe(l);
		//printf("\n");
		//printf("suppression de la liste car t1 s'incrémente de 1\n");
		supprimeListe(l);
	}
	printf("\n");
	return 0;
}