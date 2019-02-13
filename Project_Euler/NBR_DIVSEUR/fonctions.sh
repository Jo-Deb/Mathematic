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

proposition_decomposition(){
	argu=$1
	limite_crible=$(echo "sqrt($argu)" | bc -l | cut -d "." -f1)
	while [ $(read line) -eq 0 -a $val -gt 0 -a $line -le $limite_crible ]
	do	[ $((argu % line)) -eq 0 ] && val=$((line))
	done < base_nbr_premiers.dat
	
	val_canon=$((val))		
	while [ $((argu % (val*val_canon) )) -eq 0 ]; do val=$((val*val_canon)); done
}
