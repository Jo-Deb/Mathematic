#include <stdio.h>
#include <stdlib.h>
#include "Project_Euler/liste.h"
#include "Project_Euler/pile.h"



/*Il s'agit d'implémenter une version des tours de Hanoi où le disque 
 * qu'on souhaite bouger doit forcément transiter par le piquet du milieu
 * */

liste * piquetA = NULL, * piquetB = NULL, * piquetC = NULL;

void deplacerA_vers_B(void){
    if(piquetA->value > piquetB->value){
        printf("deplacerA_vers_B: déplacement impossible %d > %d\n"\
                , piquetA->value, piquetB->value); 
        return;
    }
    piquetB = ajoutEnTete(piquetB, piquetA->value);
    piquetA = supprElt(piquetA, piquetA->value);
    return;
}

void deplacerB_vers_C(void){
    if(piquetB->value > piquetC->value){
        printf("deplacerB_vers_C: déplacement impossible %d > %d\n"\
                , piquetB->value, piquetC->value); 
        return;
    }
    piquetC = ajoutEnTete(piquetC, piquetB->value);
    piquetB = supprElt(piquetB, piquetB->value);
    return;
}

void deplacerC_vers_B(void){
    if(piquetC->value > piquetB->value){
        printf("deplacerC_vers_B: déplacement impossible %d > %d\n"\
                , piquetC->value, piquetB->value); 
        return;
    }
    piquetB = ajoutEnTete(piquetB, piquetC->value);
    piquetC = supprElt(piquetC, piquetC->value);
    return;
}

void deplacerB_vers_A(void){
    if(piquetB->value > piquetA->value){
        printf("deplacerB_vers_A: déplacement impossible %d > %d\n"\
                , piquetB->value, piquetA->value); 
        return;
    }
    piquetA = ajoutEnTete(piquetA, piquetB->value);
    piquetB = supprElt(piquetB, piquetB->value);
    return;
}

