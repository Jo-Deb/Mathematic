#include<stdio.h>

void PremierJourDesMois(int tab[], int * comptage, short b, int * compteAnnee, int year){
	int mois[12]; int firstDay; int reste;
	for(int i = 0; i < 12; i++){
		firstDay = *compteAnnee + 1 + tab[0] - 1; //+1 car on entame le mois et - 1 car on ajoute les j-1 jours de 
		//décalage. Exemple le premier jour de l'an 2000 est un samedi, le 6ème jour de la semaine or nous considérons
		//qu'on démarre en début de semaine, on fait donc +5 pour se mettre au lundi.
		reste = firstDay % 7;
		if ( reste == 0){
			printf("first day of month %d of %d is a sunday \n", i+1, year);
			(*comptage)++;
		}else{printf("first day of month %d of %d is %d\n", i+1, year, reste);}

		if ( i + 1 == 9 || i + 1  == 4 || i + 1 == 6 || i + 1  == 11){ *compteAnnee += 30;} 
		if(i+1 == 2 && b == 1){*compteAnnee += 29;}
		if(i+1 == 2 && b == 0){*compteAnnee += 28;}
		if ( i + 1 != 9 && i + 1  != 4 && i + 1 != 6 && i + 1  != 11 && i+1 !=2){*compteAnnee += 31;}
	}
}

int main(){
	int tab[101]; //tableau des années pour récupérer le premier jour de la semaine de chaque mois.
	int year; tab[0] = 1; int reste;
	int compteAnnee = 365; int firstDay = 0; int comptage = 0;
	/*On rappelle que nous considérons le dimanche comme le 7ème jours de la semaine
	 *Dans le cas ou effectuerons des modulo 7 on aura: lundi 1, mardi 2, mercredi 3, jeudi 4, vendredi 5
	 *samedi 6, dimanche 0
	 */

	 printf("la liste des années bissectiles est :\n");
	 for(int i = 1; i < 101; i++){
	 	year = 1900 + i;
	 	firstDay = compteAnnee + tab[0];
	 	reste = firstDay % 7; 
	 	tab[i] = reste;
	 	if((year % 100 == 0 && year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)){
	 		//compteAnnee += 366;
	 		//printf("%4d: 366 jours, premier jour:  %2d\n", year, reste);
	 		PremierJourDesMois(tab, &comptage, 1, &compteAnnee, year);
	 	}else{
	 		//compteAnnee += 365;
	 		//printf("%4d: 365 jours, premier jour:  %2d\n", year, reste);
	 		PremierJourDesMois(tab, &comptage, 0, &compteAnnee, year);
	 	}
	 	printf("de 1901 à 2000 %d mois commencent un dimanche\n", comptage);
	 }
}