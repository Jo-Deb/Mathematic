tbs =. ;/i.4                                                                NB. initialisation du tableau des solutions
pl =. p: i.1001                                                             NB. liste des 1000 premiers nombres premiers
listeAdditionNiv1 =: 3 : 'l =. (] \: ]) (] ,. y&-) (<&(y-1) # ]) pl'        NB. liste des solutions à partir desquelles on va faire les énumérations
getAset =: 3 : 0
col2Liste =: 4 : ' x , y'"(1 1 1)                                           NB. colle 2 listes : x suivi de y
joinListeEtTableau =: 4 : 0
    x col2Liste
