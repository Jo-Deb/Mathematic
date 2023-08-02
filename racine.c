#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*calculer les racines d'un nombre en entrée*/

int partieEntiere(double val, int power){
    double i = 1.0, p = power * 1.0;
    while(pow(i,p) <= val){ i+= 1.0; }
    i -= 1.0;
    return (int) i;
}

double nextDigit(double res, double input, int mthroot, int i /*place du digit à trouver*/){
    double deno = pow(10, i), digit = 0.0, tmp = 0.0;
    do{
        digit += 1.0;
        tmp = pow(res+(digit/deno), mthroot);
    } while(tmp <= input);
    digit = (digit - 1.0)/deno;
    return digit;
}

int main(int argc, char ** argv){
    double val_input = 0.0;
    int power = 0;
    if(argc == 3){
        if(sscanf(argv[1], "%lf", &val_input) != EOF && sscanf(argv[2], "%d", &power) != EOF){}
        else { printf("Mauvais arguments, échec \n"); return 1; }
    }
    double res = (double) partieEntiere(val_input, power), digit = 0.0;
    printf("la partie entière trouvée est : %d\n", (int)res);
    int dd=0; //représente le nombre de digit déjà calculé pour la partie décimale, car on va à
              //une précision de 4 chriffres après la virgule.
    do{
        digit = nextDigit(res, val_input, power, dd+1);
        ++dd;
        res += digit;
    } while(res < val_input && dd < 9);
    printf("la valeur approchée de la racine 1/%d ème de %.15f est %.15f\n", power, val_input, res);
    return 0;
}
