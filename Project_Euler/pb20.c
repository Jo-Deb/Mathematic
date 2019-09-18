#include <stdio.h>
#include <stdlib.h>

void addition(int elt1[], int elt2[], int res[]){
	int tmp; int retenu = 0; int reste; int max;
	int i = 299;
	
	while(elt1[i] != -1 || elt2[i] != -1){
		
		if(elt1[i] != -1 && elt2[i] != -1){tmp = retenu + elt1[i] + elt2[i]; }

		if(elt1[i] != -1 && elt2[i] == -1){tmp = retenu + elt1[i];}

		if(elt1[i] == -1 && elt2[i] != -1){tmp = retenu + elt2[i];}

		if(elt1[i] == -1 && elt2[i] == -1 && retenu != 0){tmp = retenu;}

		if(tmp > 9){ retenu = tmp / 10; reste = tmp % 10; res[i] = reste;}
		else{retenu = 0; res[i] = tmp;}
		--i;
	}
}

void multiplication(int tab[], int quotien){
	int ligne1[300]; int ligne2[300]; int ligne3[300]; int dizaine, unite;
	int tmpD; int tmpU; int retenueD=0; int retenueU=0; int i = 299; int retenue = 0; int tmp;

	for(int j = 0; j < 300; j++){ligne1[j] = ligne2[j] = ligne3[j] = -1;}
	if(quotien >= 10){ dizaine = quotien / 10; unite = quotien % 10; ligne2[i] = 0;}
	else{ unite = quotien;}

	while(tab[i] != -1){
		tmpU = tab[i] * unite + retenueU;
		retenueU = tmpU / 10; tmpU = tmpU % 10;
		ligne1[i] = tmpU;
		if(tab[i-1] == -1 && retenueU > 0){ligne1[i-1] = retenueU;}

		if(quotien > 10){
			tmpD = tab[i] * dizaine + retenueD;
			retenueD = tmpD / 10; tmpD = tmpD % 10;
			ligne2[i-1] = tmpD;
			if(tab[i-1] == -1 && retenueD > 0){ligne2[i-2] = retenueD;}			
		}
		--i;
	} //addition des deux lignes

	//printf("\nVoici la ligne 1: ");
	//for(int j = 0; j < 300; j++){if(ligne1[j] != -1 ){printf("%d", ligne1[j]);}}
	//printf("\nVoici la ligne2: ");
	//for(int j = 0; j < 300; j++){if(ligne2[j] != -1 ){printf("%d", ligne2[j]);}}
	//printf("\n");

	i = 299; retenue = 0;
	while( quotien >= 10 && ligne2[i] != -1){
		if(ligne1[i] != -1){tmp = ligne1[i] + ligne2[i] + retenue;}
		else{tmp = ligne2[i] + retenue;}
		retenue = tmp / 10; tmp = tmp % 10;
		ligne3[i] = tmp;
		if(ligne2[i-1] == -1 && retenue > 0){ ligne3[i-1] = retenue; }
		--i;
	}
	if( quotien >= 10){
		i = 299;
		while(ligne3[i] != -1 ){ tab[i] = ligne3[i]; --i;}
	} 
	else {
		i = 299;
		while(ligne1[i] != -1 ){ tab[i] = ligne1[i]; --i;}
	}
}

int main(){
	int ptr[300]; int ptr2[300]; int res[300];
	for(int i = 0; i < 300; i++){ptr[i] = -1;}
	ptr[297]=1; ptr[298]=0; ptr[299]=0;

	for(int i = 99; i > 0; i--){
		for(int j = 0; j < 300; j++){if(ptr[j] != -1 ){printf("%d", ptr[j]);}}
		printf(" * %d = ", i);
		multiplication(ptr, i);
		for(int j = 0; j < 300; j++){if(ptr[j] != -1 ){printf("%d", ptr[j]);}}
		printf("\n");
	}
	int somme = 0;
	for( int j = 0; j < 300; j++){ 
		if( ptr[j] != -1) somme += ptr[j];
	}
	printf("la somme des nombres qui compose factorielle(100) est : %d\n", somme);
	return 0;
}