#!/bin/sh

nbr_diviseur(){
	produit=$((1))
	decomposition=$(/Users/SoPla/Personnel/Informatique/Perl/decomposition_nombre_premier.pl $1 | cut -d "=" -f2|tr '*' ' ')
	for term in $decomposition
	do	multiple=$(echo $term | cut -d "." -f1)
		pow=$(echo $term | sed -E 's/[0-9]+\.pow\(([0-9]+)\)/\1/g')
		#[ $multiple -eq 2 ] && produit=$((produit * pow)) || produit=$((produit * (pow + 1)))	
		produit=$((produit * (pow + 1)))	
  	done
	echo "$produit"
}

