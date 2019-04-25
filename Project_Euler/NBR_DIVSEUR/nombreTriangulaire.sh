#!/bin/sh

source fonctions.sh

n=7896
n_1=7897	
div_n=32
div_n1=12
nbr_div_n_n1=$((div_n*div_n1))
nbrTri=$((n*n_1))

if [ ! -f resultTriangulaire.txt  ]
then	echo "1:1" >> resultTriangulaire.txt
		echo "2:1" >> resultTriangulaire.txt
fi


while [ $nbr_div_n_n1 -lt 500 ]
do infoN=$(grep "^$n:" resultTriangulaire.txt)
	if [ -z "$infoN" ]
	then	div_n=$(nbr_diviseur "$n")
		 	echo "$n:$div_n" >> resultTriangulaire.txt
	else div_n=$(echo "$infoN" | cut -d ":" -f2)
	fi

	infoN1=$(grep "^$n_1:" resultTriangulaire.txt)
	if [ -z "$infoN1" ]
	then 	div_n1=$(nbr_diviseur "$n_1")
		  	echo "$n_1:$div_n1" >> resultTriangulaire.txt
	else 	div_n1=$(echo "$infoN1" | cut -d ":" -f2)
	fi

	nbrTri=$((n * n_1))
	infoT=$(grep "^$nbrTri:" resultTriangulaire.txt)
	if [ -z "$nbrTri" ]
	then 	nbr_div_n_n1=$((div_n * div_n1))
			echo "$nbrTri:$nbr_div_n_n1" >> resultTriangulaire.txt
	fi

	[ $div_n -gt 250 ] && echo "peut-etre une solution est : n:$n car div_n=$div_n"
	[ $div_n1 -gt 250 ] && echo "peut-etre une solution est : n_1:$n_1 car div_n1=$div_n1"
	[ $nbr_div_n_n1 -gt 500 ] && echo "peut-etre une solution est : nbrTri:$nbrTri car nbr_div_n_n1=$nbr_div_n_n1"

while [ $((n*n_1)) -ge 62370000  ]; do n=$((n_1)); n_1=$((n_1 + 1)); done

	n=$((n_1))
	n_1=$((n_1 + 1))
	div_n=$((div_n1))
	
done
