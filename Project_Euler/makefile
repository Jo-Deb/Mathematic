myExe_68 : pb68.o gestionList.o genList.o fonctionsPratiques.o liste.o
	cc -o myExe_68 pb68.o gestionList.o genList.o fonctionsPratiques.o liste.o

liste.o : liste.c liste.h
	cc -c -g liste.c

fonctionsPratiques.o : fonctionsPratiques.c fonctionsPratiques.h
	cc -c -g fonctionsPratiques.c

gestionList.o : gestionList.c gestionList.h
	cc -c -g gestionList.c

genList.o : genList.c genList.h
	cc -c -g genList.c

pb68.o : pb68.c
	cc -c -g pb68.c

clean : 
	rm liste.o fonctionsPratiques.o gestionList.o genList.o pb68.o
