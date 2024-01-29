#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// Fonction qui utilise les séquences d'échappement ANSI pour effacer l'écran
void cls(void) {
    printf("\x1b[2J\x1b[H");
}
// Fonction pour obtenir la largeur du terminal
int get_terminal_width() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

// Fonction pour afficher le titre centré avec le caractère spécifié
void titre(const char *titre, const char remplissage) {
    int terminalWidth = get_terminal_width();
    int titreLength = strlen(titre);
    int paddingLength = (terminalWidth - titreLength) / 2;
    int i;

    // Imprimer les caractères de remplissage avant le titre
    for (i = 0; i < paddingLength; i++) {
        putchar(remplissage);
    }

    // Imprimer le titre
    printf("%s", titre);

    // Ajuster pour les largeurs impaires de terminal
    if ((terminalWidth - titreLength) % 2 != 0) paddingLength++;

    // Imprimer les caractères de remplissage après le titre
    for (i = 0; i < paddingLength; i++) {
        putchar(remplissage);
    }

    putchar('\n'); // Nouvelle ligne à la fin
}


/* Fonction permettant de récupérer un entier de stdin entre 0 et max */
void getNumber(int * nb, int max){
    while ( *nb < 0 || *nb > max ){
        if (scanf("%d", nb) != 1) {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            // Nettoyer le tampon d'entrée
            while (getchar() != '\n') continue; // skip la suite
        }
        if (*nb < 0 || *nb > max ) printf("Merci d'entrer un choix possible.\n");
    }
}

int getMultChoice(int* resultat, int choixMax) {
    char choix[100];
    char caractereMax = 'a' + choixMax - 1; // Calculer le caractère maximal autorisé

    printf("Entrez votre choix (parmi les caractères 'a' à '%c', ou '0' pour annuler) : \n", caractereMax);
    scanf("%26s", choix); // Lit jusqu'à 26 caractères

    // Vérifier si l'utilisateur souhaite annuler
    if (choix[0] == '0' && choix[1] == '\0') {
        return -1;
    }

    *resultat = 0;
    for (int i = 0; i < (int) strlen(choix); ++i) {
        if (choix[i] >= 'a' && choix[i] <= caractereMax) {
            *resultat |= 1 << (choix[i] - 'a');
        } else {
            printf("Caractère '%c' non autorisé. Veuillez réessayer.\n", choix[i]);
            *resultat = 0; // Réinitialiser le résultat et demander une nouvelle saisie
            while (getchar() != '\n'); // Nettoyer le buffer
            return getMultChoice(resultat, choixMax);
        }
    }
    return 0;
}

// const char * interdits = "!@\"#$%^&*() "; // Exemple de caractères interdits
// Fonction pour obtenir une chaine de caractère sans les caractères interdits passés en paramètre
char* ChaineSecurisee(char* interdits, int maxSize){
    bool test = true;
    char* chaine = NULL;
    chaine = (char*)malloc(sizeof(char)* maxSize);
    while(test)
    {
        scanf("%s", chaine);
        for (int i = 0; i < (int) strlen(interdits); ++i) {
            if (strchr(chaine, interdits[i]) != NULL) {
                printf("La chaîne contient des caractères interdits. Veuillez réessayer.\n");
                break;
            }
            else
            {
                test = false;
            }
        }
    }
    return chaine;
}

void execute(char *command) {
    pid_t pid = fork();

    if (pid == -1) {
        // Échec de fork
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processus enfant
        execl("/bin/sh", "sh", "-c", command, (char *) NULL);
        // Si execl échoue
        perror("execl");
        exit(EXIT_FAILURE);
    } else {
        // Processus parent
        wait(NULL); // Attendre la fin du processus enfant
    }
}