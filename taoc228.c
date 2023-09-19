#include "bibilog.h"
#include <math.h>

#define LOG2 0.30103

/*la valeur d'entrée exp est une valeur double compris entre 0 et 1
 * et nous prenons la base 10, ainsi 1 < 10^exp < 10 */
double powerBetween0and1(double base, double exp){
    double borne_inf = 1.0, borne_sup = base, dicho, tmp, wrk;
	 char * mutukwedi;
    if( exp >= 1.0 ){ printf("la valeur de l'exposant est trop grande\nSortie du programme\n"); }
    int k = 0;
    
    while( borne_sup - borne_inf > 0.001 ){
        dicho = (borne_sup + borne_inf)/2.0;
        tmp = dicho; k = 0;
        while(tmp > 2) {
				mutukwedi = representationTouteValeur(tmp);
				decaler(mutukwedi, 1); ++k;
				tmp = mutukwediBase10(mutukwedi); 
		  }
        if(tmp < 2 && tmp > 1){
				wrk = calculLog10(approximationBinaire(tmp)) + k*LOG2;
				if(wrk > exp){borne_sup = dicho;}
				else {
					if(wrk < exp){ borne_inf = dicho; }
					else{ if (wrk == exp){return dicho;} }
    			}
		   }
	  }
	  return borne_inf;
}

//b = 10
double b_ToPower_x(double x){
	double epsilon = 0.00001, X = 1 - epsilon - x, Y = 10.0, tmp = 0, vtmp = 0;
	int k = 1; char * binaryValue = NULL;
	
	while(X != 0 || k == 19){
		tmp = pow(2, k)/(pow(2, k) - 1);
		while(X < (vtmp = calculLog10(approximationBinaire(tmp))) ){++k;}
		X -= vtmp;
		binaryValue = representationTouteValeur(Y);
		decaler(binaryValue, k);
		Y -= mutukwediBase10(binaryValue);
		printf("X = %lf, Y = %lf, et k = %d\n", X, Y, k);
	} 
	return Y;
}

int main(int argc, char ** argv){
	double base, exp;
	if(argc == 3){
		if(sscanf(argv[1], "%lf", &base) != EOF && sscanf(argv[2], "%lf", &exp) != EOF ) {}
		else { printf("Mauvais argument, il faut donner une base et un exposant < 1d\n"); }
	}
	if(exp >= 1.0){ printf("l'exposant doit être inférieure à 1; arrêt du programme\n"); return 0; }

	printf("%lf à la puissance %lf est égale à : %lf et en approximation on trouvre %lf\n",\
			base, exp, pow(base, exp), b_ToPower_x(exp) );
	
	return 0;
}

/*
int main(int argc, char ** argv){
	double base, exp;
	if(argc == 3){
		if(sscanf(argv[1], "%lf", &base) != EOF && sscanf(argv[2], "%lf", &exp) != EOF ) {}
		else { printf("Mauvais argument, il faut donner une base et un exposant < 1d\n"); }
	}
	if(exp >= 1.0){ printf("l'exposant doit être inférieure à 1; arrêt du programme\n"); return 0; }

	printf("%lf à la puissance %lf est égale à : %lf et en approximation on trouvre %lf\n",\
			base, exp, pow(base, exp), powerBetween0and1(base, exp) );
	
	return 0;
}
*/
