#!/bin/sh
#le but est de trouver le plus grand palindrome par le produit de 2 digit numbers de taille 3

limite=$((998001))
tableau=(9 9 8 0 0 1)
is_palindrome=$((-1))

next_palindrome(){
	demi=$((2))
	fin=$((5))
	i=$((0))

	while [ $i -le $demi ]
	do	if [ $((tableau[i])) -gt 0 -a $i -lt $demi ]; then tableau[$fin-$i]=$((tableau[i]))
		else	if [ $i -eq $demi -a $((tableau[i])) -gt 0 ]
				then	tableau[$i]=$((tableau[i]-1))
						tableau[$fin - $i]=$((tableau[i]))
				else	if [ $((tableau[i])) -eq 0 -a $i -eq 0 ]; then exit 0;
						else	tableau[$i - 1]=$((tableau[i - 1] - 1)) 
							 	tableau[$fin - $i + 1]=$((tableau[i-1]))
								while	[ $i -le $demi ]
								do	tableau[$i]=$((9))
									tableau[$fin - $i]=$((tableau[$i]))
									i=$((i+1))
								done
								i=$((fin + 1))
						fi
				fi
		fi
		i=$((i+1))
	done
#	tableau=(${tableau[0]} ${tableau[1]} ${tableau[2]} ${tableau[3]} ${tableau[4]} ${tableau[5]})
	echo "${tableau[@]}" | tr -d ' '
}

decomposition_ok(){

#différentes actions pour récupérer les valeurs qu'on puisse utiliser
mesPremiers=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_premier.pl "$1")
mesPremiers=$(echo "$mesPremiers" | sed -E -e 's/[0-9]+ = (.+)/\1/g' -e 's/pow\([0-9]+\)//g')
mesPremiers=$(echo "$mesPremiers" | tr -d . | tr '\*' ' ')

echo "Voici les facteurs de $1: $mesPremiers"
for facteur in $mesPremiers; do
	echo "le facteur vaut: $facteur"
	if [ $(($facteur)) -gt 999 ]; then is_palindrome=$((0)); fi
done

if [ $is_palindrome -eq -1 ]; then is_palindrome=$((1)); fi
}

valeur=$((100001))
while [ $valeur -gt 100000 ]
do
	tmp1=$(next_palindrome)
	echo "$tmp1" | tee -a "perimetre_palindrome"
	valeur=$((tmp1))
	echo "\$valeur vaut: $valeur"
	tmp=$((0))
	taille=$(echo "${#tableau[@]}")
	while [ $tmp -lt $taille ]
	do tableau[$tmp]=$(echo "$valeur" | cut -c "$((tmp+1))" )
		tmp=$((tmp + 1))
	done
done

#while [ $is_palindrome -ne 1 ]
#do	
#	palindrome=$(next_palindrome)
#	echo "la valeur de tableau est : ${tableau[@]}"
#	echo "$palindrome" >> "perimetre_palindrome.txt"
#	echo "On travaille avec le palindrome: $palindrome"
#	decomposition_ok "$palindrome"
#	if [ $is_palindrome -eq 1 ]; then echo "le palindrome $palindrome respecete les conditions"; fi
#done
#exit 0
