#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextVal(int val){
	char buf[8]; int tmp, taille, res;
	taille = sprintf(buf, "%d", val);
	if(taille > 0) { tmp = taille; }
	else { return -1; } // échec de la fonction
	
	while( tmp > 0 ){
		if (buf[tmp - 1] < 57 - (taille - tmp)){
			buf[tmp - 1] = buf[tmp - 1] + 1;
			if(tmp < taille){
				while( tmp < taille ){ buf[tmp] = buf[tmp - 1] + 1; tmp++; }
				if( sscanf(buf, "%d", &res) > 0){ return res; }
				else { printf("échec de la fonction nextval pour %d\n", val );
					return -1;
				}
			}
		}
		tmp--;
	}
	printf("échec de la fonction nextval pour %d\n", val );
	return -1;
}

int * arrangement(int val){
	int * res = malloc(24 * sizeof(int));
	int ind=0, tmp, limit, i, j, id;
	for(i = 0; i < 24; i++){ res[i] = 0; }
	char buf[8];
	*res = val;

	for(i = 2; i >= 0; i--){
		limit = ind;
		for(id = 0; id <= limit; id++){
			sprintf(buf, "%d", res[id]);
			for(j = i; j < 3; j++){
				tmp = buf[j]; buf[j] = buf[j+1]; buf[j+1] = tmp;
				sscanf(buf, "%d", &tmp); res[++ind] = tmp;
			}
		}
	}
	return res;
}

/*Renvoie un tableau contenant la moitié des diviseurs de val*/
int * mesDiviseurs(int val){
	int limit = 0, i, ind = 0, taille;
	while (limit * limit < val){ ++limit; }
	int * res = malloc((limit)*sizeof(int));
	for(i=0; i < limit; i++){ res[i] = 0; }

	for(i=2; i < limit; i++){ if( val % i == 0){ res[ind] = val/i; ++ind;} }
	return res;
}

/*Tester si l'argument est un produit pandigital*/
int panTest(int val, int * tabDiv){
	int i=0, j=0, k=0, m1, m2, present = 1;
	char buffer[10], tmp1[5], tmp2[5];
	//printf("ensemble des diviseurs pour %d :", val);
	//while(tabDiv[i] > 0){ printf("%d ", tabDiv[i]); i++;}
	//printf("\n"); i = 0;

	while(tabDiv[i] > 0){
		m1 = tabDiv[i]; m2 = val / m1;
		sprintf(buffer, "%d", val); sprintf(tmp1, "%d", m1); sprintf(tmp2, "%d", m2);
		strcat(buffer, tmp1); strcat(buffer, tmp2); 
		j = 57; //représentation ascii de 9 et 0 = 48
		while(j > 48 && present == 1){
			present = 0;
			while( buffer[k] != '\0'){ if(j == buffer[k]){present = 1;} k++;}
			k = 0; j--;
		}
		if(j==48){ printf("%d = %d * %d\n", val, m1, m2); return 0;}
		i++;
		printf("valeur du buffer pour %d : %s\n", val, buffer);
		while(k < 10){ buffer[k] = '\0'; k++;}
		printf("%s", buffer);
		k=0;
	}
	return 1;
}

int main(){
	int tabCombi[126], taille, index = 0; int * result, i, j, cpt = 0;
	tabCombi[0]= 1234;
	int tmp = tabCombi[0];
	char buf[5];
//	printf("Ci-dessous l'ensemble des combinaisons ________________________: \n");
	
	while(tabCombi[index] < 6789){
		taille = sprintf(buf, "%d", tabCombi[index]);
		if (taille == 4 && buf[3] < 57){ tabCombi[index+1] = tabCombi[index] + 1; ++index;}	
		else { tabCombi[index+1] = nextVal(tabCombi[index]); ++index;}
		//printf("%4d: %d\n", index, tabCombi[index]);
	}
	//printf("_______________________________________________________________: \n");

	//printf("\n_______________24 arrangements de 1234________________________\n");
	
	for(i=0; i < 126; i++){
		result = arrangement(tabCombi[i]);
		for(j=0; j < 24; j++){
		//printf("Opération en cours pour %d\n", result[j]);
		if( panTest(result[j], mesDiviseurs(result[j])) == 0){ cpt += result[j];}
		}
		//printf("Opération effectuée pour %d\n", tabCombi[i]);
	}
	printf("la somme totale donne : %d\n", cpt);

	return 0;
}
