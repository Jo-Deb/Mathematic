#!/bin/sh
#le but est de trouver le plus grand palindrome par le produit de 2 digit numbers de taille 3

is_palindrome(){
#l'idée est de boucler sur notre mot d'entrée et de voir si son mirroir donne la même chaine
	mirroir=""
	origine="$1"
	longueur=${#origine}
	index=$(($longueur))
	palindrome=0
	echo "on teste si  $origine est un palindrome"
	while [ $index -gt 0 ] 
	do mirroir="$mirroir"$(echo $origine | cut -c $index)
	#	echo "à cette étape mirroir vaut : $mirroir et index vaut $index pour un mot de longueur $longueur"
		index=$(($index - 1))	
	done
	if [ "$mirroir" = "$origine" ];
		then  echo "le mot $origine est un palindrome"
				palindrome=1
		else palindrome=0
	fi
}

is_palindrome2(){
	mot="$1"
	taille=${#var}
	limite_j=$((3))
	j=$((0))
	faux="0"	
	while [ $j -lt $limite_j -a $faux = "0" ]
	do elt=$(echo ${mot:j:1})
		elt_miroir=$(echo ${mot: -((j+1)):1})
		echo " la valeur en entrée est : $mot. \$elt vaut : $elt et \$elt_miroir vaut : $elt_miroir"
		if [ $elt != $elt_miroir ]; 
		then	faux="1"
			  	palindrome=$((0))
		fi
		j=$((j+1))
	done
	if [ $faux = "0" ]; then palindrome=$((1)); fi
}

calculEnCours=$((0))
multiple_11=$((90 * 11))
i=$((90))
borne2=$((999))
while [ $multiple_11 -gt 100 ]
do 
	echo "nous sommes dans la première boucle et \$multiple_11 vaut $multiple_11"
	while [ $borne2 -gt 100 ]
	do calculEnCours=$(($multiple_11 * $borne2))
		is_palindrome2 "$calculEnCours" 
		if [ $palindrome -eq 1 ]
			then echo "$calculEnCours est un palindrome"
				  echo "On met le palindrome $palindrome dans la notre banque de palindromes de nombres"
				  echo "$palindrome" >> "banque_palindrome.txt"	
				  #exit 0
		fi
		borne2=$(($borne2 - 1))
	done
	i=$((i-1))
	multiple_11=$((i * 11))
	borne2=$((999))
done
