Car_sharing: main.o Utile_UtenteMenu.o Utile_DevMenu.o HashTbAuto.o HashTbUtenti.o List_Prenotazione.o Auto.o prenotazione.o Utente.o
	gcc -o Car_sharing main.o Utile_UtenteMenu.o Utile_DevMenu.o HashTbAuto.o HashTbUtenti.o List_Prenotazione.o Auto.o prenotazione.o Utente.o
	rm -f *.o

main.o: main.c Utile_DevMenu.h Utile_UtenteMenu.h HashTbUtenti.h HashTbAuto.h List_Prenotazione.h Auto.h prenotazione.h
	gcc -c main.c

prenotazione.o: prenotazione.c prenotazione.h
	gcc -c prenotazione.c

Utente.o: Utente.c Utente.h
	gcc -c Utente.c

HashTbUtenti.o: HashTbUtenti.c HashTbUtenti.h uthash.h Utente.h
	gcc -c HashTbUtenti.c

HashTbAuto.o: HashTbAuto.c HashTbAuto.h uthash.h Auto.h
	gcc -c HashTbAuto.c

List_Prenotazione.o: List_Prenotazione.c List_Prenotazione.h
	gcc -c List_Prenotazione.c

Auto.o: Auto.c Auto.h
	gcc -c Auto.c

Utile_UtenteMenu.o: Utile_UtenteMenu.c Utile_UtenteMenu.h HashTbUtenti.h
	gcc -c Utile_UtenteMenu.c

Utile_DevMenu.o: Utile_DevMenu.c Utile_DevMenu.h HashTbAuto.h
	gcc -c Utile_DevMenu.c

clean:
	del *.o Car_sharing.exe
