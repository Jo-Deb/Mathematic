#!/bin/sh

while read palindrome 
do
#	ligne=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_nombre_premier.pl "$palindrome")
	while read multiple_11
	do
	#On teste si le palindrome est divisible par le multiple_11
		valeur=$((palindrome))
		multiple=$(($multiple_11))	
		reste=$((valeur % multiple))
#		echo "la valeur du reste pour \$valeur % \$multiple est : $reste"
		if [ $((reste)) -eq 0 ]
 		then 	quotien=$((valeur / multiple))
				echo "$multiple * $quotien donne $palindrome" 
				if [ $((quotien)) -lt 999 ]
				then 	echo "le palindrome $palindrome respecte les conditions"
						exit 0
				fi
		fi	
	done < multiple_de_11.txt
done < palindrome_liste.txt
