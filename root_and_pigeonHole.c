#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int estCarre(int d){
	if(d == 1){return 0;}
	int i, tmp = 0;
	for(i=2; tmp < d; ++i){
		tmp = i * i;
		if(tmp == d){return 0;}
	}
	return 1;
}

int main(){
	int i, j;
	double root, decimal, interval, tmp, i1=1.0/5.0, i2=2.0/5.0, i3=3.0/5.0, i4=4.0/5.0; //[0, i1[, [i1, i2[ ; [i2, i3[ ; [i3; i4[ ; [i4, 1[ 

	for(i = 2; i < 100; ++i){
		while(estCarre(i) == 0){++i;}
		root = sqrt(i);
		printf("############################################Racine(%d)###############################################\n", i);
		printf("Les intervalles sont : [0, %4lf[ [%4lf, %4lf[ [%4lf, %4lf[ [%4lf, %4lf[ [%4lf, %d[\n", i1, i1, i2, i2, i3, i3, i4, i4, 1);
		for(j=1; j<=5; ++j){
			tmp = j*root;
			decimal = modf(tmp, &interval);
			if(decimal < i1){printf("%lf a comme partie décimal %lf est dans l'intervalle i1\n", tmp, decimal);}	
			if(decimal >= i1 && decimal < i2){printf("%lf a comme partie décimal %lf est dans l'intervalle i2\n", tmp, decimal);}	
			if(decimal >= i2 && decimal < i3){printf("%lf a comme partie décimal %lf est dans l'intervalle i3\n", tmp, decimal);}	
			if(decimal >= i3 && decimal < i4){printf("%lf a comme partie décimal %lf est dans l'intervalle i4\n", tmp, decimal);}	
			if(decimal >= i4 && decimal < 1.0){printf("%lf a comme partie décimal %lf est dans l'intervalle i5\n", tmp, decimal);}	
		}
		printf("#######################################################################################################\n");
	}
}
