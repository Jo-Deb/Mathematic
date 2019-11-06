#include <stdio.h>

int power(int val, int pow){
	if( pow == 1) {return val;}
	else {return val * power(val, --pow);}
}

int verifsum(int value){
	int somme = 0, tmp, i=0;
	char buffer[20], tmpchar;

	if(sprintf(buffer, "%d", value) < 1){
		printf("Un problème est survenu avec le nombre %d\n", value);
		return 0;
	}

	while(buffer[i] != '\0'){
		tmpchar = buffer[i];
		if(sscanf(&tmpchar, "%d", &tmp) > 0){
			//printf("calcul de la puissance de %d à puissance 5\n", tmp);
			somme += power(tmp, 5);
			if(somme > value){return 0;}
			if(somme == value && buffer[i+1] == '\0'){ return value;}
		}
		i++;
	}
	return 0;
}

int decompose(int value){
	int somme = 0, tmp, i=0;
	char buffer[20], tmpchar;

	if(sprintf(buffer, "%d", value) < 1){
		printf("Un problème est survenu avec le nombre %d\n", value);
		return 0;
	}
	printf("%d = ", value);
	while(buffer[i] != '\0'){
		tmpchar = buffer[i];
		if(sscanf(&tmpchar, "%d", &tmp) > 0){
			if(buffer[i+1]!='\0'){printf("%d + ", power(tmp, 5));}
			else{ printf("%d ", power(tmp, 5));}
		}
		i++;
	}
	printf("\n");
	return 0;
}

int main(){
	int somme = 0;

	for(int i = 2; i < 600000; i++){
		if(verifsum(i) == i){ 
			printf("%d respecte la condition\n", i);
			decompose(i);
			somme += i;
		}
	}
	printf("la somme totale est %d\n", somme);
}