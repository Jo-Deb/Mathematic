#!/bin/sh

[ -f "nombre_triangulaire.txt" ] && rm -f "nombre_triangulaire.txt"
[ -f "nbr_diviseurs_carre.txt" ] && rm -f "nbr_diviseurs_carre.txt"
[ -f "result.txt" ] && rm -f "result.txt"
[ -f "FileDiviseur.txt" ] && rm -f "FileDiviseur.txt"

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

n=$((1))
minIndexValue=$((100000))
indexAvec500diviseur=$((100000))
nbrDiviseur=$((1))
while [ $n -le $minIndexValue ]
do	index_prec=$((n))
	index_suiv=$((n+1))
	nbrDiviseur=$((1))

	while [ $nbrDiviseur -lt 250 -a $index_prec -le $indexAvec500diviseur ]
	do	last_prec_index_value=$((index_prec))	
		index_prec=$(echo "(index_prec * index_suiv)/2" | bc -l | cut -d "." -f1 )
		index_suiv=$((index_prec + 1))
		prec=$(nbr_diviseur $index_prec)
		suiv=$(nbr_diviseur $index_suiv)
		nbrDiviseur=$((prec * suiv ))
		echo "index_prec=$index_prec, index_suiv=$index_suiv et nbrDiviseur=$nbrDiviseur" 
	done
	
	[ $indexAvec500diviseur -gt $index_prec ] && indexAvec500diviseur=$((index_prec))	
	[ $last_prec_index_value -lt $minIndexValue ] && minIndexValue=$((last_prec_index_value))
	echo "$index_prec terme =  $(( (index_prec * index_suiv)/2)) \t  $nbrDiviseur diviseurs \t et  minIndexValue=$minIndexValue" | tee -a "nombre_triangulaire.txt"
	n=$((n+1))
	
done

nbrDiviseur=$((2))
index_suiv=$((n))
#until [ $nbrDiviseur -gt 50 ]
#do	
#	prec=$((suiv))
	nbrDiviseur=$(nbr_diviseur $index_prec) 
	index_prec=$((index_prec+ 1))
#	nbrDiviseur=$((prec * suiv ))
#	echo "index_prec=$index_prec, nbrDiviseur = $nbrDiviseur" | tee -a  FileDiviseur.txt
#done

#while [ $n -le 2160 -a $nbrDiviseur -le 500 ] 
#do	val=$((n*(n+1)/2))
#	nbrDiviseur=$(nbr_diviseur $val)
#	echo "le $n terme vaut: $val et a $nbrDiviseur diviseurs" >> result.txt 
#	n=$((n+1))
#done 
#echo $(nbr_diviseur $1)
