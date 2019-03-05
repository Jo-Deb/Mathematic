#!/bin/sh

tab[0]="0"
tab[1]="1"
tab[2]="2 1"

rempli_tab(){
chaine=$1
reste=$1
#On itère sur la chaine pour compléter le tableau
for elt in $chaine
do	reste=$(echo ${reste#$elt})
	[ -z "${tab[elt]}" ] && tab[$elt]="$elt $reste"
done
}


collatz_suite(){
origin=$1
res="$1"
genTerme=$1
stop=$((0))
#On s'arrete quand la genTerm vaut 1
[ $genTerme -eq 1 ] && return 0
#genTerme ne vaut pas un, on itère donc pour calculer toute la suite
while [ $stop -ne 1 ]
do	[ $genTerme -eq 1 ] && stop=$((1))
	if [ $((genTerme % 2)) -eq 0 ]
	then	genTerme=$((genTerme/2))
			if [ ! -z "${tab[genTerme]}" ] 
			then	res="$res ${tab[genTerme]}"
					stop=$((1))
			else 	res="$res $genTerme"
			fi
	else genTerme=$((3*genTerme+1))
			if [ ! -z "${tab[genTerme]}" ] 
			then	res="$res ${tab[genTerme]}"
					stop=$((1))
			else 	res="$res $genTerme"
			fi
	fi					
done
tab[$origin]="$res"
}

