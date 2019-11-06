#include <stdio.h>
#include <stdlib.h>

int estPremier(int elt){
	int max = 1;
	while(max*max < elt){ max++;}

	for(int i = 2; i <= max; i++){
		if(elt % i == 0 && i != elt){ return 0;}
	}
	return 1;
}

int crible (int elt, int * power){
	int max = 1, tmp, quotient, maxD = 0, maxP = 0, tPower = 0;
	*power = 0; 
	while(max*max < elt){ max++;}
	/*On calcule si elt s'écrit comme a puissance power*/
	for(int i = 2; i <= max; i++){
		tmp = i;
		*power = 1;
		while(elt % tmp == 0){
			quotient = elt / tmp;
			if(quotient == 1){ return i;}
			tmp *= i; (*power)++;
		}
	}
	*power = 0;
	return 0;
}

int epuration(int r, int pr){
/*r: racine, pr: comme puissance racine*/
	int limit = 100, tmp, cmpt = 0;
	int wrk[pr][limit];
/* remplissage du tableau */

	for(int i = 0; i < pr; i++){
		tmp = 1;
		for(int j=0; j < i+1; j++){tmp *= r;}
		wrk[i][0] = tmp;
		for(int k = 1; k < limit; k++){ wrk[i][k] = (k+1)*(i+1); printf("%2d ", wrk[i][k]);}
		printf("\n");
	}
/* Suppression des nombres apparaissant plusieurs fois */
	printf("=================================================\n");
	for(int i = 0; i < pr; i++){
		for(int j = 1; j < limit; j++){
			while(wrk[i][j] == 0){++j;}
			for(int k = i+1; k < pr; k++){
				for(int l = 1; l < limit; l++){ if(wrk[i][j] == wrk[k][l]){ wrk[k][l] = 0; } }
			}
		}
	}
	for(int i = 0; i < pr; i++){
		for(int j = 1; j < limit; j++) {printf("%1d ", wrk[i][j]);}
		printf("\n");
	}
	for(int j = 1; j < limit; j++){ if(wrk[pr-1][j] != 0){ cmpt++;} }
	return cmpt;
}

int main(){
	int compteur = 0; int power = 0;
	int ajout, cpt = 0, b = 100, limite, tmp, calPower;

	for(int a = 2; a <= b; a++){
		if( estPremier(a) == 1) {cpt = b-1; compteur += cpt; printf("pour %d, %d valeurs ajoutées\n", a, cpt);}
		else{tmp = crible(a, &power);
			if(tmp == 0){ cpt = b-1; compteur +=cpt; printf("pour %d, %d valeurs ajoutées\n", a, cpt);}
			else{ajout = epuration(tmp, power);
				/*limite = b / power;
				ajout = b - limite; cpt = ajout; compteur += cpt;
				printf("===============================================================================================\n");
				printf("%d = %d^%d et le nombre de valeurs ajoutées est %d : ", a, tmp, power, cpt);
				for(int c = limite+1; c <= b; c++){ printf("%d^%d ", tmp, power*c);}
				printf("===============================================================================================\n");*/
				printf("%d = %d^%d et le nombre de valeurs ajoutées est %d\n", a, tmp, power, ajout);
				compteur += ajout;
			}
		}
	}
	printf("le nombre de valeurs distinctes est %d\n", compteur);

/*Code de vérification
	for(int a = 2; a <= b; a++){
		printf("%d: ", a);
		for(int c = 2; c<=b; c++){
			calPower = 1;
			for(int d = 1; d<=c; d++){ calPower *= a;}
			printf("%d ", calPower);
		}	
		printf("\n");
	} */
	return 0;
}