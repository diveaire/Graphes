#if !defined(__OUTIL__)
#define __OUTIL__

void cls(void);
int get_terminal_width();
void titre(const char *titre, const char remplissage);
void getNumber(int * nb, int max);
int getMultChoice(int* resultat, int choixMax);
char* ChaineSecurisee(char* interdits, int maxSize);

#endif
