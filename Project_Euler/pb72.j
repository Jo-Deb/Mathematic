phi =: 5&p:
+/ phi"0 (1+i.1000000) -. (1)
NB. la fonction 5 p: y est la fonction phi de Euler
NB. il faut retirer un de la liste 1+i.1000000 car phi 1 = 1 et 1/1 n'est pas une fraction à comptabiliser.
NB. on calcule donc phi pour chaque élément de notre liste et on somme toutes les valeurs trouver.

NB. ci-dessous le code de olegyk
tot=: * -.@ % @~. &.q:
x:<:+/tot>:i.1e6
