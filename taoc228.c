#include "bibilog.h"

#define LOG2 0.30103

/*la valeur d'entrée exp est une valeur double compris entre 0 et 1
 * et nous prenons la base 10, ainsi 1 < 10^exp < 10 */

double computeRoot(double arg_in){
    double borne_inf = 0.9, borne_sup = 9.0, dicho = 5, res = 0;
    while(borne_sup - borne_inf > 0.001 || res == arg_in){
        dicho = (borne_inf + borne_sup)/2;
        if(calculLog10(approximationBinaire(dicho)) < arg_in){borne_inf = dicho;}
        else{
            if(calculLog10(approximationBinaire(dicho)) > arg_in){borne_sup = dicho;}
            else {res = dicho;}
        }
    }

}


double powerBetween0and1(double base, double exp){
    double borne_inf = 1.0, borne_sup = base, dicho, tmp, wrk;
    if( exp >= 1.0 ){ printf("la valeur de l'exposant est trop grande\nSortie du programme\n"); }
    int k = 0;
    
    while( borne_sup - borne_inf > 0.001 ){
        dicho = (borne_sup + borne_inf)/2.0;
        tmp = dicho; k = 0;
        while(tmp > 2) {
				tmp = mutukwediBase10(decaler(representationTouteValeur(tmp), 1)); 
				++k;
		  }
        if(tmp < 2 && tmp > 1){
				wrk = calculLog10(tmp) + k*LOG2;
				if(wrk > exp){borne_sup = dicho;}
				else {
					if(wrk < exp){ borne_inf = dicho; }
					else{ if (wrk = exp){return dicho;} }
    			}
		   }
	  }
	  return borne_inf;
}
