# ===========================
# Rilevamento OS
# ===========================
ifeq ($(OS),Windows_NT)
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

# ===========================
# Variabili
# ===========================
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# File oggetto comuni
OBJ_COMMON = Utile_UtenteMenu.o HashTbUtenti.o HashTbAuto.o List_Prenotazione.o Utente.o Auto.o prenotazione.o Coda_StoricoUtente.o Controlli.o Utile_DevMenu.o

# ===========================
# Target di default
# ===========================
all: Car_sharing$(EXE) Test$(EXE)

# ===========================
# Eseguibile principale
# ===========================
Car_sharing$(EXE): main.o $(OBJ_COMMON)
	$(CC) $(CFLAGS) -o $@ main.o $(OBJ_COMMON)

# ===========================
# Eseguibile di test
# ===========================
Test$(EXE): Test.o $(OBJ_COMMON)
	$(CC) $(CFLAGS) -o $@ Test.o $(OBJ_COMMON)

# ===========================
# Compilazione file .o
# ===========================
%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c Utile_DevMenu.h Test.h Utile_UtenteMenu.h HashTbUtenti.h HashTbAuto.h List_Prenotazione.h Auto.h prenotazione.h
	$(CC) $(CFLAGS) -c main.c

Test.o: Test.c Test.h Utile_UtenteMenu.h HashTbUtenti.h HashTbAuto.h List_Prenotazione.h Auto.h prenotazione.h
	$(CC) $(CFLAGS) -c Test.c

prenotazione.o: prenotazione.c prenotazione.h
	$(CC) $(CFLAGS) -c prenotazione.c

Utente.o: Utente.c Utente.h Coda_StoricoUtente.h
	$(CC) $(CFLAGS) -c Utente.c

Auto.o: Auto.c Auto.h
	$(CC) $(CFLAGS) -c Auto.c

Controlli.o: Controlli.c Controlli.h
	$(CC) $(CFLAGS) -c Controlli.c

HashTbUtenti.o: HashTbUtenti.c HashTbUtenti.h uthash.h Utente.h Controlli.h Coda_StoricoUtente.h
	$(CC) $(CFLAGS) -c HashTbUtenti.c

HashTbAuto.o: HashTbAuto.c HashTbAuto.h uthash.h Auto.h
	$(CC) $(CFLAGS) -c HashTbAuto.c

List_Prenotazione.o: List_Prenotazione.c List_Prenotazione.h
	$(CC) $(CFLAGS) -c List_Prenotazione.c

Utile_UtenteMenu.o: Utile_UtenteMenu.c Utile_UtenteMenu.h HashTbUtenti.h Controlli.h
	$(CC) $(CFLAGS) -c Utile_UtenteMenu.c

Utile_DevMenu.o: Utile_DevMenu.c Utile_DevMenu.h HashTbAuto.h Controlli.h
	$(CC) $(CFLAGS) -c Utile_DevMenu.c

Coda_StoricoUtente.o: Coda_StoricoUtente.c Coda_StoricoUtente.h Utente.h prenotazione.h
	$(CC) $(CFLAGS) -c Coda_StoricoUtente.c

# ===========================
# Esecuzione test con argomenti passabili via variabile TEST_ARGS
# Esempio: make run_tests TEST_ARGS="test_suite.txt risultati.txt"
# Se non specifichi TEST_ARGS esegue senza argomenti
# ===========================
run_tests: Test$(EXE)
	./Test$(EXE) $(TEST_ARGS)

# ===========================
# Pulizia
# ===========================
clean:
	$(RM) *.o Car_sharing$(EXE) Test$(EXE) risultati.txt