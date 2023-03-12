#!/bin/sh

if [ -e ligne_De13.txt ]; then rm ligne_De13.txt; fi
if [ -e tmp.txt ]; then rm tmp.txt; fi
if [ -e result.txt ]; then rm result.txt; fi
chaine=$(cat largest_product_data.txt | tr -d '\012')
taille=$(echo ${#chaine})
limite=$((1000-13))
for((i=0; i<=$limite; i++))
do 

#	limj=$((i%13))
#	for((j=0; j<=$limj; j++))
#	do echo  " \c" >> ligne_De13.txt
#	done

	echo ${chaine:$i:13} >> ligne_De13.txt
done
#on élimine les lignes avec des zéros
sed -E 's/.*0.*//g' ligne_De13.txt > tmp.txt
grep -E '^[0-9]{13}$' tmp.txt > result.txt
#on fait un fichier de somme sur lequel on travaille
sed -E 's/([0-9])/\1\+/g' result.txt | sed -E 's/\+$//g' > tmp.txt 
#On boucle pour trouver le plus grand
greater=$((0))
while read line
do	
	actuel=$((line))
	if [ $greater -lt $actuel ]
	 then	greater=$((actuel))
			original="$line"
			original2=$(echo $original | sed -E 's/\+/\*/g')
			res2=$((original2))
			echo "orignal2 vaut: $original2 = $res2"
			echo "original vaut: $original = $greater"
	fi
done < tmp.txt
#On affiche notre plus grande valeur
original=$(echo $original | sed -E 's/\+/\*/g')
echo "le produit est : $original et vaut $((original))"
echo "la plus grande chaine est donc $(echo $original | tr -d '*')"
