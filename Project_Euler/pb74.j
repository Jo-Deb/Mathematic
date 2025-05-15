NB. je récupère une valeur, si je ne l'ai pas encore calculé, je calcule la somme des factorielles de ses digits
NB. si j'ai déjà calculé la somme je fais taille(lg) + taille(pour la suite du nbr déjà calculée)

itl =: 10&(#.^:_1)   NB. monad qui prend un nombre et retourne une liste
sf =: +/@:!@:itl       NB. prend un entier en entrée et retourne la somme des factorielles des digits qui composent l'entier
NB. pour savoir si une valeur est déjà dans une liste faire x e. y, c-à-d retourne 1 si x dans y sinon 0
NB. pour retirer les éléments d'une liste il faut utiliser x -. y qui retournera tous les atomes de x qui ne sont pas dans y
liste =: 1 2 3 4 5
(":"liste) fappends 'pb74.txt'    NB. permet d'ajouter la liste au fichier pb74.txt

prerequis =: monad : 0 
lg =: ''
fres =: 1 2 $ _1 _1
)

parse_list =: monad : 0
    d =: {: y
    l =: ({.,#)\. y
    in =: y i. (sf d)
    data =: in { l
    (}:l), (d, (1{data) )
)

NB. prend un nombre et la longueur de sa suite factorielle dans le contexte du pb74
middle_parse =: dyad : 0
    tl =: 1 { x
    ({:,tl&-@:#) \ y
)

v =: monad : 0
lg =: lg, y
sf y
)

u =: monad : 0
_3 Z: 70                                           NB. limiter à 70 itérations maximum
vc =: {."1 ] fres
index_y =: vc i. y
if. (index_y < #vc) *. (1 = #lg) do. 
    1 Z: 1
    y return.
end.
if. y e. lg do. 
    fres =: fres, (parse_list lg) 
    1 Z: 1                                         NB. indique que c'est la dernière itération et exécute le return qui suit
    y return.
end.
if. (index_y < #vc) do.
    info =: index_y { fres
    fres =: fres, (({.lg), (1{info) + #lg)
    fres =: fres, ( ({:fres) middle_parse (}.lg) )
    lg =: lg, y
    1 Z: 1                                         NB. indique qu'il s'agit de l'itération finale et exécute le return qui suit
    y return.
end.
y
)

vfold =: monad : 0
if. 0 = #y do. _2 Z: 1 end.
lg =: ''
u F: v {.y 
vdr =: y -. lg
echo 'nbr elt retour ', ":#vdr
vdr
)

ufold_old =: monad : 0
(":lg) fappends '/Users/jojo/Informatique/Mathematic/Project_Euler/pb74.txt'
({.lg), (# lg)
)

ufold =: monad : 0
(":lg) fappends '/Users/jojo/Informatique/Mathematic/Project_Euler/pb74.txt'
{:fres
)

ufold F: vfold (3+i.(1e6-3))
+/ 60 = 1 {"1 (ufold F: vfold (3 + i.(1e6-3) ) )         NB. ne marche pas très bien
