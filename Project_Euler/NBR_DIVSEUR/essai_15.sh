#!/bin/sh

source fonctions.sh

[ -f resultats.txt ] && rm resultats.txt

#On nettoie le fichier base_div.txt qui peut contenir des doublons.
sort base_div.txt | uniq  > tmp.txt && mv tmp.txt base_div.txt

n=$((2))
n_1=$((3))
valTmp=$((1))
diviseur500=$((100000000000))
tmpVal=$((n*n_1))
divNbrT=$((0))
nbrT=$((0))

while [ $tmpVal -lt $diviseur500 ]
do	foo1=$(grep "^$n:" base_div.txt)
	foo2=$(grep "^$n_1:" base_div.txt)
	
	[ -z "$foo1" ] && divN=$(nbr_diviseur $n) && echo "$n:$divN" >> base_div.txt || divN=$(echo "$foo1" | cut -d ":" -f2)
	[ -z "$foo2" ] && divN1=$(nbr_diviseur $n_1) &&  echo "$n_1:$divN1" >> base_div.txt || divN1=$(echo "$foo2" | cut -d ":" -f2)
	divTmp=$((divN * divN1))
	
	while [ $divNbrT -le 500 -a $nbrT -lt $diviseur500 ]
	do	plus1=$((tmpVal+1))	
		nbrT=$((tmpVal * plus1/2))
		if [ $((tmpVal % 2)) -eq 0 ]
		
		then	pairTmp=$((tmpVal/2))
				divPairTmp=$(grep "^$pairTmp:" base_div.txt)
				if [ -z "$divPairTmp" ]; then divPairTmp=$(nbr_diviseur $pairTmp) &&  echo "$pairTmp:$divPairTmp" >> base_div.txt 
				else divPairTmp=$(echo "$divPairTmp" | cut -d ":" -f2)
				fi

				divPlus1=$(grep "^$plus1:" base_div.txt)
				if [ -z "$divPlus1" ]; then divPlus1=$(nbr_diviseur $plus1) && echo "$plus1:$divPlus1" >> base_div.txt 
				else divPlus1=$(echo "$divPlus1" | cut -d ":" -f2) 
				fi
				divNbrT=$((divPlus1 * divPairTmp))

		else 	pairTmp=$((plus1/2))
				divPairTmp=$(grep "^$pairTmp:" base_div.txt)
				[ -z "$divPairTmp" ] && divPairTmp=$(nbr_diviseur $pairTmp) &&  echo "$pairTmp:$divPairTmp" >> base_div.txt || divPairTmp=$(echo "$divPairTmp" | cut -d ":" -f2)
				divTmp=$(grep "^$tmpVal:" base_div.txt)
				[ -z "$divTmp" ] && divTmp=$(nbr_diviseur $tmpVal) && echo "$tmpVal:$divTmp" >> base_div.txt || divTmp=$(echo "$divTmp" | cut -d ":" -f2) 
				divNbrT=$((divTmp * divPairTmp))
		fi
		tmpVal=$((nbrT))
	done

	if [ $nbrT -le $diviseur500 -a $nbrT -gt 0 -a $divNbrT -ge 500 ]; then echo "$nbrT a $divNbrT diviseurs" | tee -a resultats.txt; fi
 	[ $diviseur500 -gt $nbrT -a $nbrT -gt 0 ] &&  diviseur500=$((nbrT))
	
	n=$((n_1))
	n_1=$((n_1 + 1))
	tmpVal=$((n * n_1))
	nbrT=$((0))
	divNbrT=$((0))
done
