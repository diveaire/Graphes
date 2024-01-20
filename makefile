# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I./src/header
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
FILE_DIR = ./files
HEADERS = ./src/header/*.h

# Noms de fichiers sources
SOURCES = $(SRC_DIR)/graphe.c $(SRC_DIR)/tableauGraphe.c $(SRC_DIR)/main.c

# Création automatique des noms des fichiers objets à partir des fichiers sources
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))


# Cibles par défaut
all: directories

# Création des répertoires
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(FILE_DIR)

# Règle de compilation pour l'exécutable graphe
graphe: directories $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BIN_DIR)/graphe

# Règle pour lancer le programme
start: graphe
	$(BIN_DIR)/graphe

# Règle générique pour les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Règle pour nettoyer les fichiers de temps générés
cleanfiles:
	rm -rf $(FILE_DIR)/*

.PHONY: all clean cleanfiles graphe directories
