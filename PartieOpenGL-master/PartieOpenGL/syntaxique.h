#ifndef SYNTAXIQUE_H
#define SYNTAXIQUE_H

#include "jeton.h"
// Fonction pour v�rifier si un jeton est un op�rateur
int est_operateur(typejeton jeton); 


Node* arbre_binaire(typejeton* entree, int long_entree);
void afficher_arbre(Node* arbre);

#endif
