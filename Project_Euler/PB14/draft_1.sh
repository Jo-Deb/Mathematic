#!/bin/sh
#idée: retourner la suite afin que la fin soit en premier, cela permettra de sortir
#de la fonction rempli_tab() sans avoir à parcourir la suite dans sa totalité
#Mettre la longueur de la suite dans case. Bien faire attention que lors de la
#concaténation de suite on garde bien l'ordre inverse
# Tableau tab: la liste des numéros pour lesquels on souhaite savoir si ils ont 
# 				ou non la grande suite.
# Tableau array: la liste des éléments pour lesquels il ne faut pas calculer la 
#				 longueur de la suite, si la valeur de array est à 0


tab[0]="0"
tab[1]="1"
tab[2]="2"
array[0]="1"
positionTab[0]=0

initiateVal(){
for ((i=1; i < 1000000; i=i+1)); do array[$i]="1"; done
}

rempli_tab(){
chaine=$1
reste=$1
#On itère sur la chaine pour compléter le tableau
for elt in $chaine
do	reste=$(echo ${reste#$elt})
	[ -z "${tab[elt]}" ] && tab[$elt]="$elt $reste"
	[ $elt -lt 1000000 ] && array[$elt]="0"
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
[ $genTerme -eq 1 ] && stop=$((1))
#genTerme ne vaut pas un, on itère donc pour calculer toute la suite
while [ $stop -ne 1 ]
do	[ $genTerme -eq 1 ] && stop=$((1))
	[ $((genTerme % 2)) -eq 0 ] && genTerme=$((genTerme/2)) || genTerme=$((3*genTerme+1))
	[ $genTerme -lt 1000000 -a $genTerme -lt $origin ] && array[$genTerme]=0
	nbrNewElt=$((nbrNewElt+1))
	if [ ! -z "${tab[$genTerme]}" ] #On vérifie si un terme a déjà été calculé pour cette suite
	then nbrNewElt=$((nbrNewElt + ${tab[$genTerme]})) 
		 stop=$((1))
	else [ -z "${positionTab[$genTerme]}" ] && positionTab[$genTerme]=$((nbrNewElt))
	     [ ${positionTab[$genTerme]} -gt $nbrNewElt ] && stop=$((1)) || positionTab[$genTerme]=$((nbrNewElt))
	fi
done
echo "$nbrNewElt"
}

n=$((999999))
max_length=$((2))
maxElt=$((2))
initiateVal
while [ $n -gt 13 ]
do	if [ ${array[n]}  -eq 1 ]
	then tmp=$(collatz_suite "$n")
		 [ $tmp -gt $max_length ] && max_length=$tmp &&  maxElt=$n
	fi
	[ $((n % 50)) -eq 0 ] && echo "calcul de $n en cours; actuellement la plus longue suite calculée est $maxElt et mesure $max_length"
	n=$((n-1))
done
	



