getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
sortDesc =: 3 : 'y \: y'    NB. trie dans l'ordre décroissant

NB. récupère la fin de la liste x à partir de index(y)+1
endList =: 4 : ' ((1: + i.&y) }. ]) x' 

main0 =: 3 : 0
    NB. si y = 5 par exemple, retourne le tableau 4 1; 3 2. 
    NB. Si y = 6 retourne le tableau 5 1, 4 2, 3 3
    if. y > 1 do.
        col =. 1 + i.(<. y%2)
        (y&-,. ]) col
    end.
)

main1 =: 3 : 0
    NB. ici nous avons la fonction principale elle prend l'élément le plus grand de chaque liste 
    NB. y applique main0 et concatène le résultat avec la suite de la liste
    NB. exemple : si j'ai la liste (5 1) après application de main1 j'aurai (4 1 1, 3 2 1)
    head    =:  0 getCol y
    queue   =:  }. y
    taq     =:  ((<. head%2) , #queue) $ queue
    NB. on s'arrange pour que queue soit toujours une liste
    res0    =:  sortDesc"(1) (main0 head),. taq 
)

main2 =: 4 : 0
    NB. cette fonction est celle qui doit être appelé avec les fold
    echo 'l''itération ',(":x-1),' a produit :',(":y)
    echo 'C''est la ',(":x),' itération'
    if. (y > 1) *. (#y) = 1 do. main0 y return. end.
    if. ((#$y) = 1) *. ((#y) = +/y) do. (0 Z: 1) else. tmp =: ,/main1"(1) y end. 
    NB. le ELSE du dernier IF dégrade les dimensions du résultat. 
    NB. La ligne ci-dessous permet de retravailler le résultat.
    tres =: ~.tmp
    NB. tres =: ( (*/@:}: , {:)@:$ $ ;) tmp
)

NB. 100 ] F:. main2 1 + i.2500

combil =: 4 : 0
    NB. x = (base, len, value) et y est la liste en cours de construction, cette liste est vide au début.
    base    =: 0 { x
    len     =: 1 { x
    value   =: 2 { x
    if. ( ((+/y) + len * base) < value ) +. (base > value) do. '' return. end.
    if. ( value - (+/y) ) > base 
        do.
            if. (#y) = 0 do. (base, (len - 1), value) combil base return.
                else. (base, (len - 1), value) combil (y, base) return.
            end.
    end.
    if. ((value-(+/y)) <: base) *. (value-(+/y))>0 do. (base,(len - 1),value) combil y,(value-(+/y))-(len-1) return. end.
    y
)

pivot =: 4 : 0
    NB. x est la liste et y un élément de la liste
    id =. x i. y
    if. id = (#y) do. echo (":y), 'n''est pas dans la liste d''entrée' return. end.
    if. (0 <: id-1) *. ((id+1) <: (#y)-1) do.
        p =. (id-1) { x
        f =. (id+1) { x
        if. p >: y > f+1 do. 1 return. else. 0 return. end.
    else. 0 return. end.
)

pivot2 =: 4 : 0
    NB. x est une liste et y un indice de la liste
    if. y > #x 
        do. echo 'l''indice en entrée ',(":y),' est invalide'
            0 return. end.
    if. 0 < y < (#x) - 1 
        do. if. (((y-1){x) >: (y{x)) *. ((y{x) - ((y+1){x)) >: 2  do. 1 return.
                else. 0 return. end.
        else. 0 return. end.
)
pivot3 =: (] pivot2"(1,0) i.@:#)
NB. la fonction ci-dessous permet d'avoir l'index du pivot le plus petit
spid =: >./@:I.@:(] pivot2"(1,0) i.@:#)

lisse =: 3 : 0
    NB. elle lisse la liste y pour trouver une autre liste de taille #y dont la somme vaut +/y
    id =. spid y
    val =. (<:@:(id&{), >:@:((id+1)&{)) y
    res =. val (id, (id+1))} y
)

lisse2 =: 3 : 0
    NB. elle lisse la liste y pour trouver une autre liste de taille #y dont la somme vaut +/y
    id =. y
    val =. (<:@:(id&{), >:@:((id+1)&{)) y
    res =. val (id, (id+1))} y
)

lissage =: 4 : 0
    NB. x est un atome au sens du langage J et y est une liste.
    echo 'génération des possibilités pour : ',(":y)
    if. 0 < +/ pivot3 y do. lisse y return. else. (0 Z: 1) return. end.
) 
NB. (35 35 29 1) ] F:. lissage i.2500

fct76 =: 3 : 0
    NB. de façon générale quand on a une liste ordonnée (a1 a2.. aN),
    NB. de façon décroissante numériquement et dont la somme
    NB. donne une valeur V, on peut passer à une autre liste en prenant 
    NB. e, qui est la plus petite valeur de la liste supérieure à 1. 
    NB. Faire la somme de tous les éléments de la liste inférieure à e et y ajouter e,
    NB. appelons cette somme N1, alors la représentation de N1 sous forme d'addition 
    NB. avec e-1 comme valeur la plus grande est obtenu à partir de la fonction combil.
    if. ($y) = 0 do. (y-1),1 return. end.  
    e   =. <./ (1&<@:] # ]) y              
    idm =. y i: e                          
    s   =. +/ ((i.#y) -. (i.idm)) { y      
    res =. ((i.idm) { y), ((e-1), (>.s%(e-1)), s) combil '' 
    (":res) fappends 'test76.txt'
    res
)

fld =: 4 : 0
    if. (#y) = (+/y) do. (_2 Z: 1) end.
    NB.echo 'itération ',(":x), ' en cours'
    fct76 y
)

NB. 100 ] F:. fld (i.10000000)

NB. version 2
NB. ti est le tableau dans lequel on conservera toutes les valeurs calculées.
ti =: ((%&2,2:)@:#$]) (0,0,1,0,2,1,3,2,4,4,5,6,6,10,7,14,8,21,9,29)

NB. la fonction suivante est pour calculer la liste des valeurs à ajouter dans ti en fct de y
list76 =: 3 : '(i.(y+1)) -. (i.#ti)'

express76 =: 4 : 0
    NB. Permet d'exprimer y en fonction de x, sous la forme d'une liste ou tous 
    NB. les éléments sont inférieures ou égalent à x et la somme de la liste = y
    c =. (0,x)#:y
    if. ({:c) > 0 do.((#&x)@:{.,{:)c else. (#&x)@:{.c end.
) 
score =: 4 : 0
	NB.Permet de calculer le score d'une liste dans le cadre du problème euler76.
   NB.le score d'une liste est le nbr de liste qu'on peut avoir en décomposant
   NB. les sommes possibles qui représentent le dernier digit. 
	echo 'x égale ',(":x), ' et y égale ',(":y)
    c =. (+/@:(=&1), +/@:(=&2)) y
    if. c -: (0, 0) do.
        le =. (_1 { y) { ti 
        lescr =. 1 getCol le
        (x+1+lescr),2 return.
        NB.(x+1+ (1 getCol((_1{y){ti))),2 return.
    else.
        ((x+1+(1{c)),1 + +/c) return.
    end.
)
main3 =: 3 : 0
    NB.Une fonction récursive qui calcule le nombre de façon différente d'exprimer
    NB. y sous forme de somme.
    echo 'en cours de calcul de ',(":y)
    if. (#y) = 1 do. 
        if. y < #ti do. 1 getCol (y{ti) return. 
        else. 
            echo 'à l''intérieur du else, on va aller dans la boucle récursive'
            main3 (1,2, (y-1), 1) return. 
        end.
    end.
    echo 'y est : ',(":y)
    lu  =. 2}.y
    scr =. 0{y
    slt =. 1{y
    c=.(+/@:(=&1), +/@:(=&2)) lu
    if. (#lu) = +/c do.
        echo 'nbr combinaison pour',(":+/lu), ' est ',(":scr)
        ti =: ti,((+/lu), scr)
        return.
    end.
    b   =. ((- slt){y) - 1
    rf  =. b express76 +/(- slt){.y
    scr =. scr score ((- slt)}.lu), rf
    main3 scr,((- slt)}.lu),rf
)
foldMain =: 4 : 0
    NB. Cette fonction est proche de la fonction main3, leur objectif est le même mais
    NB. foldMain est faite pour fonctionner avec le fold. Quelques rappels sur le langage J
    NB. {. extraire un nbr d'élément (cmptm dyad), }. retirer un nbr d'élément (cmptm dyad)
    if.(#y) = 1 do.
        if. y < (#ti) do. 1 getCol y { ti return.    
        else. (1, 2, (y-1), 1) return.
        end.
    end.
    lu  =. 2 }. y
    scr =. 0{y
    slt =. 1{y
    c   =. (+/@:(=&1), +/@:(=&2)) lu
    if. (#lu) = +/c do. (1 Z: 1)
       echo 'nbr combinaison pour ',(":+/lu), ' est ',(":scr)
       ti =: ti, ((+/lu), scr) return.
    end.
    b   =. ((-slt){y) - 1
    rf  =. b express76 +/(-slt){.lu
    scr =. scr score ((-slt)}.lu), rf
	echo 'le score calculé pour ', (":((-slt)}.lu), rf), ' est ',(":scr)
    scr,((-slt)}.lu),rf
)

launch =: 3 : ' y ] F.. foldMain (i.1000000)'
NB. réaliser une fonction qui génère la combinaison suivante sans prendre en compte le dernier élément de la liste
nextListe =: 3 : 0
    NB.Si on a une liste à 1 élément
    if. (#y) = 1 do. (y-1), 1 return. end.
    NB.Obtenir l'index de l'élément l'index de l'élément le plus petit supérieure à 1 n'étant pas le dernier
    id =. (] i: 1:) (1&<) }: y
    echo 'nextListe id = ',(":id)
    NB.Obtenir la racine de la liste c-à-d la liste des éléments qui ne changent pas
    if. id > 0 do. rac =. (i. id) { y else. rac =. '' end.
    echo 'nextListe rac = ',(":rac)
    cible =. +/ id }. y
    base =. (id { y) - 1
    res =. rac, (base express76 cible)
)
vnext =: 4 : 0
    echo 'itération ',(":x)
    nextListe y
)
NB. 100 ] F.. vnext (i.1000000)
nextPivot =: 3 : 'i:&1 (2&<:)@:((_1&}.) - (1&}.)) y'
racine =: 4 : 'x {. y'
cible =: 4 : '+/ x }. y'
base =: 4 : '(x { y) - 1'

decompose =: 3 : 0
    if. (#y) = 1 *. y > 0 do. (y-1), 1 return. end.
    if. (#y) = (+/y) do. y return. end.
    id =. nextPivot y
    echo 'id = ', (":id)
    if. id = (#y)-1 do. id =. 0 end.
    echo 'la nouvelle valeur de l''id est', (":id)
    deb =. id racine y
    fin =. id (base express76 cible) y
    res =. deb , fin
)

fdecompose =: 4 : 0
    echo 'iteration ', (":x), ' en cours'
    l =. decompose y
    if. (#l) = (+/l) do. (1 Z: 1) return. end.
    l
)
launch"0 list76 70
NB. récupérer la plus petite sous-liste avec deux nombres supérieures à 2
sousListe76 =: 3 : 0 
    NB. récupérer le 1er indice de la sous-liste
    id=. <./ _2 {. I. 2&< y
    if. (#id) = 0 do. 0 return. end.
    id {. y
)
NB. comparer deux listes dans le cadre du problème 76
comparaisonListe =: 4 : 0
    NB. On trie les deux listes, on retire les 0 et on fait les comparaison
    lx =. (0&< # ]) x \: x   
    ly =. (0&< # ]) y \: y
    lx -: ly  
)
next_iteration =: 4 : 0
   NB. x est l'indice du pivot et y est la liste
   deb =. x racine y
   fin =. x (base express76 cible) y
   res =. deb, fin
)

NB.la fonction ci-dessous calcule le score et l'index
idxEtScr =: 3 : 0
    if. (#y) = 1 do. 0, 0 return. end.
	NB.test pour voir si on est à la fin
	if. (#y) = +/y do. (0,1) return. end.
	NB. ci-dessous on regarde si les 2 derniers éléments sont inférieurs à 2
	if. 1 > +/ (2&<) _2{.y do.
		id =. nextPivot y
		sc =. 1 + +/(2&=) (id+1) }. y
		(id,sc) return.
	end.
	handlingSublist y
)

handlingSublist =: 3 : 0
	NB. si la somme des deux derniers nombres est supérieure à 70 
	NB. on retourne la valeur de l'index et le score du dernier nombre
	if. 70 < +/ _2 {. y do. 
        if. (_1 { y) = 1 do. 0, 1 return.
        else. ((#y)-2), 1 getCol (_1{.y){ti return. end.
    end.
	((#y)-3), scr76 _2{.y
)

NB. ci-dessous, calculer le score d'une liste à 2 éléments dont la somme est inférieure à 20.
scr76 =: 3 : 0
	NB. si j'ai A + B avec A > B et que je connaisse le score pour C=A+B
	NB. alors score(A+B)=score(C)- [ score((A+B-1)+1) + score((A+B-2)+2)... + score((A+B-(B-1))+ B-1)]
	NB. le calcul décrit ci-dessus est ce qu'on essaie de faire ci-dessous  
	cible=. +/y
	half =. <. cible%2
	t =. (\:~ (-half) {. i.cible),.(1 + i.half)
	echo 't est égale à ',(":t)
	NB. récupérer tous les éléments qui précède y dans t
	l =. (t i. y) {. t
	echo 'l est : ', (":l)
	NB. calcluler le score de tous les éléments dans l
	s =.(#l) +  +/ 1 getCol (1 getCol l) { ti
	echo 's est égale à ', (":s)
	NB. calcul du score pour y
	(1 getCol cible{ti) - s
)
