
#include "syntaxique.h"


int mesure = 0;

Node* arbre_binaire(typejeton* entree, int long_entree) {
    Node* noeud_point = malloc(sizeof(Node));

    // Vérification de la taille de l'entrée
    if (long_entree <= 0) {
        fprintf(stderr, "Erreur : entrée vide.\n");
        return NULL;
    }

    // Si l'entrée est une seule variable ou réel, créer un nœud feuille
    if (long_entree == 1) {
        noeud_point->jeton = entree[0];
        noeud_point->pjeton_preced = NULL;
        noeud_point->pjeton_suiv = NULL;
        return noeud_point;
    }

    // Vérification et suppression des parenthèses englobantes
    int count = 0;
    if (entree[0].lexem == PAR_OUV && entree[long_entree - 1].lexem == PAR_FERM) {
        for (int i = 1; i < long_entree - 1; i++) {
            if (entree[i].lexem == PAR_OUV) {
                count++;
            }
            else if (entree[i].lexem == PAR_FERM) {
                count--;
            }
            if (count == 0) {
                // Récursion pour gérer le contenu entre les parenthèses
                return arbre_binaire(entree + 1, long_entree - 2);
            }
        }
    }

    // Recherche de fonctions
    for (int i = 0; i < long_entree; i++) {
        if (entree[i].lexem == FONCTION) {
            // Création du nœud pour la fonction
            noeud_point->jeton = entree[i];
            noeud_point->pjeton_preced = NULL;
            // Récursion pour gérer les arguments de la fonction
            noeud_point->pjeton_suiv = arbre_binaire(entree + i + 1, long_entree - i - 1);
            return noeud_point;
        }
    }

    // Recherche des opérateurs
    typeoperateur ops[] = { PUISS, DIV, FOIS, MOINS, PLUS };
    int num_ops = sizeof(ops) / sizeof(ops[0]);
    int index = -1;
    for (int i = 0; i < num_ops; i++) {
        for (int j = 0; j < long_entree; j++) {
            if (entree[j].lexem == OPERATEUR && entree[j].valeur.operateur == ops[i]) {
                index = j;
                break;
            }
        }
        if (index != -1) {
            break;
        }
    }

    if (index != -1) {
        // Un opérateur a été trouvé
        noeud_point->jeton = entree[index];
        // Création du sous-arbre pour l'opérateur
        noeud_point->pjeton_preced = arbre_binaire(entree, index);
        noeud_point->pjeton_suiv = arbre_binaire(entree + index + 1, long_entree - index - 1);
        return noeud_point;
    }

    // Si aucune opération ou fonction n'est détectée, considérer le premier jeton comme une variable/réel
    noeud_point->jeton = entree[0];
    noeud_point->pjeton_preced = NULL;
    noeud_point->pjeton_suiv = arbre_binaire(entree + 1, long_entree - 1);
    return noeud_point;
}


void afficher_arbre(Node* arbre) {
    if (arbre == NULL) {
        return;
    }

    // Affiche le jeton du nœud actuel
    switch (arbre->jeton.lexem) {
    case PAR_OUV:
        printf("PARENTHESE OUVERTE : ( \n");
        break;
    case PAR_FERM:
        printf("PARENTHESE FERMEEE : ) \n");
        break;
    case REEL:
        printf("REEL: %.2f\n", arbre->jeton.valeur.reel);
        break;
    case OPERATEUR:
        printf("OPERATEUR: ");
        switch (arbre->jeton.valeur.operateur) {
        case PLUS:
            printf("+\n");
            break;
        case MOINS:
            printf("-\n");
            break;
        case FOIS:
            printf("*\n");
            break;
        case DIV:
            printf("/\n");
            break;
        case PUISS:
            printf("^\n");
            break;
        default:
            printf("Inconnu\n");
        }
        break;
    case FONCTION:
        printf("FONCTION: ");
        switch (arbre->jeton.valeur.fonction) {
        case ABS:
            printf("abs\n");
            break;
        case SIN:
            printf("sin\n");
            break;
        case COS:
            printf("cos\n");
            break;
        case TAN:
            printf("tan\n");
            break;
        case EXP:
            printf("exp\n");
            break;
            // Ajoute d'autres fonctions si nécessaire
        default:
            printf("Inconnu\n");
        }
        break;
    case VARIABLE:
        printf("VARIABLE: X \n");
        break;
    default:
        printf("Inconnu\n");
    }

    // Appel récursif pour afficher les sous-arbres
    afficher_arbre(arbre->pjeton_preced);
    afficher_arbre(arbre->pjeton_suiv);
}


