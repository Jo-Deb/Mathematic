#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Project_Euler/genList.h"

int estCarre(int d){
	if(d == 1){return 0;}
	int i, tmp = 0;
	for(i=2; tmp < d; ++i){
		tmp = i * i;
		if(tmp == d){return 0;}
	}
	return 1;
}

void show_couple(void * tab){ 
    int * tmp = (int *) tab;
    printf("x=%d, y=%d et d=%d et N=%d", tmp[0], tmp[1], tmp[2], abs(tmp[0]*tmp[0] - (tmp[2]*tmp[1]*tmp[1])));
}

int * solution(int * t1, int * t2){
   int * res = malloc(3*sizeof(int));
   res[0] = (abs(t1[0]-t2[0])), res[1] = abs(t1[1]-t2[1]), res[2] = t1[2];
   return res;
}

glist * treatList(glist *l){
    glist * res = NULL, * tmp = l, *l2=NULL;
	 int * t1=NULL, * t2=NULL; 
	 while(tmp){
		  t1 = (int*) tmp->elt;
		  l2 = tmp->next;
		  while(l2){
			   t2 = (int*) l2->elt;
			   res = g_ajoutTete(res, solution(t1, t2), NULL);
            if(l2->next == NULL){l2 = NULL;} else {l2 = l2->next;}
		  }
        if(tmp->elt == NULL){tmp = NULL;} else {tmp = tmp->next;}
    }
	 return res;
}

int main(){
	int i, j, pen;
   glist * l1=NULL, * l2=NULL, * l3=NULL, * l4=NULL, * l5=NULL;
	double root, decimal, interval, tmp, i1=1.0/5.0, i2=2.0/5.0, i3=3.0/5.0, i4=4.0/5.0; //[0, i1[, [i1, i2[ ; [i2, i3[ ; [i3; i4[ ; [i4, 1[ 

	for(i = 2; i < 100; ++i){
		while(estCarre(i) == 0){++i;}
		root = sqrt(i);
		printf("############################################Racine(%d)###############################################\n", i);
		printf("Les intervalles sont : [0, %4lf[ [%4lf, %4lf[ [%4lf, %4lf[ [%4lf, %4lf[ [%4lf, %d[\n", i1, i1, i2, i2, i3, i3, i4, i4, 1);
		for(j=1; j<=15; ++j){
			tmp = j*root;
         pen = (int) round(tmp);
			decimal = modf(tmp, &interval);
         int * tab = malloc(3*sizeof(int));
         tab[0] = pen, tab[1] = j, tab[2] = i;
			if(decimal < i1){
             printf("%lf a comme partie décimal %lf est dans l'intervalle i1 et la norme donne : %d \n", tmp, decimal, abs(pen*pen - (j*j)*i) );
             l1 = g_ajoutTete(l1, (void *)tab, NULL);
         }	
			if(decimal >= i1 && decimal < i2){
             printf("%lf a comme partie décimal %lf est dans l'intervalle i2 et la norme donne %d\n", tmp, decimal, abs(pen*pen - (j*j)*i) );
             l2 = g_ajoutTete(l2, (void *)tab, NULL);
         }	
			if(decimal >= i2 && decimal < i3){
            printf("%lf a comme partie décimal %lf est dans l'intervalle i3 et la norme donne %d\n", tmp, decimal, abs(pen*pen - (j*j)*i) );
             l3 = g_ajoutTete(l3, (void *)tab, NULL);
         }	
			if(decimal >= i3 && decimal < i4){
             printf("%lf a comme partie décimal %lf est dans l'intervalle i4 et la norme donne %d\n", tmp, decimal, abs(pen*pen - (j*j)*i));
             l4 = g_ajoutTete(l4, (void *)tab, NULL);
         }	
			if(decimal >= i4 && decimal < 1.0){
              printf("%lf a comme partie décimal %lf est dans l'intervalle i5 et la norme donne %d\n", tmp, decimal, abs(pen*pen - (j*j)*i));
             l5 = g_ajoutTete(l5, (void *)tab, NULL);
         }	
		}
      printf("liste originale l1: "); g_afficheList(l1, show_couple);
		printf("liste des couples pour l'intervalle i1: \n");
		g_afficheList(treatList(l1), show_couple);
      printf("liste originale l2: "); g_afficheList(l2, show_couple);
		printf("liste des couples pour l'intervalle i2: \n");
		g_afficheList(treatList(l2), show_couple);
      printf("liste originale l3: "); g_afficheList(l3, show_couple);
		printf("liste des couples pour l'intervalle i3: \n");
		g_afficheList(treatList(l3), show_couple);
      printf("liste originale l4: "); g_afficheList(l4, show_couple);
		printf("liste des couples pour l'intervalle i4: \n");
		g_afficheList(treatList(l4), show_couple);
      printf("liste originale l5: "); g_afficheList(l5, show_couple);
		printf("liste des couples pour l'intervalle i5: \n");
		g_afficheList(treatList(l5), show_couple);
		printf("#######################################################################################################\n");
		g_freeList(l1); g_freeList(l2); g_freeList(l3); g_freeList(l4); g_freeList(l5);
		l1 = l2 = l3 = l4 = l5 = NULL;	
	}
}
