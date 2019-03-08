#!/bin/sh
#idée: retourner la suite afin que la fin soit en premier, cela permettra de sortir
#de la fonction rempli_tab() sans avoir à parcourir la suite dans sa totalité
#Mettre la longueur de la suite dans case. Bien faire attention que lors de la
#concaténation de suite on garde bien l'ordre inverse

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

length_sequence(){
argument=$1
echo "$argument" | wc -w | tr -d " " 
}

collatz_suite(){
origin=$1
res="$1"
genTerme=$1
stop=$((0))
nbrNewElt=$((1))
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
					nbrNewElt=$((nbrNewElt+1))
			fi
	else genTerme=$((3*genTerme+1))
			if [ ! -z "${tab[genTerme]}" ] 
			then	res="$res ${tab[genTerme]}"
					stop=$((1))
			else 	res="$res $genTerme"
					nbrNewElt=$((nbrNewElt+1))
			fi
	fi					
done
tab[$origin]="$res"
[ $nbrNewElt -gt 1 ] && rempli_tab "$res"
}

n=$((3))
max_length=$((2))
maxElt=$((2))
while [ $n -lt 1000000 ]
do	if [ -z "${tab[n]}" ]
	then 	collatz_suite "$n"
			tmp=$(length_sequence "${tab[n]}")
			[ $tmp -gt $max_length ] && max_length=$tmp; maxElt=$n
	fi
	[ $((n % 50)) -eq 0 ] && echo "calcul de $n en cours; actuellement la plus longue suite calculée est $maxElt et mesure $max_length"
	n=$((n+1))
done
	



