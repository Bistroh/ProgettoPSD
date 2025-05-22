# Rileva Windows o Unix
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

Car_sharing$(EXE): main.o Coda_StoricoUtente.o Controlli.o Utile_UtenteMenu.o Utile_DevMenu.o HashTbAuto.o HashTbUtenti.o List_Prenotazione.o Auto.o prenotazione.o Utente.o
	gcc -o Car_sharing$(EXE) main.o Coda_StoricoUtente.o  Controlli.o Utile_UtenteMenu.o Utile_DevMenu.o HashTbAuto.o HashTbUtenti.o List_Prenotazione.o Auto.o prenotazione.o Utente.o
	$(RM) *.o

main.o: main.c Utile_DevMenu.h Utile_UtenteMenu.h HashTbUtenti.h HashTbAuto.h List_Prenotazione.h Auto.h prenotazione.h
	gcc -c main.c

prenotazione.o: prenotazione.c prenotazione.h
	gcc -c prenotazione.c

Utente.o: Utente.c Utente.h Coda_StoricoUtente.h
	gcc -c Utente.c

HashTbUtenti.o: HashTbUtenti.c HashTbUtenti.h uthash.h Utente.h Controlli.h Coda_StoricoUtente.h
	gcc -c HashTbUtenti.c

HashTbAuto.o: HashTbAuto.c HashTbAuto.h uthash.h Auto.h
	gcc -c HashTbAuto.c

List_Prenotazione.o: List_Prenotazione.c List_Prenotazione.h
	gcc -c List_Prenotazione.c

Auto.o: Auto.c Auto.h
	gcc -c Auto.c

Utile_UtenteMenu.o: Utile_UtenteMenu.c Utile_UtenteMenu.h HashTbUtenti.h Controlli.h
	gcc -c Utile_UtenteMenu.c

Utile_DevMenu.o: Utile_DevMenu.c Utile_DevMenu.h HashTbAuto.h Controlli.h
	gcc -c Utile_DevMenu.c

Controlli.o: Controlli.c Controlli.h
	gcc -c Controlli.c

Coda_StoricoUtente.o: Coda_StoricoUtente.c Coda_StoricoUtente.h Utente.h prenotazione.h
	gcc -c Coda_StoricoUtente.c
clean:
	$(RM) *.o Car_sharing$(EXE)