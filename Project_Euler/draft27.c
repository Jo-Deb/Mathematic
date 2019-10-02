#include <stdio.h>

int isPrime( int val){
	int limit = 0, i;
	if(val < 0){val = -1 * val;}
	while((limit * limit ) < val){++limit;}
	
	for( i = 2; i <= limit; i++){ if(val % i == 0){return 0;} }
	return 1;	
}




int main(){
	int n, a, b, max = 0, result, abs_b, neg_b;

	for(b=-999; b <= 1000; b+=2){
		if( isPrime(b) == 1){
			if( b < 0){ abs_b = b*-1; neg_b = b;}
			else{ abs_b = b; neg_b = -1 * b;}
			for(a=neg_b+2; a<abs_b; a+=2){
				for(n=0; n<abs_b; n++){
					if(isPrime(n + n*n*a + b) == 0){break;}
					if(n > max){ 
						max = n; 
						result = a*b; 
						printf("n+%d*n^2+%d produit %d premier et a*b=%d\n", a, b, n, result);
					}
				}
			}
		}
	}
	printf("le max de nombres premiers produit est %d et a*b=%d\n", max, result);
	return result;
}
