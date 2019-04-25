#/bin/sh

source fonctions.sh

[ -f base_nbrDiviseur.txt ] && rm base_nbrDiviseur.txt
[ -f debugg.txt ] && rm debugg.txt
n=7895
echo "1:1" >> base_nbrDiviseur.txt
echo "2:2" >> base_nbrDiviseur.txt

get_nbrDiviseur(){
	val="$1"
	if [ $((val % 2)) -eq 0 ]
	then 	pair=$((val/2))
		 	nbrDivPair=$(grep "^$pair:" base_nbrDiviseur.txt)
			#Si le nombre n'est pas dans la base on l'y rajoute
			if [ -z "$nbrDivPair" ] 
			then	nbrDivPair=$(nbr_diviseur $pair) 
					echo "$pair:$nbrDivPair" >> base_nbrDiviseur.txt
					echo "$nbrDivPair"
			else 	echo "$nbrDivPair" | awk -F ":" '{print $2;}' | uniq
			fi

	else 	impair=$(grep "^val:" base_nbrDiviseur.txt)
			if [ -z "$impair" ] 
			then  impair=$(nbr_diviseur $val) 
					echo "$val:$impair" >> base_nbrDiviseur.txt 
					echo "$impair"
			else 	echo "$impair" | cut -d ":" -f2 | uniq
			fi
	fi
}

prec=$(get_nbrDiviseur $n)

while [ $n -lt 15625 ]
do	suiv=$(get_nbrDiviseur $((n+1)))
	div=$((prec * suiv))
	nbT=$((n*(n+1)/2))
	if [ $(grep -c "^$nbT:" base_nbrDiviseur.txt) -eq 0 ]; then echo "$nbT:$div" >> base_nbrDiviseur.txt; fi
	if [ $div -ge 500 ]
	then echo "n=$n prec=$prec suiv=$suiv prec*suiv=$div" | tee -a  result3.txt
	fi
	prec=$suiv
	n=$((n+1))
done
	

