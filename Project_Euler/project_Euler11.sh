#!/bin/sh
# 1- Test pour voir comment se comporte les valeurs précédées par un 0

if [ -w pivotColonnes.txt ]; then rm pivotColonnes.txt; fi #On supprime le fichier car il sera recrée et l'écriture se fait en mode append
if [ -w pivotDiagonaleLeft.txt ]; then rm pivotDiagonaleLeft.txt; fi 
if [ -w pivotDiagonaleRight.txt ]; then rm pivotDiagonaleRight.txt; fi 
if [ -w pivotDiagoBaseInverse.txt ]; then rm pivotDiagoBaseInverse.txt; fi 
if [ -w pivotDiagoHautInverse.txt ]; then rm pivotDiagoHautInverse.txt; fi 

i=$((0))
tmp=$((0))
maxTab=(0 0 0 0)
interTab=(0 0 0 0)

tri(){
	tmpMax=$(echo ${maxTab[@]})
	tmpInt=$(echo ${interTab[@]})
	valMax=$((1))
	valInt=$((1))
	for ((l=0; l < 4; l++)) #On boucle pour éliminer les éléments se trouvant dans les deux tableaux
	do
	if [ ${maxTab[l]} -eq 0 ] 
	then 	maxTab=($(echo ${interTab[@]}))
			return	
	fi
	val=${maxTab[l]}
	if [ $(echo "$tmpInt" | grep -c "$val") -gt 0 ]
	then 	tmpMax=$(echo $tmpMax | sed s/${val}//g )	#On élimine les valeurs communes aux deux tableaux
			tmpInt=$(echo $tmpInt | sed s/${val}//g )	
	fi
	done
	
	for j in $tmpMax
	do if [ $(expr $j : 0. ) -gt 0 ]; then j=$(echo $j | cut -c 2); fi 
		valMax=$((valMax * j ))
	done #On calcule le plus grand elt
	for k in $tmpInt
	do if [ $(expr $k : 0. ) -gt 0 ]; then k=$(echo $k | cut -c 2); fi 
		valInt=$((valInt * k )) 
	done
	[ $valInt -gt $valMax ] && maxTab=($(echo ${interTab[@]})) #On compare les deux elts et on détermine le Max
}

pivot(){ #transformer les colonnes en lignes et les diagonales en lignes
	line1=""
	for((m=1; m<=20; m++))
	do	for((n=1; n<=20; n++)); do	line1="$line1 "$(sed -n "$n p" largest_product_data.txt | cut -d " " -f $m); done
		echo "$line1" >> pivotColonnes.txt
		line1=""
	done
	#Boucle pour le calcul des diagonales
	for((p=1; p<=17; p++)) #p indique la ligne de départ
	do	r=1
		line2=""
		line3=""
		w=$((20))
		for((q=$p; q<=20; q++)) #q effectue l'itération sur les lignes
		do fullLine=$(sed -n "$q p" largest_product_data.txt)
			line1="$line1 "$(echo "$fullLine" | cut -d " " -f $r)
			line3="$line3 "$(echo "$fullLine" | cut -d " " -f $w)
			w=$((w-1))
			r=$((r+1))
		done
		line4=""
		y=$((20-p))
		for ((t=1; t<=20-p; t++))
		do	s=$((p+t))
			fullLine=$(sed -n "$t p" largest_product_data.txt)
			if [ $s -le 20 -a $p -lt 17 ]; then line2="$line2 "$(echo "$fullLine" | cut -d " " -f $s);fi
			if [ $y -ge 1 -a $p -lt 17 ]; then line4="$line4 "$(echo "$fullLine" | cut -d " " -f $y);fi
			y=$((y-1))
		done		
		echo "$line1" >> pivotDiagonaleLeft.txt
		echo "$line2" >> pivotDiagonaleRight.txt
		echo "$line3" >> pivotDiagoBaseInverse.txt
		echo "$line4" >> pivotDiagoHautInverse.txt
		line1=""
	done
}

pivot

for file in largest_product_data.txt pivotColonnes.txt pivotDiagonaleLeft.txt pivotDiagonaleRight.txt pivotDiagoBaseInverse.txt pivotDiagoHautInverse.txt
do
	while read line 
	do	tabArg=($line)
		limite=$((${#tabArg[@]} - 3))
		for ((i=1; i <= $limite; i++))
		do index=$((i+3))
			interTab=($(echo "$line" | cut -d " " -f $i-$index))
			#echo "interTab vaut : ${interTab[@]}"
			tri
		done
		echo "Le plus grand produit de 4 pour la ligne $line est : echo ${maxTab[@]} \n"
	done < $file
done 
