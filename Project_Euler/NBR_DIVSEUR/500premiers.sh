#!/bin/sh

source fonctions.sh

n=$((500))
div_n=$(nbr_diviseur $n) 

while [ $n -lt 15625 ]
do	suiv=$(nbr_diviseur $((n+1))) 
	if [ $div_n -ge 10 -o  $suiv -ge 10 ]  
		then 	val=$((div_n * suiv)) 
				if [ $val -ge 500 ]; then echo "Voici une réponse : n=$n div_n=$div_n suiv=$suiv div_n*suiv=$val" | tee -a result2.txt; fi 
	fi
	div_n=$suiv
	n=$((n+1))
done

