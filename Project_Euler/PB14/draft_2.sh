#!/bin/sh
#énoncé: Prendre le nombre k, voir si sa chaine est calculée si non la calculer
#et calculer tous ses multiples tels qu'ils s'écrivent k.2^n avec n un entier naturel
#Si on tombe sur un élément qui a déjà été calculé on somme la taille. 
#Pour l'instant on ne met pas le système de comparaison des places pour les éléments des suites
array[0]="1"
tab[1]="1"
tab[2]="2"

initiate(){
	for ((i=1; i < 1000000; i=i+1)); do array[$i]="1"; done
}

#Main
n=$((3))
while [ $n -lt 1000000 ]
do	[ ${array[n]} -eq 0 ] && [ -z "${tab[n]}" ] && tmp=$(collatz_suite $n) && 
