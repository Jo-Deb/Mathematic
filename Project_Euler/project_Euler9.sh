#!/bin/sh

#On essaie de trouver un triplet pythagoricien telle que a + b + c = 1000
#Une propriété dit que si v > u et de parité différente tel que 2v(u+v)=1000
#alors a= v^2 - u^2 et c=v^2+u^2 et b = 2uv

parite(){
arg1=$1
arg2=$2
par1=$((arg1 % 2))
par2=$((arg2 % 2))
echo $((par1*par2))
}

for((v=16; v < 23; v++))
do
	for((u=0; u < $v; u++))
	do	if [ $(parite "$u" "$v") -eq 0 ];
		then 	result=$((2* v * ( u + v ) ))
				echo "2*$v*($u+$v) vaut: $result"
				if [ $result -eq 1000 ]; 
				then 	a=$(echo "$v^2 - $u^2" | bc -l)
						c=$(echo "$v^2 + $u^2" | bc -l)
						b=$(echo "2*$v*$u" | bc -l)
						echo "par consequent a=$a, b=$b, c=$c et u=$u, v=$v"
						exit 0
				fi
		fi
	done
done
