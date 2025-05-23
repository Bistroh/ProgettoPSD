#ifndef CONTROLLI_H
#define CONTROLLI_H

int stringaValida(const char *str);
int confrontaCaseInsensitive(const char *a, const char *b);
int validaPassword(const char *pwd);
int validaTarga(const char *targa);
int validaEmail(const char *email);
int validaCodiceFiscale(const char *cf);
int validaViaStradale(const char* input);
int validaTelefono(const char *numero);
void pulisciConsole();
void pausaConsole();
int validaCognome(const char *cognome);
int validaNome(const char *nome);
void capitalizza(char* nome);
#endif //CONTROLLI_H
