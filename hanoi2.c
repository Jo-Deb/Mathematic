#include <stdio.h>
#include <stdlib.h>
#include "Project_Euler/liste.h"
#include "Project_Euler/pile.h"

pile * piquetA = NULL, *piquetB = NULL, *piquetC = NULL;

typedef enum { A, B, C } tige;
typedef struct {
    tige from;
    tige to;
    int val;
} move;

move * createMove(tige f, tige t, int dia){
    move * res = malloc(sizeof(move));
    res->from = f; res->to = t; res->val = dia;
    return res;
}

void addMove(tige t, move * m){
    switch(t) {
        case A: 
            piquetA = empilePile(piquetA, (void *) m);
            break;
        case B:
            piquetB = empilePile(piquetB, (void *) m);
            break;
        case C:
            piquetC = empilePile(piquetC, (void *) m);
            break;
    }
    return;
}

void inverseMove(move * m){
    tige tmp = m->from;
    m->from = m->to;
    m->to = tmp;
    return;
}

pile * inversePile(pile * p){
    pile ** m = map_pile(p);
    pile * res = NULL;
    int i;
    for(i=Taille_p-1; i>=0; --i){res = empilePile(res, m[i]->data);}
    return res;
}

int * make_pointer(int n){
    int * res = malloc(sizeof(int));
    * res = n;
    return res;
}

pile * build_movesd(int nbr_disc){
    int i;
    pile * all_moves = NULL, * wrk = NULL;
    piquetA = NULL;
    for(i=nbr_disc; i>=1; --i){ piquetA = empilePile(piquetA, make_pointer(i)); }
    for(i=1; i<=nbr_disc; ++i){
        wrk = all_moves;
        if(i==1) {
            wrk = empilePile(wrk, (void *) createMove(A, B, i));
            wrk = empilePile(wrk, (void *) createMove(B, C, i));
            all_moves = wrk;
        }
        else {
            /*On fait nouveau disque vers B + inverse(ancienne pile) + puis 
             * déplacement du nouveau disque vers C + ancienne pile */
            all_moves = empilePile(all_moves, (void*)createMove(A, B, i));
            all_moves = concatene_pile(all_moves, inversePile(wrk));
            all_moves = empilePile(all_moves, (void*)createMove(B, C, i));
            all_moves = concatene_pile(all_moves, wrk);
        }
        return all_moves;
    }
}

void afficheHanoiPile(pile * p){
    pile * tmp = p;
    move * m = (move *) tmp->data;
    while(tmp->back != NULL){
        switch(m->from){
            case A :
                if(m->to == B){printf("%d, A->B\n", m->val);}
                else{printf("%d, A->C\n", m->val);}
                break;
            case B :
                if(m->to == C){printf("%d, B->C\n", m->val);}
                else{printf("%d, B->A\n", m->val);}
                break;
            case C :
                if(m->to == B){printf("%d, C->B\n", m->val);}
                else{printf("afficheHanoiPile: Erreur\n");}
                break;
            default :
                printf("afficheHanoiPile: valeur inconnue\n");
                break;
        } 
        tmp = tmp->back;
    }
}


