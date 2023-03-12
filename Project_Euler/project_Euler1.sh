#!/bin/sh

#Euler project 1

multiples_3_5(){
compte=$((0))
i=$((0))

while [ $i -lt 1000 ]; do
	if [ $(expr $i % 3) -eq 0 -o $(expr $i % 5) -eq 0 ]; then  compte=$(expr $compte + $i) ; fi
	i=$(expr $i + 1)
done
echo "la somme des multiples de 3 et 5, inférieur ou égale 1000, est : $compte" 
}

even_fibo_numbers(){
term_n2=1
term_n1=2
term=$(expr $term_n2 + $term_n1)
compte=2
index=3

while [ $term -lt 4000000 ]; do
	term_n2=$term_n1 && term_n1=$term && term=$(expr $term_n2 + $term_n1)
	if [ $(expr $term % 2) -eq 0 ]; then compte=$(expr $compte + $term)
		echo "au rang $index, la somme vaut: $compte"
		index=$(expr $index + 1)
	fi
done
 
}

even_fibo_numbers
