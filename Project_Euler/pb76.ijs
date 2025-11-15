getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
sortDesc =: 3 : 'y \: y'    NB. trie dans l'ordre décroissant

NB. récupère la fin de la liste x à partir de index(y)+1
endList =: 4 : ' ((1: + i.&y) }. ]) x' 

main0 =: 3 : 0
NB. si y = 5 par exemple, retourne le tableau 4 1; 3 2. Si y = 6 retourne le tableau 5 1, 4 2, 3 3
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

100 ] F:. main2 1 + i.2500

combil =: 4 : 0
NB. x = (base, len, value) et y est la liste en cours de construction, cette liste est vide au début.
    base    =. 0 { x
    len     =. 1 { x
    value   =. 2 { x
    if. ( ((+/y) + len * base) < value ) +. (base > value) do. '' return. end.
    if. ( value - (+/y) ) > base do.
        if. (#y) = 0 do. (base, (len - 1), value) combil base return.
            else. (base, (len - 1), value) combil (y, base) return.
    end.
    if. (value-(+/y)) <: base *. (value-(+/y))>0 do. (base,(len - 1),value) combil y,(value-(+/y)-(len-1)) return. end.
    y
)