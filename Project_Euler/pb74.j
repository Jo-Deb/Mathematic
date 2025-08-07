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
NB.################################################################################################################
NB. On essaie une nouvelle solution, la précédente ne peut pas gérer le seuil de 1000000
itl =: 10&(#.^:_1)   NB. monad qui prend un nombre et retourne une liste
sf =: +/@:!@:itl       NB. prend un entier en entrée et retourne la somme des factorielles des digits qui composent l'entier

NB. une fonction initialise_m qui met en place les prérequis
initialise_m =: monad : 0
    m =: ((],.sf)"0 i.y) ,. (y,1)$0
    lg =: ''
    nbrlm =: y
)
NB. l'objectif de compléter les valeurs inférieurs à 100 pour lesquelles on ne connait pas la longueur
NB. l'argument à gauche du verbe (x) représente la taille de la liste initiale d'où le préfixe est tiré.
complete_lg =: dyad : 0
    if. 0 = #y do. return. end.
    ql =. {: y
    if. ql < nbrlm do. 
        idx =. <(ql, 2)
        m =: (x - #y) idx } m
    end.
)
m =: (],.sf)"0 i.1e6
lg =: ''
NB. calculer la chaine factorielle
callg =: monad : 0
    e1 =: {.lg
    if. (#lg) > 0 do. idx =: < (e1, 2) end.
    if. y < nbrlm do. tch =: 2 { (y{m) else. tch =: 0 end.
    if.(0 = #lg) *. (tch > 0) do. y return. end.
    NB. si y est dans lg
    if. (y e. lg) do.
        m =: (#lg) idx } m
        (#lg)&complete_lg\ (}.lg)
        lg return.
    end.
    NB. si y n'est pas dans lg et qu'on connait la taille de sa chaine factorielle
    if. (0 = y e. lg) *. (tch > 0) do.
        m =: (tch + #lg) idx } m
        (tch + #lg)&complete_lg\ (}.lg)
        (lg =: lg, y) return.
    end.
    NB. Si on arrive ici c'est que y n'est pas dans lg et son tch n'est pas connu
    lg =: lg, y
    if. (0 = y e. lg) *. (y < 1e6) do. callg (1 { (y{m)) return. end.
    callg (sf y)
)

v =: monad : 0 
    echo 'traitement : ', (":{.y), ' en cours'
    lg =: ''
    callg {.y
    (":lg) fappends '/Users/jojo/Informatique/Mathematic/Project_Euler/pb74.txt'
    if. 1<#y do. (}.y) return. end.
    if. 1 = #y do. _2 Z: 1 end.
)
NB. les deux instructions suivantes ont permis d'avoir le résultat.
initialise_m 1000000
]F.v i.1000000
NB. maintenant il faut trier m et garder uniquement les lignes qui ont une valeur supérieure ou égale à 60
60 >: 2({"1)m
NB. identifier les indices
I. 60 <: 2{"1]m

NB. Olegyk code 
NB. cette fonction n permet de casser un nombre en ces digits et de calculer la somme 
NB. de la valeur factorielle de chaque digit
n=: +/@(!@"."0@":@x:) NB. x: permet de récupérer l'entrée de la monade et d'en déterminer le rang, 
NB. ensuite cette entrée est donnée à la fonction ": "
N=: n"0 i.1000000
+/60&=#@((,`[@.(e.~) n`({&N)@.(<&1e6)@{:)^:_)"0 i.1e6

(,`[@.(e.~) n`({&N)@.(<&1e6)@{:) NB. Hook : [x] (u v) y = (x or y) u v y
