NB. je récupère une valeur, si je ne l'ai pas encore calculé, je calcule la somme des factorielles de ses digits
NB. si j'ai déjà calculé la somme je fais taille(lg) + taille(pour la suite du nbr déjà calculée)

itl =: 10&(#.^:_1)   NB. monad qui prend un nombre et retourne une liste
sf =: +/@:!@:itl       NB. prend un entier en entrée et retourne la somme des factorielles des digits qui composent l'entier
NB. pour savoir si une valeur est déjà dans une liste faire x e. y, c-à-d retourne 1 si x dans y sinon 0
NB. pour retirer les éléments d'une liste il faut utiliser x -. y qui retournera tous les atomes de x qui ne sont pas dans y
liste =: 1 2 3 4 5
(":"liste) fappends 'pb74.txt'    NB. permet d'ajouter la liste au fichier pb74.txt

lg =: ''
fres =: 1 2 $ _1 _1

v =: monad : 0
lg =: lg, y
sf y
)

u =: monad : 0
_3 Z: 70                                           NB. limiter à 70 itérations maximum
vc =: {."1]fres
if. (y e. vc) *. (1 = #lg) do. _2 Z: 1 end.
if. y e. lg do. 
    fres =: fres, (({.lg), (#lg)) 
    _2 Z: 1 
end.
index_y =: (y i.~ {."1]fres)
if. index_y < #vc do.
    info =: (index_y,0) {. fres
    fres =: fres, (0{.info, (1{.info) + index_y)
    _2 Z: 1
end.
y
)

vfold =: monad : 0
if. 0 = #y do. _2 Z: 1 end.
lg =: ''
res =: ''
res =: u F: v {.y 
head =: {.y
lg =: head, lg
nexty =: y -. res
nexty -. head
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
