#ifndef LEXICAL_H
#define LEXICAL_H
#include "jeton.h"

int lire_jeton(const char* s, typejeton T[]);

void afficher_jeton(typejeton jeton[], int nb_jetons);


#endif 
