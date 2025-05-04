fp =: ~. @ q:                             NB. obtenir la liste des facteurs premiers du nombre en entrée
mask =: (0 < */@(fp |/ 1+i.)) # (1+i.)    NB. obtenir la liste des entiers avec lesquels l'entrée est premier
fr_pb73 =: monad : 0                      NB. fonction monad qui pour l'entrée trouve le nombre de fractions
deno =: y                                 NB. simplifiées ayant pour dénominateur y et > 1/3 et < 1/2
pr =: mask y
cond =: (3&* > deno"0) *. (2&* < deno"0)  NB. vérifier les premiers relatif de y qui vérifient la condition 
                                          NB. y < 3*pr et y > 2*pr, où pr est un premier relatif
list_index =: I. cond"0 pr
list_fraction =: (1%y)&* list_index { pr
(y) , (# list_index)
)

+/ fr_pb73 (1+i.12000)

NB. Olegyk code : 
$~.;(<@#~ >&(%3) *. <&0.5)@:%"0 1/~ >:@i.10000
