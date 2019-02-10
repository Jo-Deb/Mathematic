#!/bin/sh

construction_palindrome(){
	borne=$((997))
	tab=(0 0 0 0 0 0)
	while [ $borne -ge 100 ]
	do
		for((index=0; index < 3; index++))
		do cut_index=$((index + 1))
			tab[$index]=$(echo $borne | cut -c $cut_index)
			tab[5-$index]=$(echo ${tab[index]})
		done
		echo ${tab[@]} | tr -d ' ' | tee -a "palindrome_liste.txt"
		borne=$((borne - 1))
	done
}


construction_palindrome

