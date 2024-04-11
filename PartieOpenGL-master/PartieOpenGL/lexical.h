#ifndef LEXICAL_H
#define LEXICAL_H
#include "jeton.h"
#include <ctype.h>
#include <string.h>

int lire_jeton(const char* s, typejeton T[], typeerreur* erreur);

void afficher_jeton(typejeton jeton[], int nb_jetons);


#endif 