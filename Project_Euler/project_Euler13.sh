#!/bin/sh

col=$((50))
sommeCol=$((0))
retenu=$((0))
res=""

while [ $col -ge 1 ]
do	sommeCol=$((retenu))
	#sommeCol=$((0))
	while read line 
	do elt=$(echo "$line" | cut -c $col)
		sommeCol=$((sommeCol + elt)) 
	done < donnees_pb13.txt
	tmp=$(echo ${sommeCol: -1})
	res="$tmp$res"
	retenu=$(echo ${sommeCol:0:${#sommeCol}-1})
	col=$((col - 1))
	echo "sommeCol=$sommeCol, retenu=$retenu et res=$res"
done
res="$retenu$res"
echo "les 10 premiers chiffres de res sont ${res:0:10}"

#col=$((1))
#sommeCol=$((0))
#res=$((0))

#while [ $col -le 14 ]
#do 
#	while read line
#	do	elt=$(echo "$line" | cut -c $col)
#	sommeCol=$((sommeCol + elt))
#	done < donnees_pb13.txt #somme de la colonne effectuee
#	res=$((res * 10))
#	res=$((res + sommeCol))
#	echo "res=$res"
	#préparation du passage à la colonne suivante
#	col=$((col + 1)) 
#	sommeCol=$((0))
#done
#echo "les 10 premiers chiffres de res sont ${res:0:10}"


#while read line
#do	sommeCol=$((sommeCol + line))
#	echo "sommeCol=$sommeCol"
#done < donnees_pb13.txt
#echo "les 10 premiers chiffres sont ${sommeCol:0:10}"
