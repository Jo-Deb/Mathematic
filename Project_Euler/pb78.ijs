res =: (1 2 $ 1x 1x), (1 2 $ 1x 1x)                                                                
liste_PNK =: 3 : '(((],1:) $ ]) ,. }.@:i.@:(+&1)) y'                            
testCondition =: 4 : '(1*((x=y)+.(y=1))) + (2*((y=0)+.(y>x))) + 3*((x>y)*.(y>1))'
getElement =: 4 : '((< (x-1),(y-1)) { res) + ((<(x-y),y) { res)'
agenda =: 4 : 'x (0:`1:`0:`getElement@.testCondition) y'"(0,0)
pnFirst =: 3 : '((0&{ - 1:) agenda (1&{ - 1:)) y'"1
pnSecond =: 3 : '((0&{ - 1&{) agenda (1&{)) y'"1
partition =: 3 : 0
    t =. liste_PNK y
    res =: res, (+/,]) (x:)@:(pnFirst + pnSecond)"1 t
)
nombrePentagonaux =: 3 : 'x: (%&2) ( ( ((*&3)@:*: + ]),( (*&3)@:*: - ]) ) * (_1:`1:@.(2&|)) ) y'"0
nbp =: nombrePentagonaux i.101
lpn =: (1 1 2 3)
getPentagonalNumber =: 3 : '((I.@:(<:&y)@:|) { ]) , }. nbp'
partitionEuler =: 3 : 0
    if. y < # lpn do. y { lpn return. end.
    lb =. ( * ,: (y&-)@:|) getPentagonalNumber y
    valeurPartition =. , (1 { lb) { lpn
    listeSigne =. , 0 { lb
    lpn =: lpn , x: +/ listeSigne * valeurPartition
)

NB. Je mets ici bas les commentaires du code
NB. res : initialisation du tableau qui va contenir toutes les valeurs p(n,k) 
NB. liste_PNK : fonction qui génère un tableau listant les p(n,k) à calculer
NB. testCondition : fonction qui sera utiliser dans un agenda pour déterminer la valeur à retourner
NB. si testCondition donne 1 on retournera 1 pour 2 ce sera 0 et pour 3 une fonction sera appliquée
NB. les entrées de la fonction testCondition sont x = n et y = k, on implémente l'algorithme : https://tinyurl.com/msfbuuvt
NB. getElement : récupère une valeur dans le tableau res. x indique la ligne, y la colonne.
NB. partition doit permettre de calculer pn(y), si pour tout x < y pn(x) et pn(x, k) est connu, x, k étant des entiers positifs
NB.la fonction nombrePentagonaux permet de déterminer les nombres pentagonaux généralisés.
NB. lpn est la liste des p(n) dans l'ordre croissant
NB. la fonction getPentagonalNumber retourne la liste des nombres pentagonaux généralisés qui sont inférieurs ou égaux à y