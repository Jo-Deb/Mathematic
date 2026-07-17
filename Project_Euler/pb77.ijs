tbs =. ;/i.4                                                                NB. initialisation du tableau des solutions
pl =. p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getAset =: 4 : ' ((0 0,: _ 1)(<&x);.0 # ]) y { tbs'"(0,0)                   NB. récupérer les lignes de la box Y ayant le premier digit inférieur à X 
crossJoin =: 4 : 0
    NB. Faire un cross join entre les lignes de X et celle Y 
    tx =. ,/((#y), 1{$x) $"1 x                                              NB. on limite $ à la liste, il travaillera avec les atomes de nos listes
    ty =. ((#x) * (#y)) $ y                                                 NB. on travaille ici avec un tableau donc $ travaillera avec des listes,  raison pour laquelle on précise juste le nbr de lignes
    tx ,. ty
)
