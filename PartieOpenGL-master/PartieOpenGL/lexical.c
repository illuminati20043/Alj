#include "lexical.h"


int lire_jeton(const char* s, typejeton T[]) {
    int jetons = 0;
    int i = 0;
    while (s[i] != 0) {
        switch (s[i]) {
        case '(':
            T[jetons].lexem = PAR_OUV;
            i++;
            jetons++;
            break;
        case ')':
            T[jetons].lexem = PAR_FERM;
            i++;
            jetons++;
            break;
        case '+':
            T[jetons].lexem = OPERATEUR;
            T[jetons].valeur.operateur = PLUS;
            i++;
            jetons++;
            break;
        case '-':
            T[jetons].lexem = OPERATEUR;
            T[jetons].valeur.operateur = MOINS;
            i++;
            jetons++;
            break;
        case '*':
            T[jetons].lexem = OPERATEUR;
            T[jetons].valeur.operateur = FOIS;
            i++;
            jetons++;
            break;
        case '/':
            T[jetons].lexem = OPERATEUR;
            T[jetons].valeur.operateur = DIV;
            i++;
            jetons++;
            break;
        case '^':
            T[jetons].lexem = OPERATEUR;
            T[jetons].valeur.operateur = PUISS;
            i++;
            jetons++;
            break;
        }

        if (isalpha(s[i])) {
            char t[10];
            int j = 0;
            while (isalpha(s[i]) && j < 9) {
                t[j++] = s[i++];
            }
            t[j] = '\0';
            if (strcmp(t, "abs") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = ABS;
            }
            else if (strcmp(t, "exp") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = EXP;
            }
            else if (strcmp(t, "sin") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = SIN;
            }
            else if (strcmp(t, "cos") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = COS;
            }
            else if (strcmp(t, "tan") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = TAN;
            }
            else if (strcmp(t, "entier") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = ENTIER;
            }
            else if (strcmp(t, "val_neg") == 0) {
                T[jetons].lexem = FONCTION;
                T[jetons].valeur.fonction = VAL_NEG;
            }
            else if (strcmp(t, "x") == 0) {
                T[jetons].lexem = VARIABLE;
            }
            jetons++;
        }

        if (isdigit(s[i])) {
            T[jetons].lexem = REEL;
            char t[20];
            int j = 0;
            while (isdigit(s[i]) || s[i] == '.') {
                t[j++] = s[i++];
            }
            t[j] = '\0';
            T[jetons].valeur.reel = atof(t);
            jetons++;
        }

        // Ignorer les espaces
        if (isspace(s[i])) {
            i++;
        }
    }
    return jetons;
}

void afficher_jeton(typejeton jeton[], int nb_jetons) {
	for (int i = 0; i < nb_jetons; i++) {
		switch (jeton[i].lexem) {
		case REEL:
			printf("REEL: %f\n", jeton[i].valeur.reel);
			break;
		case OPERATEUR:
			printf("OPERATEUR: %d\n", jeton[i].valeur.operateur);
			break;
		case FONCTION:
			printf("FONCTION: %d\n", jeton[i].valeur.fonction);
			break;
		case ERREUR:
			printf("ERREUR: %d\n", jeton[i].valeur.erreur);
			break;
		case FIN:
			printf("FIN\n");
			break;
		case PAR_OUV:
			printf("PAR_OUV\n");
			break;
		case PAR_FERM:
			printf("PAR_FERM\n");
			break;
		case VARIABLE:
			printf("VARIABLE: %c\n", jeton[i].valeur.reel);
			break;
		default:
			printf("Type inconnu\n");
			break;
		}
	}
}

