#include <stdio.h>
#include <string.h>

int compteLettre(char * mot, int *compteur){
 	int longueur = 0;
	int taillePropre = 0;
 	longueur = strlen(mot);
 	for (int i = 0; i <= longueur; i++){
		if (mot[i] > 47){(*compteur)++; taillePropre++;}
	}	
	return taillePropre;
}

void calcul(){
	int centaine, dizaine, reste, unite = 0; 
	int incr = 0;
	char mot[100];
	char firstVingt[21][50]={"", "one", "two", "three", "four", "five", "six", "seven"
		  , "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen"
		  , "sixteen", "seventeen", "eighteen", "nineteen", "twenty"};

	char tabDecimal[10][50]={"", "ten", "twenty", "thirty", "forty", "fifty"
		  , "sixty", "seventy", "eighty", "ninety"};

	for (int i = 1; i <= 1000; i++){
			if( i <= 20) {
				sprintf(mot, "%s", firstVingt[i]);
				printf("%d: %s # la taille est donc %d\n", i, mot, compteLettre(mot, &incr));
				//compteLettre(mot, &incr);
			}
			if( i < 100 && i > 20 ){
				dizaine = i / 10; reste = i % 10;
				sprintf(mot, "%s-%s", tabDecimal[dizaine], firstVingt[reste]);
				printf("%d: %s # la taille est %d\n", i, mot, compteLettre(mot, &incr));
				//compteLettre(mot, &incr);
			}
			if (i >= 100 && i < 1000 && i % 100 == 0 ){
				centaine = i / 100;
				sprintf(mot, "%s hundred", firstVingt[centaine]);
				printf("%d: %s hundred # la taille est donc %d\n", 
					i, firstVingt[centaine], compteLettre(mot, &incr));

			}
			if(i >= 100 && i < 1000 && i % 100 != 0){
				centaine = i / 100; reste = i % 100; 
				if (reste > 20) {dizaine = reste / 10; unite = reste % 10;
				sprintf(mot, "%s hundred and %s-%s", firstVingt[centaine], tabDecimal[dizaine], firstVingt[unite]);
				printf("%d: %s hundred and %s-%s # la taille est donc %d\n", 
					i, firstVingt[centaine], tabDecimal[dizaine], firstVingt[unite], compteLettre(mot, &incr));
				
				}else{dizaine = reste; unite = 0;
					sprintf(mot, "%s hundred and %s", firstVingt[centaine], firstVingt[dizaine]);
					printf("%d: %s hundred and %s # la taille est donc %d\n", 
					i, firstVingt[centaine], firstVingt[dizaine], compteLettre(mot, &incr));
				}  
			}
			if( i == 1000){
				sprintf(mot, "one thousand");
				printf("%d: %s # la taille est %d\n", i, mot, compteLettre(mot, &incr));
				//compteLettre(mot, &incr);
			}
	}
	printf("The total number of letter use is %d\n", incr);
}

int main(){
	calcul();
}
