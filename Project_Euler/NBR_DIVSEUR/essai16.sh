#!/bin/sh

source fonctions.sh

sort base_div.txt | uniq > tmp.txt && mv tmp.txt base_div.txt

combienPourArriverA500(){
val=$1
decomposition=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_nombre_premier.pl $val | cut -d "=" -f2 | tr -d " " | tr "*" " " )
mesPuissances=$(echo "$decomposition" | sed -E 's/[0-9]+\.pow\(([0-9]+)\)/\1/g')
accommodant=""
tmpString="$mesPuissances"
div=$((1))

while [ $div -le 500 ]
do	for value in "$tmpString"
	do div=$((div * (value * 2 + 1) ))
		tmpVal=$((2*value))
		accommodant="$accommodant $tmpVal"
	done
	tmpString="$accommodant"
	val=$((val*val))
done
echo "$div:$val"
}

[ -f resultats.txt ] && rm resultats.txt

n=$((2))
limit=$((1000000000))
max_compte=$((1000))
max_div=$((2))

while [ $n -lt $limit ]

do div=$(grep "^$n:" base_div.txt)
	if [ -z "$div" ] 
	then 	div=$(nbr_diviseur $n)
 			echo	"$n:$div" >> base_div.txt 
	else 	div=$(echo "$div" | cut -d ":" -f2)
	fi
	if [ $div -gt $max_div ]
	then	tmpCompte=$(combienPourArriverA500 $n)
			compteDiv=$(echo $tmpCompte | cut -d":" -f1) 
			compteVal=$(echo $tmpCompte | cut -d":" -f2) 
		  	if [ $compteVal -le $max_compte ]
			then 	tmpBigVal=$(echo "$n ^ $tmpCompte" | bc -l)
					if [ $tmpBigVal -gt 0 -a $tmpBigVal -lt $limit ]
					then	limit=$((tmpBigVal))
							echo "une solution: $tmpBigVal avec $tmpCompte diviseurs et limite vaut $limit"
					fi
			fi
			max_div=$((div))
	fi
	n=$((n+1))
done
