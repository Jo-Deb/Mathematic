NB. un calcul de borne a été fait. On a déduit, en utilisant l'inégalité triangulaire, que si a + b + c = 1 500 000 alors
NB. (c = 1.5e6 - (a+b)) < 7 500 000
NB.initialisation d'un tableau pour les résultats
initialise_m =: monad : 0
    res =: 0 5 $0
    m =: (*:i.y)
)

search =: monad : 0
    tt =: (i.y) { m                                NB. on récupère toutes les valeurs carées inférieures à y
    vc =: y{m                                      NB. on récupère le carré de y
    ls =: vc - (}.tt)                              NB. on calcule vc moins toutes les valeurs carrées qui lui sont inférieures
    ls =: ls (e.#[) tt                             NB. les valeurs carrées de ls qui sont dans tt
    construct ^:(0 < #ls) ls
)

composeTriplet =: dyad : 0
    triplet =:(+/,]) m&i.(x, y, (x-y))
    s =: {. triplet
    ls =: ls -. (y, (x-y))
    tl =: ((>:@:(s&{)) s} ]) tl
)

construct =: monad : 0
    g5 =: vc,(vc&-,]){.y
    res =: res,((+/,])(m i. g5)),vc
    echo 'calcul pour hypothénuse ',":vc
    ls =: y -. g5
NB.    ($:)^:(0<#ls) ls
    construct^:(0<#ls) ls
)

search_2 =: monad : 0
    tt =: (i.y) { m
    vc =: y{m
    ls =: vc - }.tt
    ls =: ls (e.#[) tt
    vc,ls
)

soses =: dyad : 0
NB. y doit être un atome et une valeur carrée, celle-ci sera additionné à toutes les valeurs carrées dans m
NB. les résultats qui seront des carrés et les sommes (%:y) + (%:x) + (%:val) qui seront inférieurs à 1500000 seront conservés
    val =: y + x
    mask =: val e. m_0             NB. conserve uniquement les éléments carrés
    soses_res =: mask # val      NB. conserve uniquement les éléments carrés.
NB.    (%:y),.(%:|soses_res-y),.(%:soses_res),.(%y)+(%:|soses_res-y)+(%:soses_res)
    (%:y),.(%:soses_res-y),.(%:soses_res),.(%:y)+(%:soses_res-y)+(%:soses_res)
)

NB. x permet d'indiquer l'index de la colonne et y le tableau où se trouve la colonne
get_col =: dyad : 0
    x {"1 ] y
)
NB. permet d'obtenir le nombre d'itération de l'atome x dans la liste y
numberof =: dyad : 0
x, +/(x = y)
)
NB. une deuxième fonction qui fait la recherche quand y est trié.
numberof2 =: dyad : 0
    l =. (x >. #y) {. y
    x, +/(x = l)
)
NB. le plus petit majorant de la racine carré de y
majsqrt =: 3 : '>.%:y'
search_sqrt =: 3 : 0
    tt =: ((y&>)#]) m
    ls =: y - }.tt
    y, %:ls (e.#[) tt
)
NB. calculer la somme des côtés
sommeCote =: 4 : 0
    coef =. (1 get_col x)
    ln =: (0 get_col y) i. (0 get_col x)
    tln =: ln { y NB. les décompositions des racines dans l'ordre de l'entrée x
    x,.tln,. (coef * +/"1 tln)
)
diophante =: dyad : 0
NB. (a^2+b^2)(c^2+d^2) = (ac +/- bd)^2 + (ad -/+ bc)^2, la fonction ci-dessous représente ce calcul
NB. le terme de gauche x est le vecteur (a b), le terme de droite y est le vecteur (c d)
NB. ac ad
NB. bc bd
    t  =.(2,2) $ ;x */ y
NB.    l1 =. (*:((<0;0) { t) - ((<1;1){t)) , (*:((<0;1) { t) + ((<1;0){t)) 
NB.    l2 =. (*:((<0;0) { t) + ((<1;1){t)) , (*:((<0;1) { t) - ((<1;0){t)) 
    l1 =.(|((<0;0) { t) - ((<1;1){t)) , (((<0;1) { t) + ((<1;0){t)) 
    l2 =. (((<0;0) { t) + ((<1;1){t)) , (|((<0;1) { t) - ((<1;0){t)) 
    l1,:l2
)

diophante2 =: dyad : 0
NB. (a^2+b^2)(c^2+d^2) = (ac +/- bd)^2 + (ad -/+ bc)^2, la fonction ci-dessous représente ce calcul
NB. le terme de gauche x est le vecteur (a b), le terme de droite y est le vecteur (c d)
NB. ac ad
NB. bc bd
    t  =.;x */ y
NB.    l1 =. (*:((<0;0) { t) - ((<1;1){t)) , (*:((<0;1) { t) + ((<1;0){t)) 
NB.    l2 =. (*:((<0;0) { t) + ((<1;1){t)) , (*:((<0;1) { t) - ((<1;0){t)) 
    l1 =.(|@:(0&{ - 3&{),(1&{ + 2&{)) t 
    l2 =.((0&{ + 3&{),|@:(1&{ - 2&{)) t
    l1,:l2
)
compute_coef =: 3 : 0
NB. La fonction calcule les coefficients a et b d'un nombre carré x tel que a^2+b^2=x^2. 
NB. On calcule les facteurs premiers pythagoriciens et on applique la fonction diophante à l'ensemble 
NB. Cette fonction sort tous les solutions possibles, ensuite on épure pour retirer les doublons et les lignes avec un coeff 0
    part1 =: ''
    lpp =: prime75 q:y
    if. (#lpp) = 1 do. tb =: search_sqrt"0 lpp 
        ((0 1),:((#tb),2))];.0 tb return.
    else. 
        t1 =: search_sqrt"0 lpp                       NB. on isole la matrice de coefficient
        t2 =:((0 1),:((#t1),2))];.0 t1                NB. on isole la matrice de coefficient
    end.
    tmp =: diophante2"(1,1)/t2
    nbl=: (*/$tmp) % 2                                NB. le nombre de lignes permet ensuite de construire un tableau à 2 dimensions
    tb =: no_zero ~.(nbl,2) $ ; tmp                   NB. on travaille tb pour obtenir un tableau de nbl lignes et 2 colonnes
)
get_line =: dyad : 0
NB. Fonction pour rechercher une valeur dans un tableau, 
NB. elle retoune la liste des lignes dans lesquelles se trouve la valeur. l'élément de gauche est 
NB. un vecteur à 2 positions: élément 0 la valeur à rechercher et élément 1 la colonne du tableau 
NB. dans laquelle se trouve cette valeur
    elt =. 0 { x
    col =. (1{x) get_col y
    (I.elt&= col) { y
)
getLine2 =: dyad : 0
NB. les paramètres sont identiques à ceux de get_line
    val=: 0 { x
    col=: 1 { x
    ls=: col get_col y
    start=: ls i. val
    end=: ls I. (val+1)
    (start + i.(end - start)) { y
)

NB. définir une nouvelle fonction qui initialise un tableau sur 11 colonnes
initialise_res =: 3 : 'resultat =:(0 11) $i.0 '
mod4 =: 3 : '4|y'                                                       NB. calcule le reste de la division par 4 
test_value =: 3 : 0
NB. une fonction pour calculer les premiers termes si la valeur d'entrée le permet
    partie1 =: ''
    lp =.+/(1&=)mod4 q: y
    if. lp>:1 do.
        partie1 =: y, (*:y),( ((*:@:]),]) (*/(((1&=)@:mod4) #])"1 q:y) ), ((*:@:]),])other_prime q:y 
    end.
NB.  partie1
)
newsearch =: 3 : 0
NB. Il faut définir une nouvelle fonction search. La valeur x est c, non élevé au carré, 
NB. et y la variable resultat qui devra tout contenir. L'algorithme est le suivant : 
NB. 1 - On teste c pour calculer ses premiers pythagoriciens pp, ses premiers égalent à 3 (mod 4), nommons-les op, 
NB. ainsi que leur valeurs au carré
NB. 2 - on regarde si la valeur du produit des pp est déjà disponibles dans resultat (y) 
NB. et si oui on effectue quelques multiplications par les op pour déterminer le résultat pour x et se résultat 
NB. est ensuite joint au tableau resultat
    c =: y 
    if. nb=.(#((c,0) get_line resultat)) = 0 do.
        test_value c
        if. (#partie1 > 0) do. tmp=:((3 get_col partie1), 0) get_line resultat end.
        echo 'la valeur de tmp est ',(":tmp)
        if. (#tmp) > 0 do. 
            echo 'on est entré dans le 2ème if'
            coef=.(5 get_col partie1)             
            cola=.coef * (6 get_col tmp)
            colb=.coef * (7 get_col tmp)
            tres =.((#cola),6) $ partie1
            tres =.tres,.cola,.colb,.(*:cola),.(*:colb),.(y+cola+colb)
            resultat =: resultat, tres
        elseif. (#partie1 > 0) do. 
            echo 'on est entré dans le 3ème if'
            coef=.(5 get_col partie1)             
NB.            line =. search_2 x
            line =. compute_coef (2 get_col partie1)
NB.         a =: %:1 get_col line
NB.         b =: %:2 get_col line
            a =: coef * 0 get_col line
            b =: coef * 1 get_col line
            tres =: ((#a),6) $ partie1
            tres =: tres,.a,.b,.(*:a),.(*:b),.(y+a+b)
NB.            echo 'la valeur de tres est : ', (":tres)
            resultat =: resultat, tres
        end.
    end.
)
no_zero =: 3 : 0
NB. récupérer les lignes où il n'y a pas de zéros dans les colonnes 0 et 1
    lis =. (I.0&=(0 get_col y)),(I.0&=(1 get_col y))           NB. la liste des lignes contenant un zéro
    ((i.#y) -. lis) { y
)
NB. exemple de valeur carré qui est représentable par des sommes de carré différentes : 25^2 = 24^2 + 7^2 ou 25^2 = 20^2 + 15^2
NB. les déclenchements effectués pour la recherche du résultat
initialise_m 750001
m_0 =: }. m
NB. la valeur carrée est sur la 1ère colonne
pthgrc =: (],(+/&:(1&=)&:(4&|@:q:)))"0 (1+i.750000)
NB. Identifier les triplets pythagoricien s'exprimant d'une seule et unique manière.
tpu =: ((I.@:(1&=)@:(1&get_col)) { ]) pthgrc                            NB. tpu pour Triplet Pythagoricien Unique
tp =: ((I.@:(0&<)@:(1&get_col)) { ]) pthgrc                        
prime75 =: 3 : '(1&=@:mod4 # ]) y'"1                                    NB. identifie les éléments égalent à 1 mod 4
other_prime =: 3 : '*/&(1:`((1&<@:mod4)#])@.(+/&(1&<@:mod4)>0:)) y'"1   NB. identifie les éléments avec un reste plus grand
                                                                        NB. que 1 mod 4
NB. il est probable que tout le travail au-dessus soit une fausse piste, mais une fausse piste qui nous a mené à une autre plus prometteuse, on espère.
nbp =: p:^:_1 (_4 p: 750000)
NB. ci-dessous la phrase pour obtenir la liste des premiers égalent à 1 (mod 4) et inférieurs ou égale à 750000
lpp =: ((1&=@:mod4) # ]) p: i.(nbp+1)
triplet_premier =: %:search_2"0 lpp
NB. la liste des triplet pytagoriciens premiers ayant la somme de leurs 3 côtés inférieure à 1500000
tps =: (1500000&>:@:(3&get_col)#]) (],.+/"1) triplet_premier
(":tps) fwrites '/Users/jojo/Informatique/Mathematic/Project_Euler/pb75_output'
ltps =: (3 get_col tps)
NB. la ligne ci-dessous permet de classer tps selon l'ordre croissant de ltps
tps =: tps /: ltps
NB. la liste des longueurs qu'on va analyser
len_val =: 12+i.(1500001-12)
NB. faire une fonction qui calcule le nombre de triplet pytagoricien de longueur y
how_many_tps =: monad : 0
    short_ltps =. ((y&>:)#]) ((ltps I. y)+1) {. ltps
    y,(#,])((0&=)@:(|&y) # ]) short_ltps 
)
resultat =: how_many_tps"0 len_val
NB. on élimine les valeurs qui ne sont pas la somme d'un triplet pythagoricien primaire
resultat_no_zero =: (((0&<)@:(1&get_col)) # ]) resultat
NB. on élimine les sommes qui sont divisibles par plusieurs triplet pythagoricien
length_of_one =: (((1&=)@:(1&get_col)) # ]) resultat
NB. une fonction pour identifier les sommes qui sont des multiples de sommes non premières. 
NB. Attention ici il faut prendre les ayant 0 ou 1 sur la 2ème colonne car certaines sommes sont directement le résultat des 
NB. des tps qui la ""plupart du temps"" ne peuvent être obtenu par un autre tps 
how_many_multiple =: monad : 0
    smaller_sum =. ~.((ltps I. y) {. ltps) , ((0 get_col length_of_one) I. y) {. 0 get_col length_of_one
    y,(#,])((0&=)@:(|&y) # ]) smaller_sum
)
res1 =: how_many_multiple"0 (0 get_col length_of_one)
NB. on filtre res1 pour obtenir le nbr de valeur ayant 1 ou 0 multiple
res2 =: ((1&>:)@:(1&get_col) # ]) res1
NB. dans les triplets premiers il y a 603 sommes qui sont en doublon, on les identifie ici
analyse_doublon=:~.((1&<)@:(1&get_col)#]) ltps numberof"(0,1) ltps
how_many_divisor =: dyad : 0
NB. les dividendes sont x et les diviseurs y, le rang de travail pour x est 0 et celui pour y 1
    if. (+/(0&=)(|&x)y) > 0 do. x,((0&=)@:(|&x)#]) y return. end.
)
NB. définition des matrices pour la génération des TPP
m1 =: (3 3) $ 1 _2 2 2 _1 2 2 _2 3
m2 =: (3 3) $ _1 2 2 _2 1 2 _2 2 3
m3 =: (3 3) $ 1 2 2 2 1 2 2 2 3
root =: (3 4 5)
res =: 0 4 $0
fct_pm =: 4 : 0   NB. cette fonction simule le produit matriciel
    x +/ . * y
)
tom =: (1 3 3) $ m1,m2,m3   NB. un vecteur de matrice
NB. fonction pour calculer les triplets pythagoriciens primitifs
NB. dont le périmètre est inférieure à 1,510e6. ttpp est un tableau de tpp 
NB. (tpp : triplet pytagoricien primitif). Pour les arguments de la dyade : x est un index
NB. et y un tableau de tpp
main0 =: 4 : 0
    ttpp =: tom fct_pm"(2,1) (x { y)
    
fct_ptt =: 3 : 0
res =: (y, +/y), res NB. On garde ce qui a été déjà calculée
if. +/y > 1.5e6 do. res return. else. fct_ptt"1 ((3 3) $ (m1 +/ . * y), (m2 +/ . * y), (m3 +/ . * y)) end.
)

NB. Calcule l'ensemble des TPP (triplet pythagoricien primitif) à partir de y
NB. et retourne uniquement les TPP dont le périmètre est inférieure à 1.5e6
main1 =: 4 : 0
    echo 'itération ', (": x),' en cours'
    rt =: (((# % 3:), 3:) $ ]) ;tom fct_pm"(2,1)/ y
    rt =: ((I.@:(<:&1.5e6)@:(+/"1)) { ]) rt
    if. (# = 0:) rt do. (_2 Z: 1) return. else. rt end.
)
res =: (1 3) $ 3 4 5
wres =: 3 : 0 
res =: res, y
)
root wres F.. main1 1+(i.2000)
lngr =: +/"1 res
lnr =: lngr numberof"(0,1) lngr NB. les longueurs et leurs occurences
(]*((i."0)@:(<.)@:(1.5e6&%))) lnr

main2 =: 4 : 0
    lt =:(]*((i."0)@:(<.)@:(1.5e6&%))) x
    lr =: 0&get_col (0, 1) get_line  lt numberof"(0,1) y
    lr,y
)

depiler =: 4 : 'x }. y'     NB. retourne y priver de ses x premiers éléments
nbrValSup =: 4 : 'x I. y'   NB. retourne l'index qui permet de placer y dans x en gardant x trié.
lngr =: lngr /: lngr        NB. on trie, dans l'ordre croissant, lngr
main3 =: 4 : 0
    l =: (>:@:(nbrValSup&x) {. ]) lngr  NB. toutes les valeurs de lngr inférieures à x
    d =: +/(0&=) l | x                  NB. le nbr de diviseurs de x dans lngr
    if. d = 1 do. y,x else. y end.      NB. si x a un seul diviseur on ajoute y à x, sinon on retourne uniquement y
)
x_arg_m3 =: 12 depiler (i. 1.5e6+1) NB. la liste des valeurs pour lesquels on doit déterminer le nbr de diviseurs
NB. provenant de lngr.

NB. la ligne ci-dessous permet de calculer les valeurs de x_arg_m3 qui n'ont qu'un seul diviseur dans la liste lngr
res3 =: '' ] F.. main3 x_arg_m3 