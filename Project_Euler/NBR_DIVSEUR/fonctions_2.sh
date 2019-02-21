#!/bin/sh

trouveDiviseur(){
nbr_argu=$1
arret=$((0))
racine=$(echo "sqrt($nbr_argu)" | bc -l | cut -d "." -f1 )
line=$((0))
retour=$((nbr_argu))

while [ $arret -eq 0 -a $line -le $racine ]
do	read line
	if [ $((nbr_argu % line)) -eq 0 ]
	then 	arret=$((1))
		retour=$((line))
	fi
done < base_nbr_premiers.dat

echo "$retour"
}

maxPuissance(){
triangulaire=$1
premier=$2
max=$2
puissance=$((1))
stop=$((0))

while [ $stop -eq 0 ]
do	tmp=$((max * premier))
	if [ $((triangulaire % tmp)) -eq 0 ]
	then	max=$((tmp)) && puissance=$((puissance + 1))
	else stop=$((1))
	fi
done

premier=$((premier + 1))
echo "$max:$puissance"
}
