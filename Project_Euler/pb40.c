#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "fonctionsPratiques.h"

int main(){
	int cpt = 0, index = 1, tmp;
	liste * l = NULL;

	while(cpt <= 1000020){
		tmp = calculTailleEntier(index);
		cpt += tmp;
		if(cpt >= 10 && cpt<=14) printf("cpt = %d et tmp=%d\n", cpt, index);
		if(cpt >= 100 && cpt<=104) printf("cpt = %d et tmp=%d\n", cpt, index);
		if(cpt >= 1000 && cpt<=1006) printf("cpt = %d et tmp=%d\n", cpt, index);
		if(cpt >= 10000 && cpt<=10008) printf("cpt = %d et tmp=%d\n", cpt, index);
		if(cpt >= 100000 && cpt<=100010) printf("cpt = %d et tmp=%d\n", cpt, index);
		if(cpt >= 1000000 && cpt<=1000012) printf("cpt = %d et tmp=%d\n", cpt, index);
		++index;
	}
	return EXIT_SUCCESS;
}
