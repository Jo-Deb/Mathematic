#include <stdio.h>
#include <stdlib.h>

#define HIGHCARD 			20
#define ONE_PAIR 			25
#define TWO_PAIR 			30
#define THREE_KIND 		    35
#define STRAIGHT			40
#define FLUSH 				45
#define FULL_HOUSE	    	50
#define FOUR_A_KIND	    	55
#define STRAIGHT_FLUSH  	60

char * retrieveValues(char * jeu){
	char * res = malloc(6*sizeof(char));
	int i;
	for(i=0; i<=9; i++){ if(i%2==0){res[i/2]=jeu[i];} }
	res[5]='\0';
	return res;
}

void triDescArray(char * tab, int taille){
 int i, j, tp;
 for(i=0;i<=taille-2;i++){
      for(j=i+1; j<=taille-1;j++){
         if(tab[i]>tab[j]){tp=tab[i]; tab[i]=tab[j]; tab[j]=tp;}
      }
   }
}

char * getTwoPairValues(char * jeu){
    int i, cpt, j, index=0;
    char * tab = retrieveValues(jeu);
    char * res = malloc(3*sizeof(char));
    triDescArray(tab, 5);

    for(i=0; i<=3; i++){
        cpt=1;
        for(j=i+1; j<=4; j++){if(tab[i]==tab[j]){++cpt;}}
        if(cpt==2){
            if(index==0){res[index]=tab[i];}
            if(index==1 && tab[i]!=res[index-1]){res[index]=tab[i];}
        }
        cpt=0;
    }
    return res;
}

void affiche(char * tab, int taille){
	int i;
	for(i=0; i<taille; i++){ printf("%c ", tab[i]);}
	printf("\n");
}

int bestHighCard(char * jeu1, char * jeu2){
	char * pone = retrieveValues(jeu1);
	char * ptwo = retrieveValues(jeu2);
	int i;
	
	for(i=0; i<5; i++){ 
		if(jeu1[i]>jeu2[i]){return 1;} 
		if(jeu1[i]<jeu2[i]){return 2;} 
	}
	return 0;	
}

/*highCard retourne la valeur la plus grande de la main*/
int highCard(char * jeu, int index){
	int tmp[5]; int i, j, tp;
	for(i=0; i<=9; i++){
		if(i%2==0){
			switch(jeu[i]){
				case '2': tmp[i/2]=2; break;
				case '3': tmp[i/2]=3; break;
				case '4': tmp[i/2]=4; break;
				case '5': tmp[i/2]=5; break;
				case '6': tmp[i/2]=6; break;
				case '7': tmp[i/2]=7; break;
				case '8': tmp[i/2]=8; break;
				case '9': tmp[i/2]=9; break;
				case 'T': tmp[i/2]=10; break;
				case 'J': tmp[i/2]=11; break;
				case 'Q': tmp[i/2]=12; break;
				case 'K': tmp[i/2]=13; break;
				case 'A': tmp[i/2]=14; break;
				default : break;
			}	
		}	
	}
	//Tri du tableau et envoie de la plus grande valeur.
	for(i=0;i<=3;i++){
		for(j=i+1; j<=4;j++){
			if(tmp[i]<tmp[j]){tp=tmp[i]; tmp[i]=tmp[j]; tmp[j]=tp;}
		}
	}
	return tmp[index-1];
}

//Deux cartes de meme valeur
char onePair(char * jeu){
	int i, j, cpt=0; 
    char * val = retrieveValues(jeu);
    triDescArray(val, 5);
	for(i=0; i<=4; i++){
		cpt = 0;
		for(j=0; j<=4; j++){
			if(val[j]==val[i]){cpt++;}	
		}
		if(cpt==2){free(val); return val[i];}
	}
	free(val);
    return 0;
}

int twoPair(char * jeu){
	int i, j, cpt=0, nbr_pair=0;
    char * val = retrieveValues(jeu);
    triDescArray(val, 5);
	for(i=0; i<=4; i++){
		cpt = 1;
		for(j=i+1; j<=4; j++){
			if(val[i] == val[j]){cpt++;}
		}
		if(cpt>=2){nbr_pair++;}
	}
	if(nbr_pair == 2){free(val); return 1;}
	free(val); 
    return 0;
}

char kind(char * jeu, int kd){
   int i, j, cpt=0;
   char * val = retrieveValues(jeu);
   triDescArray(val, 5);
   for(i=0; i<=4; i++){
      cpt = 1;
      for(j=i+1; j<=4; j++){
         if(val[j]==val[i]){cpt++;}
      }
      if(cpt==kd){free(val); return val[i];}
   }	
    free(val);
    return 0;
}

int straight(char * jeu){
   int tmp[5]; int i, j, tp;
   for(i=0; i<=9; i++){
      if(i%2==0){
         switch(jeu[i]){
            case '2': tmp[i/2]=2; break;
            case '3': tmp[i/2]=3; break;
            case '4': tmp[i/2]=4; break;
            case '5': tmp[i/2]=5; break;
            case '6': tmp[i/2]=6; break;
            case '7': tmp[i/2]=7; break;
            case '8': tmp[i/2]=8; break;
            case '9': tmp[i/2]=9; break;
            case 'T': tmp[i/2]=10; break;
            case 'J': tmp[i/2]=11; break;
            case 'Q': tmp[i/2]=12; break;
            case 'K': tmp[i/2]=13; break;
            case 'A': tmp[i/2]=14; break;
            default : break;
         }
      }
   }
   //Tri du tableau et envoie de la plus grande valeur.
   for(i=0;i<=3;i++){
   	for(j=i+1; j<=4;j++){
   		if(tmp[i]<tmp[j]){tp=tmp[i]; tmp[i]=tmp[j]; tmp[j]=tp;}
   	}
   }
   for(i=0; i<=3; i++){
		if(tmp[i]-tmp[i+1]!=1){return 0;}
	} 
	return 1;
}

int flush(char * jeu){
	int i, j=0;
	char suit = jeu[1];
	for(i=0; i<=9; i++){
		if(i%2==0){i++;}
		if (jeu[i]==suit){j++;}
	}
	if(j==5){return 1;}
	return 0;
}

int fullHouse(char * jeu){
	char c = onePair(jeu);
	if(c==0){return 0;}
	char e = kind(jeu, 3);
	if(e==0){return 0;}
	if(c==e) {return 0;}
	return 1;
}

int straightFlush(char * jeu){
	if(straight(jeu) >= 1){
		if(flush(jeu) >= 1) {return 1;}
	}
	else {return 0;}
    return 0;
}

int value(char * jeu){
	if(fullHouse(jeu) >= 1){return 7;}
	if(flush(jeu) >= 1){return 6;}
	if(straight(jeu) >= 1){return 5;}
	if(kind(jeu, 3) >= 1){return 4;}
	if(twoPair(jeu) >= 1){return 3;}
	if(onePair(jeu) >= 1){return 2;}
	if(highCard(jeu, 1) >= 1){return 1;}
    return 0;
}

char * copietab(char * original, char * copie, int taille){
	copie = malloc(taille*sizeof(char));
	int i; 
	for(i=0; i<taille; i++){copie[i]=original[i];}
	return copie;
}


int translate(char c){
    int res=c;
    switch(c){
        case '2': res=2; break;
        case '3': res=3; break;
        case '4': res=4; break;
        case '5': res=5; break;
        case '6': res=6; break;
        case '7': res=7; break;
        case '8': res=8; break;
        case '9': res=9; break;
        case 'T': res=10; break;
        case 'J': res=11; break;
        case 'Q': res=12; break;
        case 'K': res=13; break;
        case 'A': res=14; break;
        default : break;
    }
    return res;
}


int analyse(char * jeu){
	if(straightFlush(jeu)   >  0){ return STRAIGHT_FLUSH;}
	if(kind(jeu, 4)         >  0){ return FOUR_A_KIND;}
	if(fullHouse(jeu)       >  0){ return FULL_HOUSE;}
	if(flush(jeu)           >  0){ return FLUSH;}
	if(straight(jeu)        >  0){ return STRAIGHT;}
	if(kind(jeu, 3)         >  0){ return THREE_KIND;}
	if(twoPair(jeu)         >  0){ return TWO_PAIR;}
	if(onePair(jeu)         >  0){ return ONE_PAIR;}
	if(highCard(jeu, 1)     >  0){ return HIGHCARD;}
    return 0;	
}

int compareHighCard(char * jeu1, char * jeu2){
    int index = 1;
    while(1==1){
        if(highCard(jeu1, index) > highCard(jeu2, index)){ return 1;}
        if(highCard(jeu1, index) < highCard(jeu2, index)){ return 2;}
        if(highCard(jeu1, index) == highCard(jeu2, index)){ ++index;}
    }
    return 0;
}

int compareTwoPair(char * jeu1, char * jeu2){
    int i;
    char * tab1 = getTwoPairValues(jeu1); 
    char * tab2 = getTwoPairValues(jeu2);
    triDescArray(tab1, 2); triDescArray(tab2, 2);
    for(i=0; i<=1; i++){
        if(translate(tab1[i]) > translate(tab2[i])){return 1;}
        if(translate(tab1[i]) < translate(tab2[i])){return 2;}
    }
    return 0;
}


int versus(char * jeu1, char * jeu2, int val1, int val2){
    int res1, res2;
    switch(val1){
        case STRAIGHT_FLUSH: return compareHighCard(jeu1, jeu2); 
        case FOUR_A_KIND: res1=translate(kind(jeu1,4)); res2=translate(kind(jeu2,4));
                          if(res1 > res2){return 1;}
                          if(res1 < res2){return 2;}
                          if(res1 == res2){return compareHighCard(jeu1, jeu2);}
        case FULL_HOUSE:  res1=translate(kind(jeu1,3)); res2=translate(kind(jeu2,3));
                          if(res1 > res2){return 1;}
                          if(res1 < res2){return 2;}
                          res1=translate(onePair(jeu1)); res2=translate(onePair(jeu2));
                          if(res1 > res2){return 1;}
                          if(res1 < res2){return 2;}
                          break;
        case FLUSH:       return compareHighCard(jeu1, jeu2);
        case STRAIGHT:    return compareHighCard(jeu1, jeu2);
        case THREE_KIND:  res1=translate(kind(jeu1,3)); res2=translate(kind(jeu2,3));
                          if(res1 > res2){return 1;}
                          if(res1 < res2){return 2;}
                          return compareHighCard(jeu1, jeu2);
        case TWO_PAIR:    if((res1=compareTwoPair(jeu1, jeu2)) > 0){return res1;}
                          if(res1==0){return compareHighCard(jeu1, jeu2);}
        case ONE_PAIR:    res1=translate(onePair(jeu1)); res2=translate(onePair(jeu2));
                          if(res1 > res2){return 1;}
                          if(res1 < res2){return 2;}
                          return compareHighCard(jeu1, jeu2);
        case HIGHCARD:    return compareHighCard(jeu1, jeu2);
        default:          return 0;
    }   
    return 0;
}

int main(){
	FILE * fprt = fopen("p054_poker.txt", "r");
	int input, compteur = 0, player1_cpt=0, position = 0, val1, val2;
	char * player1 = malloc(11*sizeof(char)); 
	char * player2 = malloc(11*sizeof(char));
	
	while((input=fgetc(fprt))!=EOF){
		if(input != 32 && input != 10){
			++compteur;
			if(compteur<=10){player1[position]=input; ++position;}
			else{
				if(compteur==11){position=0;}
				player2[position]=input; ++position;
			}
		}
		if(input==10){
			compteur = 0; position = 0;
			player1[10]='\0'; player2[10]='\0';
            val1=analyse(player1); val2=analyse(player2);
            if(val1>val2){
                player1_cpt++;
                printf("player1: %s, player2: %s, player1 gagne %d et player2 a %d\n", player1, player2, val1, val2);
            }
            if(val1==val2){
                if(versus(player1, player2, val1, val2)==1){
                    player1_cpt++;
                    printf("Confrontation : player1: %s, player2: %s, player1 gagne %d et player2 a %d\n", player1, player2, val1, val2);
                }
                else{printf("Confrontation : player1: %s, player2: %s, player2 gagne %d et player1 a %d\n", player1, player2, val2, val1);}
            }
            if(val1<val2){printf("player1: %s, player2: %s, player2 gagne %d et player1 a %d\n", player1, player2, val2, val1);}
			//if(onePair(player1) >= 1 && kind(player1, 3)>=1) {printf("le jeu %s a une pair %c  et un brelan de valeur %c\n", player1, onePair(player1), kind(player1,3));}
			//if(onePair(player2) >= 1 && kind(player2, 3)>=1) {printf("le jeu %s a une pair %c  et un brelan de valeur %c\n", player2, onePair(player2), kind(player2,3));}
		}
	}
    printf("========================> Pour le joueur 1 on comptabilise %d parties gagnées\n", player1_cpt);
}
