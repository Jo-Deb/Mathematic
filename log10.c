#include<stdio.h>
#include<math.h>

/*Une implémentation pour calculer log10*/

double algoLog10(int n, int precision){
    double curval = n * 1.0;
    int exposant_entier = 0, pr = 0, k = 0;

    while(fabs(curval) < 1 || fabs(curval) >= 10){
        if(fabs(curval) < 1){
            --exposant_entier;
            curval = curval * 10.0;
        }else{
            if(fabs(curval) > 10){
                ++exposant_entier;
                curval = curval/10.0;
            }
        }
    }

    double res = exposant_entier * 1.0;
    while(pr < precision){
        curval *= curval;
        printf("curval%d = %.10f et res = %.10f \n", k, curval, res);
        if(fabs(curval) >= 10.0){
            curval /= 10.0;
            ++k; ++pr;
            res += (1.0 / pow(2, k));
        } else {++k;}
    }
    printf("log(%d) = %.10f\n", n, res);
    return res;
}



int main(int argc, char ** argv){
    int log_val_to_compute, precision;

    if(argc == 3){
        if(sscanf(argv[1], "%d", &log_val_to_compute)!=EOF && sscanf(argv[2], "%d", &precision)!=EOF){}
        else{ printf("Mauvais arguments, échec\n"); return 1; }
    }
    algoLog10(log_val_to_compute, precision);
    return 0;
}
