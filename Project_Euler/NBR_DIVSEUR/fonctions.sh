#!/bin/bash

nbr_diviseur(){
	produit=$((1))
	decomposition=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_nombre_premier.pl $1 | cut -d "=" -f2|tr '*' ' ')
	for term in $decomposition
	do	multiple=$(echo $term | cut -d "." -f1)
		pow=$(echo $term | sed -E 's/[0-9]+\.pow\(([0-9]+)\)/\1/g')
		#[ $multiple -eq 2 ] && produit=$((produit * pow)) || produit=$((produit * (pow + 1)))	
		produit=$((produit * (pow + 1)))	
  	done
	echo "$produit"
}

crible_eratosthene(){
argu=$1
racine=$(echo "sqrt($argu)" | bc -l | cut -d "." -f1)
n=$((2))
pasPremier=$((0))

while [ $n -le $racine -a $pasPremier -eq 0 ]
do	[ $((argu % n)) -eq 0 ] && pasPremier=$((1))
	n=$((n+1))
done

#Si le résulte est 0 alors nous avons un nombre premier
#autrement non
[ $pasPremier -eq 0 ] && echo "0" || echo "1"
}

primeTab=(2 3 5)

tabOfPrime(){
decompte=$((0))
incr=$((2))
echo "debut du chargement du tableau, veuillez patienter"
while [ $decompte -le 5000 ] # 5000 c'est bien trop pour du shell, le perl à l'air plus performant
do	if [ $( crible_eratosthene $incr ) -eq 0 ]
	then	tab[$decompte]=$((incr)) && decompte=$((decompte + 1))
	fi
	incr=$((incr + 1))
done
echo "fin du chargement, tableau des 5001 premiers entiers instancié"
}


puissanceMaxDuPremier(){
nbr=$1
nbr_premier=$2
max=$2
depasse=$((0))
puissance=$((1))
while [ $depasse -eq 0 ]
do	tmp=$((max * nbr_premier))
	if [ $((nbr % tmp)) -eq 0 ] 
	then	max=$((max * nbr_premier)) 
		puissance=$((puissance + 1))
	else	depasse=$((1))
	fi
done
echo "$max:$puissance"
}

hoMaDiv(){
val=$1

racine=$(echo "sqrt($val)" | bc -l | cut -d "." -f1)
arret=$((0))

while [ $arret -eq 0 -a $val -gt 1 ]
do	read line
	[ $line -gt $racine ] && arret=$((1))
	if [ $((val % line)) -eq 0 ]
	then	h_tmpLine=$(puissanceMaxDuPremier $val $line)	
		h_diviseur=$(echo "$h_tmpLine" | cut -d ":" -f1)
		h_nbr_div=$(echo "$h_tmpLine" | cut -d ":" -f2)
		h_suite=$((val/h_diviseur)) && arret=$((1))
	fi
done < base_nbr_premiers.dat

[ $val -lt 0 -o $val -eq 1 ] && echo "1"
 # Si cette condition est vrai alors val est un nombre premier
[ $arret -eq 1 -a -z "$h_tmpLine" -a $val -gt 1 ] && echo "2"

if [ ! -z "$h_suite" ]
then	if [ $h_suite -gt 1 ] 
	then 	h_tmp=$(hoMaDiv $h_suite )
		echo $((h_nbr_div * h_tmp))
	else [ $h_suite -eq 1 ] && echo "1"
	fi
fi
}


proposition_decomposition(){
val=$1
diviseurPremier=$((0))
while [ read line -a  $diviseurPremier -eq 0 ]
do	if [ $((val % line)) -eq 0 ]
	then	diviseurPremier=$((line))
	fi
done < base_nbr_premiers.dat
diviseurPremier=$(PuissanceMaxDuPremier $val $diviseurPremier)
}
