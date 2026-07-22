tbs =: ;/i.4                                                                NB. initialisation du tableau des solutions
pl =: p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getCol =: 4 : 'x {"(0,1) y' NB. récupère la colonne x du tableau y
addToTbs =: 4 : ' x, < (((#x)&=)@:(+/"1) # ]) y'                            NB. ajuster le contenu de y à tbs, x sera tbs lors de l'appel
noDoublon =: 3 : ' ((~:)@:(\:"1~) # ]) y'                                   NB. On élémine les doublons qui peuvent venir de listeAdditionNiv1
noDoublonNoZero =: 3 : ' ((>&0)@:+/"1 # ]) noDoublon y'                       
crossJoin =: 4 : 'y ,.~ ((0 { $y),1) $ x'                                   NB. crossJoin entre l'atome x et le tableau y               
fct1 =: 3 : 0
    NB. on attend une liste de deux éléments
    NB. s'agissant de cette 1ère ligne de code, on extrait le tableau de tbs et si le 2ème élément de y est premier et plus petit que le
    NB. 1er élément, alors on l'ajoute à t. Par exemple 20 = 13 + 7 si on ne fait pas ce qui est écrit ci-dessus on perd cette expression
    t =. (1 1 $ 1{ y) ,^:((>:/y) *. (1 p: (1{y))) > (1 { y) { tbs                  
    pp =. (0 { y)
    if. (([: # $) t) = 0 do. res =. (1,1) $ t else. res =.((<:&pp)@:(0&getCol) # ]) t end.
    if. (([: # $) res) = 1 do. res =. (1, $res) $ res end.
    if. (*/$res) = 0 do. res return. end.
    pp crossJoin res
)
pb771 =: 3 : 'tbs =: tbs addToTbs noDoublonNoZero ,/fct1"1 listeAdditionNiv1 y'"0

NB. Je mets ci-dessous les remarques que je me suis faite au cours de la connaissance du problème.
NB. il ne faut pas supprimer les doublons car 5 + 3 est différents de 3 + 5 car 5 + 3 ne sera pas étendu mais 3 + 5
NB. donnera 3 + 3 + 2
NB. On ajoute la fonction noDoublonNoZero car certaine expression comme 2 + 5, si l'on souhaite que le 1er premier soit le plus grand,
NB. ne peuvent pas être étendu car 2 + 5 = 2 + 2 + 2 + 1 et comme 1 n'est pas premier il ne s'agit pas d'une expression valable
NB. quand la fonction fct1 rencontre l'expression 2 + 5 elle retourne un tableau vide qui par le mécanisme de fill de J deviendra
NB. une suite de 0 et noDoublonNoZero permet d'éliminer ce type de lignes de notre résultat.
NB. On fait évoluer la fonction addToTbs pour qu'elle éjecte les lignes qui sont inférieure différente de la taille du tableau

NB. olegyk solution
NB. J:
   dp=: +/@:~.@q:
   <:#(, (+/@:(* dp@>:@i.@-@#) % #))^:(<&5000@{:)^:_] 1 0
71
