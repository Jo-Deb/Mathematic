struct g_list {
	int elt; 
	struct g_list * l; 
	struct g_list * prev;
};

typedef struct g_list list;

extern int    listLongueur(list * l);

extern list * ajoutFin(list * l, int n);

extern list * deleteLastElts(list * l, int n);

extern int    getElt(list * l, int n);

extern void   afficheList(list * l);

extern list * getPartList(list * l, int n);

extern void   freeList(list * l);

extern list * supprimElt(list *l, int elt);

extern list * concatList(list * l1, list * l2);

extern int 	  getLastElt(list * l);

extern int    gl_isPresent(list * l, int elt);
