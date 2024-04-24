#ifndef JETON_H
#define JETON_H
//énumération des différents types de lexems existants
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TAILLE_TAB_JETONS 200
typedef enum {
	REEL,
	OPERATEUR,
	FONCTION,
	ERREUR,
	FIN,
	PAR_OUV,
	PAR_FERM,
	VARIABLE,
	ABSOLU
} typelexem;
//énumération des différents types d'opérateurs existants
typedef enum { PLUS, MOINS, FOIS, DIV, PUISS } typeoperateur;

//énumération des différents types de fonctions éxistantes
typedef enum {
	SIN, COS, ABS, SQRT, LOG, TAN, EXP, ENTIER, VAL_NEG, PUIS
} typefonction;
//énumération des différents types d'erreurs éxistantes
typedef enum { OK, CHAR_INCONNU, REEL_INVALID, CHAR_INVALID } typeerreur;

//Ã©numÃ©ration des diffÃ©rents types d'erreurs
typedef enum {
	AUCUNE,
	ERREUR_ABS_SIGNE_FOIS,
	ERREUR_OPERATEUR,
	ERREUR_PARENTHESES,
	ERREUR_FCT_SANS_PARAM,
	ERREUR_TROP_CARACT_FANT,
	ERREUR_MALLOC,
	ERREUR_FCT_INCO,
	ERREUR_OPE_INCO,
	ERREUR_JETON_INCO,


}TypeErreur;

//énumération des différents types de valeurs éxistantes
typedef union {
	float reel;
	typefonction fonction;
	typeoperateur operateur;
	typeerreur erreur;
} typevaleur;
//énumération des différents types de jetons éxistants
typedef struct {
	typelexem lexem;
	typevaleur valeur;
} typejeton;
// déclaration de l'arbre
typedef struct Node {
	typejeton jeton;
	struct Node* pjeton_preced;
	struct Node* pjeton_suiv;
} Node;
typedef Node* Arbre;

#endif
