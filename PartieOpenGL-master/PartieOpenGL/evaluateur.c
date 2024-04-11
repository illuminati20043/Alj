#include "evaluateur.h"
#include "jeton.h"

//evalue la valeur du code grace a de la recursivité

float Evaluateur(Node* A, float X)
{
	//si c'est vide
	if (A == NULL) {
		return NAN;
	}
	//cas ou il y a réel
	switch (A->jeton.lexem) {
	case REEL:
		return A->jeton.valeur.reel;
		break;
	//cas ou il y a variable x
	case VARIABLE:
		return X;
		break;
	//cas opérateur
	case OPERATEUR:
		switch (A->jeton.valeur.operateur) {

		case PLUS:
			if (A->pjeton_suiv == NULL) { printf("Erreur syntaxe"); }
			else { return Evaluateur(A->pjeton_preced, X) + Evaluateur(A->pjeton_suiv, X); }
			break;
		case MOINS:
			if (A->pjeton_suiv == NULL) { printf("Erreur syntaxe");  }
			else { return Evaluateur(A->pjeton_preced, X) - Evaluateur(A->pjeton_suiv, X); }
			break;
		case FOIS:
			if (A->pjeton_suiv == NULL) { printf("Erreur syntaxe"); }
			else { return Evaluateur(A->pjeton_preced, X) *Evaluateur(A->pjeton_suiv, X); }
			break;
		case PUISS:
			return powf(Evaluateur(A->pjeton_preced, X), Evaluateur(A->pjeton_suiv, X));
			break;
		case DIV:
			if (A->pjeton_suiv->jeton.valeur.reel == 0) {
				printf("Erreur syntaxe division par 0");

			}
			else{return Evaluateur(A->pjeton_preced, X) / Evaluateur(A->pjeton_suiv, X);
			}
		default:
			printf("non");
			return 0;
			break;

		}


	//cas fonction
	case FONCTION:
		switch (A->jeton.valeur.fonction) {
		case SIN:
			return sinf(Evaluateur(A->pjeton_suiv, X));
			break;
		case COS:
			return cosf(Evaluateur(A->pjeton_suiv, X));
			break;
		case TAN:
			return tanf(Evaluateur(A->pjeton_suiv, X));
			break;
		case EXP:
			return expf(Evaluateur(A->pjeton_suiv, X));
			break;
		case LOG:
			return logf(Evaluateur(A->pjeton_suiv, X));
			break;
		case ENTIER:
			return floorf(Evaluateur(A->pjeton_suiv, X));
			break;
		case VAL_NEG:
			return (Evaluateur(A->pjeton_suiv, X));
			break;
		default:
			printf("Bad function");
			return 0;

		}

	}




}






