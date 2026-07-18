tbs =. ;/i.4                                                                NB. initialisation du tableau des solutions
pl =. p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
getAset =: 4 : 0"0 0 
    t =. > y { tbs
    echo 't =', (":t)
    if. (([: # $ ) t) = 0 do. t return. end.
    NB. récupérer les lignes de la box Y ayant le premier digit inférieur à X
    ((<:&x)@:(1&getCol) # ]) t
)
addToTbs =: 4 : ' y =: y, < x'                                              NB. ajuster le contenu de x à tbs
noDoublon =: 3 : ' ((~:)@:(\:"1~) # ]) y'                                   NB. On élémine les doublons qui peuvent venir de listeAdditionNiv1
crossJoin =: 4 : 0
    NB. Faire un cross join entre les lignes de X et celle Y 
    tx =. ((#y),1) $ x                                                      NB. on limite $ à la liste, il travaillera avec les atomes de nos listes
    ty =. ((#x) * (#y)) $ y                                                 NB. on travaille ici avec un tableau donc $ travaillera avec des listes,  raison pour laquelle on précise juste le nbr de lignes
    tx ,. ty
)
fct1 =: 3 : 0
    NB. on attend une liste de deux éléments
    if. -. (#y) = 2 do. echo ' y ne contient pas deux éléments' return.
    else. res =. getAset/ y  end.
    (0 { y) crossJoin res
)