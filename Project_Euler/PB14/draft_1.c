#include <stdio.h>

unsigned int tab[1000000];/*Ne pas oublier d'initialiser le tableau dans le main*/

int collatz_suite(unsigned int origin){
	unsigned int debut = origin, genTerme = origin, stop=0;
	unsigned int pair=0, impair=0, nbrElt=1;
	if (genTerme == 1){stop = 1;}	

	while(stop != 1){
		if ( genTerme % 2 == 0){genTerme = genTerme / 2; pair=1;}
		else {genTerme = (3*genTerme+1)/2; impair = 1;}
		
	//printf("la valeur en cours de genTerme est %d\n", genTerme);
	
		if (genTerme < 1000000 && tab[genTerme] != 0 && pair==1){ nbrElt = tab[genTerme] + nbrElt; stop=1;}
		if (genTerme < 1000000 && tab[genTerme] == 0 && pair==1){ nbrElt = 1 + nbrElt;}

		if (genTerme < 1000000 && tab[genTerme] != 0 && impair==1){ nbrElt = tab[genTerme] + nbrElt + 1; stop=1;}
		if (genTerme < 1000000 && tab[genTerme] == 0 && impair==1){ nbrElt = 2 + nbrElt + 1;}
		
		if (genTerme >= 1000000 && pair==1){ ++nbrElt; }
		if (genTerme >= 1000000 && impair==1){ nbrElt = nbrElt + 2; }

		pair=0; impair=0;
	}
	return nbrElt;
}

int main(){
	unsigned int i, n=3, maxElt=0, tailleMax=0;
/* Initialisation du tableau */
	printf("Début du programme et initialisation du tableau tab\n");
	for (i=0; i < 1000000; i++){ tab[i] = 0;}
	tab[0]=0; tab[1]=1; tab[2]=2;
	printf("Début de la boucle sur n");
	while (n < 1000000){
		if( n % 2 == 0) tab[n]=tab[n/2] + 1; 	
		else { tab[n]=collatz_suite(n); }
		if (tab[n] > tailleMax){ tailleMax=tab[n]; maxElt=n;}
		if (n % 10000 == 0 ) {printf("la taille max est %d pour le nombre %d\n", tailleMax, maxElt);}
		++n;
	}	
}
