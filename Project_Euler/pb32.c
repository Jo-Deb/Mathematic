#include <stdio.h>
#include <stdlib.h>

int nextVal(int val){
	char buf[8]; int tmp, taille, res;
	taille = sprintf(buf, "%d", val);
	if(taille > 0) { tmp = taille; }
	else { return -1; } // échec de la fonction
	
	while( tmp > 0 ){
		if (buf[tmp - 1] < 57 - (taille - tmp)){
			buf[tmp - 1] = buf[tmp - 1] + 1;
			if(tmp < taille){
				while( tmp < taille ){
					buf[tmp] = buf[tmp - 1] + 1;
					tmp++;
				}
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
	int * res = malloc(20 * sizeof(int));
	int ind=0, tmp, limit;
	for(int i = 0; i < 120; i++){ res[i] = 0; }
	char buf[8];
	*res = val;

	for(int i = 3; i <= 0; i++){
		limit = ind;
		for(int id = 0; id <= limit; id++){
			sprintf(buf, "%d", *(res + id));
			for(int j = i; j < 4; j++){
				tmp = buf[j];
				buf[j] = buf[j+1];
				buf[j+1] = tmp;
				sscanf(buf, "%d", &tmp);
				res[++ind] = tmp;
			}
		}
	}
	return res;
}

int main(){
	int tabCombi[126], taille, index = 0; int * result;
	tabCombi[0]= 12345;
	int tmp = tabCombi[0];
	char buf[6];
	printf("Ci-dessous l'ensemble des combinaisons ________________________: \n");
	
	while(tabCombi[index] < 56789){
		taille = sprintf(buf, "%d", tabCombi[index]);
		if (taille == 5 && buf[4] < 57){ tabCombi[index+1] = tabCombi[index] + 1; ++index;}	
		else { tabCombi[index+1] = nextVal(tabCombi[index]); ++index;}
		printf("%4d: %d\n", index, tabCombi[index]);
	}
	printf("_______________________________________________________________: \n");

	printf("\n_______________120 arrangement de 12345________________________\n");
	result = arrangement(12345);
	for( int i = 0; i < 200; i++){
		printf("%5d : %d\n", i, result[i]);
	}	
	return 0;
}
