#include <stdio.h>

/*The Fibonacci sequence is defined by recurrence relation:
*Fn = Fn-1 + Fn+2, where F1=1=F2
*The 12th term, F12 is the first term to contain three digits.
*what is the index of the first term in the Fibonacci sequence to contain 1000 digits
*
*Pour la résolution, on passe par un chgt de base (base binaire), car on constate en base 2 que:
*quand la taille en digit de l'elt est pair en base alors :
*	soit l'elt précédent à aussi la même taille et alors l'elt suivant aura la taille + 1
*	soit l'etl précédent à une taille impaire
*/