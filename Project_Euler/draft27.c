#include <stdio.h>

int isPrime( int val){
	int limit = 0, i;
	if(val < 0){val = -1 * val;}
	while((limit * limit ) < val){++limit;}
	
	for( i = 2; i <= limit; i++){ if(val % i == 0){return 0;} }
	return 1;	
}




int main(){
	int n, a, b, max = 0, result, abs_b, neg_b, tmp, max_a, max_b;

	for(b=-999; b <= 1000; b++){
		if( isPrime(b) == 1){
			if( b < 0){ abs_b = b*-1; neg_b = b;}
			else{ abs_b = b; neg_b = -1 * b;}
			for(a=-999; a<1000; a+=2){
				for(n=0; n<abs_b; n++){
					tmp = n*n + n*a + b;
					if(isPrime(n*n + n*a + b) == 0){break;}
					printf("%d ", tmp);
					if(n > max){ 
						max = n; 
						result = a*b; 
						max_a=a; max_b=b;
						printf("\n n+%d*n^2+%d produit %d premier et a*b=%d\n et a=%d et b=%d", a, b, n, result, a, b);
					}
				}
				printf("\n");
			}
		}
	}
	printf("le max de nombres premiers produit est %d et a*b=%d, a=%d et b=%d\n", max, result, max_a, max_b);
	return result;
}
