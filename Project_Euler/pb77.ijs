tbs =. ;/i.4                                                                NB. initialisation du tableau des solutions
pl =. p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
addToTbs =: 4 : ' x, < y'                                                   NB. ajuster le contenu de x à tbs
noDoublon =: 3 : ' ((~:)@:(\:"1~) # ]) y'                                   NB. On élémine les doublons qui peuvent venir de listeAdditionNiv1
crossJoin =: 4 : 'y ,.~ ((0 { $y),1) $ x'                                   NB. crossJoin entre l'atome x et le tableau y               
fct1 =: 3 : 0
    NB. on attend une liste de deux éléments
    t =. > (1 { y) { tbs
    pp =. (0 { y)
    if. (([: # $) t) = 0 do. res =. (1,1) $ t else. res =.((<:&pp)@:(0&getCol) # ]) t end.
    if. (([: # $) res) = 1 do. res =. (1, $res) $ res end.
    pp crossJoin res
)

NB. Je mets ci-dessous les remarques que je me suis faite au cours de la connaissance du problème.
NB. il ne faut pas supprimer les doublons car 5 + 3 est différents de 3 + 5 car 5 + 3 ne sera pas étendu mais 3 + 5
NB. donnera 3 + 3 + 2