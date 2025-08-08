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
NB. (a^2+b^2)(c^2+d^2) = (ac +/- bd)^2 + (ad -/+ bc)^2, la fonction ci-dessous représente ce calcul
NB. le terme de gauche x est le vecteur (a b), le terme de droite y est le vecteur (c d)
diophante =: dyad : 0
NB. ac ad
NB. bc bd
    t  =. x */ y
NB.    l1 =. (*:((<0;0) { t) - ((<1;1){t)) , (*:((<0;1) { t) + ((<1;0){t)) 
NB.    l2 =. (*:((<0;0) { t) + ((<1;1){t)) , (*:((<0;1) { t) - ((<1;0){t)) 
    l1 =. ((<0;0) { t) - ((<1;1){t) , ((<0;1) { t) + ((<1;0){t) 
    l2 =. ((<0;0) { t) + ((<1;1){t) , ((<0;1) { t) - ((<1;0){t) 
    l1,:l2
)
NB. Fonction pour rechercher une valeur dans un tableau, elle retoune la liste des lignes dans lesquelles se trouve la valeur.
NB. l'élément de gauche est un vecteur à 2 positions: élément 0 la valeur à rechercher et élément 1 la colonne du tableau 
NB. dans laquelle se trouve cette valeur
get_line =: dyad : 0
    elt =. 0 { x
    col =. (1{x) get_col y
    (I.elt&= col) { y
)
NB. définir une nouvelle fonction qui initialise un tableau sur 11 colonnes
initialise_res =: 3 : 'resultat =:(0 11) $i.0 '
mod4 =: 3 : '4|y'                                                       NB. calcule le reste de la division par 4 
NB. une fonction pour calculer les premiers termes si la valeur d'entrée le permet
test_value =: 3 : 0
    partie1 =: ''
    lp =.+/(1&=)mod4 q: y
    if. lp>:1 do.
        partie1 =: y, (*:y),( ((*:@:]),]) (*/(((1&=)@:mod4) #])"1 q:y) ), ((*:@:]),])other_prime q:y 
    end.
NB.  partie1
)
NB. Il faut définir une nouvelle fonction search. La valeur x est c, non élevé au carré, 
NB. et y la variable resultat qui devra tout contenir. L'algorithme est le suivant : 
NB. 1 - On teste c pour calculer ses premiers pythagoriciens pp, ses premiers égalent à 3 (mod 4), nommons-les op, 
NB. ainsi que leur valeurs au carré
NB. 2 - on regarde si la valeur du produit des pp est déjà disponibles dans resultat (y) 
NB. et si oui on effectue quelques multiplications par les op pour déterminer le résultat pour x et se résultat 
NB. est ensuite joint au tableau resultat
newsearch =: dyad : 0
    c =: x 
    if. nb=.(#((c,0) get_line y)) = 0 do.
        test_value c
        if. (#partie1 > 0) do. tmp=.((3 get_col partie1), 0) get_line resultat end.
NB.        echo 'la valeur de tmp est ',(":tmp)
        if. (#tmp) > 0 do. 
NB.            echo 'on est entré dans le 2ème if'
            coef=.(5 get_col partie1)             
            cola=.coef * (6 get_col tmp)
            colb=.coef * (7 get_col tmp)
            tres =.(1 6) $ partie1
            tres =.((((tres,.cola),.colb),.(*:cola)),.(*:colb)),.(x+cola+colb)
            resultat =: resultat, tres
        elseif. (#partie1 > 0) do. 
NB.            echo 'on est entré dans le 3ème if'
            coef=.(5 get_col partie1)             
            line =. search_2 x
            a =: %:1 get_col line
            b =: %:2 get_col line
            tres =: (1 6) $ partie1
            tres =: (((((tres,.a),.b),.(*:a)),.(*:b)),.(x+a+b))
NB.            echo 'la valeur de tres est : ', (":tres)
            resultat =: resultat, tres
        end.
    end.
)
NB. exemple de valeur carré qui est représentable par des sommes de carré différentes : 25^2 = 24^2 + 7^2 ou 25^2 = 20^2 + 15^2
NB. les déclenchements effectués pour la recherche du résultat
initialise_m 750001
NB. la valeur carrée est sur la 1ère colonne
pthgrc =: (],(+/&:(1&=)&:(4&|@:q:)))"0 (1+i.750000)
NB. Identifier les triplets pythagoricien s'exprimant d'une seule et unique manière.
tpu =: ((I.@:(1&=)@:(1&get_col)) { ]) pthgrc                            NB. tpu pour Triplet Pythagoricien Unique
tp =: ((I.@:(0&<)@:(1&get_col)) { ]) pthgrc                        
prime75 =: 3 : '(1&=@:mod4 # ]) y'"1                                    NB. identifie les éléments égalent à 1 mod 4
other_prime =: 3 : '*/&(1:`((1&<@:mod4)#])@.(+/&(1&<@:mod4)>0:)) y'"1   NB. identifie les éléments avec un reste plus grand
                                                                        NB. que 1 mod 4
racine =: ,prime75 q:"0 (0 get_col tpu)                                 NB. tous les premiers de tpu qui sont égaux à 1 mod 4
coefficient =: other_prime q:"0 (0 get_col tpu)                         NB. tous les premiers de tpu qui ne sont pas égaux à 1 mod 4
res1 =: racine,.coefficient                                             NB. tableau à 2 colonnes avec en 0 la racine et en 1 les coeff
psd =: search_sqrt"0 (~.racine)                                         NB. la décomposition des premiers en somme de 2 carrés
ln =: (0 get_col psd) i. racine
tln =: ln { psd
col1_tln =: (1 get_col tln)
col2_tln =: (2 get_col tln)
tln2 =: tln,.(*:(*:col1_tln) - (*:col2_tln)),.*:(2*col1_tln*col2_tln)
sprimaire =: +/"1 tln                                                   NB. la somme des côtés des triplets (sans produit avec le coef)
NB.rres =: res1,.tln,.sprimaire,.(coefficient * sprimaire)
rres =: coefficient,.tln2
eneBwam =: coefficient,.racine,.(coefficient * racine),.(coefficient * %:4 get_col rres),.(coefficient * %:5 get_col rres)
eneBwam =: eneBwam,.(2 get_col eneBwam) + (3 get_col eneBwam) + (4 get_col eneBwam)
tailleok =: (I.(1500000&>:) 5 get_col eneBwam) { eneBwam                NB. Obtenir les lignes de eneBwam dont la 5ème colonne est < 1500000
tailleok_tri =: tailleok /: (/: 5 get_col tailleok)                     NB. trier tailleok selon sa dernière colonne triée
len =: (5 get_col tailleok_tri)                                         
longueurEtOccurence =: (~.len) numberof"(0 _)" len                      NB. Obtenir pour chaque longueur son nombre d'occurence
analyse=:I. 1&= (1 get_col longueurEtOccurence)
((I.@:(1&=)@:(1 get_col ])){]) longueurEtOccurence
mesureCote =: 3 : '(other_prime * (%:@:search_2"0@:prime75)) y'         NB. donne la longueur des 3 côtés
(1500000&<: # ]) +/ mesureCote
longueur =: monad def '+/"1@:(*/@:other_prime * %:@:search_2"0"@:prime75) y'
tpu_reduit=: ((1500000&<)@:(2&*) # ]) (0 get_col tpu)                   NB. liste des racines carrées c où 2*c > 1500000
