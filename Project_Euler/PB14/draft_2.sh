#!/bin/bash 
#Pour ce draft2 on fait un test en mode bash
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

alignTab(){
	start="$1" && origin="$1" && nbrElt="${tab[origin]}" && start=$((start * 2))
	while [ $start -lt 1000000 ]
	do	nbrElt=$((nbrElt + 1))
		[ -z "${tab[start]}" ] && tab[$start]=$((nbrElt)) 
		start=$((start * 2))
	done
}

deduitTaille(){
taille="$1"
suite="$2"
for elt in $suite; do taille=$((taille - 1)) && tab[$elt]=$taille; done
}

tabPuissanceDedeux(){
	local depart=2
	local taille=2
	while [ $depart -lt 1000000 ]
	do	tab[$depart]=$((taille))
		depart=$((depart * 2))
		taille=$((taille+1))
	done
}

nbrPremier_collatzSuit(){
	local source="/Users/SoPla/Personnel/Informatique/Perl/base_nbr_premiers.dat"
	local line="1"
	while [ $line -lt 1000000 ]
	do	tab[$line]=$(collatz_suite "$line")
		echo "calcul du premier $line en cours"
		read line
	done < $source
}

collatz_suite(){
debut=$1 && res="$1" && genTerme=$1 && stop=$((0)) && nbrNewElt=$((1)) && local pair=$((0)) && local impair=$((0))
#genTerme ne vaut pas un, on itère donc pour calculer toute la suite
while [ $stop -ne 1 ] 
do [ $genTerme -eq 1 ] && stop=$((1))
   if [ $((genTerme % 2)) -eq 0 ] 
	then genTerme=$((genTerme/2)) && pair=$((1)) 
	else genTerme=$(( (3*genTerme+1)/2 )) && impair=$((1))
	fi
   #if [ ! -z "${tab[$genTerme]}" ] #On vérifie si un terme a déjà été calculé pour cette suite
	if [ $genTerme -lt $debut ]
   then [ $pair -eq 1 ] &&  nbrNewElt=$((nbrNewElt + ${tab[$genTerme]})) && stop=$((1))
	[ $impair -eq 1 ] &&  nbrNewElt=$((nbrNewElt + 1 + ${tab[$genTerme]})) && stop=$((1))
   else [ $pair -eq 1 ] && nbrNewElt=$((nbrNewElt+1)) 
  	[ $impair -eq 1 ] && nbrNewElt=$((nbrNewElt+2)) 
   fi
	pair=$((0)) && impair=$((0))  
done
echo "$nbrNewElt"
}


#Main
n=$((3))
maxElt=$((0))
tailleMax=$((0))
echo "$(date "+%H:%M:%S - ") debut du traitement"
while [ $n -lt 1000000 ]
do	if	[ -z "${tab[n]}" ]; then	tab[$n]=$(collatz_suite $n); fi
	if [ ! -z ${tab[n]} ] && [ ${tab[n]} -gt $tailleMax ]; then tailleMax=$((${tab[n]})) && maxElt=$((n)); fi		 
	if [ $((n % 10000)) -eq 0 ]; then echo "$(date "+%H:%M:%S - ")la taille max des suites est $tailleMax pour le nombre $maxElt"; fi
	n=$((n+1)) #incrémentation disponible en bash
done
