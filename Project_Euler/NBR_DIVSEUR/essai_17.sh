#!/bin/sh

[ -f debbug.txt ] && rm debbug.txt
#source fonctions.sh
source fonctions_2.sh 

nombreDiviseur=$((1))
incr=$((2))

while [ $nombreDiviseur -le 500 ]
do	val=$((incr * (incr + 1)/2))
	suite=$((val))
	chaine=""

	while [ $suite -gt 1 ]
	do	diviseur=$(trouveDiviseur $suite)
		if [ $diviseur -eq $suite ] 
		then 	chaine="$chaine 2 "
				suite=$((1))
		else	ligneMax=$(maxPuissance $suite $diviseur)
				divMax=$(echo "$ligneMax" | cut -d ":" -f1)
				chaine="$chaine$(echo "$ligneMax" | cut -d ":" -f2) "
				suite=$((suite / divMax))
		fi
	done
	
	tmpDiv=$((1))
	for j in $chaine; do tmpDiv=$((tmpDiv * j)); done
	nombreDiviseur=$((tmpDiv))
	incr=$((incr+1))
done
echo "le $incr nombre triangulaire a $nombreDiviseur diviseurs"
