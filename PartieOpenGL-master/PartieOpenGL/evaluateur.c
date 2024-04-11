#include "evaluateur.h"
#include "jeton.h"
	
float Evaluateur(Node* A, float X)
{
	if (A == NULL) {
		return NAN;
	}

	switch (A->jeton.lexem) {
	case REEL:
		return A->jeton.valeur.reel;
		break;
	case VARIABLE:
		return X;
		break;
	case OPERATEUR:
		switch (A->jeton.valeur.operateur) {

		case PLUS:
			return Evaluateur(A->pjeton_preced, X) + Evaluateur(A->pjeton_suiv, X);
			break;
		case MOINS:
			return Evaluateur(A->pjeton_preced, X) - Evaluateur(A->pjeton_suiv, X);
			break;
		case FOIS:
			return Evaluateur(A->pjeton_preced, X) * Evaluateur(A->pjeton_suiv, X);
			break;
		case PUISS:
			return powf(Evaluateur(A->pjeton_preced, X), Evaluateur(A->pjeton_suiv, X));
			break;
		default:
			printf("non");
			return 0;
			break;

		}


	
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






