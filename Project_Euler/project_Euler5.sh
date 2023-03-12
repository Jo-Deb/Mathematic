#!/bin/sh

#On effectue la décomposition entière des 20 premiers entiers
echo "ok le echo fonctionne"
i=$((2))

if [ -e "tmp.txt" ]; then rm "tmp.txt"; fi
if [ -e "result.txt" ]; then rm "result.txt"; fi
if [ -e "final_result.txt" ]; then rm "final_result.txt"; fi

while [ $i -le 20 ];
do 
	decomposition=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_nombre_premier.pl "$i")
	decomposition2=$(echo $decomposition | cut -d "=" -f 2 | sed -E 's/.pow\(([0-9])\)/-\1/g') 
	echo "$decomposition2" | tr '\*' '\012' | tr -d ' ' >> tmp.txt
	echo "$i est fait"
	i=$((i+1))
done

#On trie le fichier pour que la 1er ligne pour un premier particulier soit celle que l'on conserve
sort -n -r -t "-" tmp.txt >> result.txt
#Les lignes résultantes de la boucle ci-dessous sont la decomposition de notre nombre
past="foo"
present="foo"
while read line
do 
	present=$(echo $line | cut -d "-" -f 1)
	if [ $present != $past ]; then echo "$line" >> final_result.txt; fi
	past=$(echo $line | cut -d "-" -f 1) 	
done < result.txt

#On effectue le calcul de notre nombre
resultat=1
while read line
do
	prime=$(echo $line | cut -d "-" -f 1)
	power=$(echo $line | cut -d "-" -f 2)
	tmp=$(echo "$prime ^ $power" | bc -l)
	echo "prime vaut : $prime, power vaut : $power et tmp vaut : $tmp"
	resultat=$(echo "$resultat * $tmp" | bc -l)
	echo "resultat vaut $resultat"
done < final_result.txt

echo "resultat vaut : $resultat"
echo "debut de la vérification du résultat"

for ((i=2; i <= 20; i++))
do	reste=$((resultat % $i))
	if [ $reste -ne 0 ]; then echo "$i ne divise pas $resultat"; fi
done
	
