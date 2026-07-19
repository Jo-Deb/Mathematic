tbs =. ;/i.4                                                                NB. initialisation du tableau des solutions
pl =. p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
addToTbs =: 4 : ' y =: y, < x'                                              NB. ajuster le contenu de x à tbs
noDoublon =: 3 : ' ((~:)@:(\:"1~) # ]) y'                                   NB. On élémine les doublons qui peuvent venir de listeAdditionNiv1
crossJoin =: 4 : 'y ,.~ ((0 { $y),1) $ x'                                   NB. crossJoin entre l'atome x et le tableau y               
fct1 =: 3 : 0
    NB. on attend une liste de deux éléments
    echo 'dans la fonction fct1 : y = ', (":y)
    t =. > (1 { y) { tbs
    echo 'dans la fonction fct1 : t = ', (":t)
    pp =. (0 { y)
    echo 'dans la fonction fct1 : pp = ', (":pp)
    if. (([: # $) t) = 0 do. res =. (1,1) $ t else. res =.((<:&pp)@:(0&getCol) # ]) t end.
    if. (([: # $) res) = 1 do. res =. (1, $res) $ res end.
    echo 'dans la fonction fct1 : res = ', (":res), ' et ses dimensions sont ', (": $ res) 
    pp crossJoin res
)