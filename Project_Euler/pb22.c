#include <stdio.h>

int main(){
	FILE * fp; int i = 0; int position = 1; int nameSum = 0; int tmp;
	int globValue = 0;
	fp = fopen("tmp_pb22.dat", "r");
	char buff[255];
	
	while ( fgets(buff, 255, fp) != NULL ){
		i = 0;
		nameSum = 0;
		printf("calcul pour le prénom %s", buff);
		printf("nameSum = ");
		while(buff[i] != '\n'){
			tmp = (buff[i] - 64);
			nameSum += tmp;
			printf(" + %d", tmp);
			i++;
		}
		tmp = position * nameSum;
		globValue += tmp;
		printf("\nval du calcul: %d\nposition: %d\nvaleur globale: %d\n", tmp, position, globValue);
		position++;
		printf("=============================================\n");
	}
	return 0;
}
