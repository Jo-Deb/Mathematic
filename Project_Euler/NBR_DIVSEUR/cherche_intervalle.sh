#!/bin/sh

source fonctions.sh

triangulaire(){
	echo $(($1 * ($1 + 1) / 2))
}


n=$((998))
majorant=$((100000000000))
borneSup=$((20000))
borneMin=$((20000))

while [ $n -le $borneSup ]
do	echo "n=$n"
	nbrT=$(triangulaire $n)
	div=$(nbr_diviseur $nbrT)
	if	[ $div -ge 500 ]; then echo "div=$div et nbrT=$nbrT"; fi
	while [ $div -lt 500 ] 
	do	limit=$nbrT
		nbrT=$(triangulaire $nbrT)	
		if [ $nbrT -lt $majorant ] 
		then	div=$(nbr_diviseur $nbrT)
				if	[ $div -gt 500 -a $nbrT -gt 0 ] 
				then	echo "div=$div et nbrT=$nbrT et n'=$limit"
						majorant=$((nbrT))
						[ $limit -lt $borneSup ] && borneSup=$limit	
				fi
		else break
		fi
	done
n=$((n+1))
done
