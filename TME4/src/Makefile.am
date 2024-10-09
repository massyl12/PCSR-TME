# Utiliser bin_PROGRAMS si le programme doit être installé
# sinon, garder noinst_PROGRAMS pour ne pas installer le programme
bin_PROGRAMS = tme4

# Répertoires des fichiers d'en-tête et des sources
INC_DIR = $(top_srcdir)/include
SRC_DIR = $(top_srcdir)/src

# Flags de compilation
AM_CPPFLAGS = -I $(INC_DIR) -g -Wall -std=c++1y

# Flags de l'éditeur de liens
AM_LDFLAGS = -pthread

# Sources du programme tme4
tme4_SOURCES = $(SRC_DIR)/Banque.h $(SRC_DIR)/Banque.cpp \
                $(SRC_DIR)/Compte.h $(SRC_DIR)/Compte.cpp \
                $(SRC_DIR)/main.cpp

# Optionnel : si tu utilises des bibliothèques spécifiques pour lier ton programme
# tme4_LDADD = -lmylib

# Si tu veux installer les fichiers dans un dossier spécifique
# (par exemple, pour les fichiers d'en-têtes)
# include_HEADERS = $(SRC_DIR)/Banque.h $(SRC_DIR)/Compte.h

# Si tu veux spécifier un répertoire d'installation pour les binaires compilés
# bin_PROGRAMS = tme4
