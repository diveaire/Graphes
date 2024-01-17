# Variables
CC = gcc
CFLAGS = -Wall -Wextra -I./src/header
SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin
FILE_DIR = ./files
HEADERS = ./src/header/*.h

# Cibles par défaut
all: directories

# Création des répertoires
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR) $(FILE_DIR)

# Règle générique pour compiler l'exercice Graphe
$(BIN_DIR)/graphe: $(OBJ_DIR)/graphe.o
	$(CC) $^ -o $@

# Règle générique pour les fichiers objets
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


# Règle pour les graphes
graphe: directories
	$(MAKE) $(BIN_DIR)/graphe
	$(BIN_DIR)/graphe


# Règle pour nettoyer les fichiers générés
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Règle pour nettoyer les fichiers de temps générés
cleanfiles:
	rm -rf $(FILE_DIR)/*

.PHONY: all clean cleanfiles arbreBinaireSimple directories
