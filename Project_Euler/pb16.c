#include <stdio.h>

void cal(){
	int ope[500];
	int tmp=0;
	int retenue=0;
	int limite=0;

	for (int i=0; i<=499; i++){ ope[i]=0;}
	ope[499]=1;
	//on multilplie par 2 en faisant lui même par lui même
	retenue=0; limite = 0; tmp = 0;
	for (int n=1; n<=1000; n++){	
		for (int j=499; j>=499-limite-1; j--){
			if(retenue == 0) {tmp = 2*ope[j]; 
				if (tmp > 0 && j <= 500 - limite ) {limite++;}
				if (tmp >= 10) {retenue = 1; ope[j] = tmp - 10; }
				else { retenue = 0; ope[j] = tmp; }
			}else {
				tmp = 2*ope[j] + 1;
				retenue = 0;
				if (tmp > 0 && j <= 500 - limite ) {limite++;}
				if (tmp >= 10) {retenue = 1; ope[j] = tmp - 10; }
				else { retenue = 0; ope[j] = tmp; }
			}	
		}
		//printf(" 2 à la puissance %d = ", n);
		//for (int k =0; k <500; k++){printf("%d", ope[k]);}
		//printf("\n\n");
	}
	printf("2 à la puissance 1000 donne:");
	for (int k =0; k <500; k++){printf("%d", ope[k]);}
	for (int k =0; k <500; k++){ope[0] = ope[0]+ope[k];}
	printf("\n\n la somme des chiffres de 2^1000 est %d \n", ope[0]);
	
}

int main (){
cal();
}
