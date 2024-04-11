#ifndef EVALUATEUR_H
#define EVALUATUEUR_H
#include "jeton.h"

float Evaluateur(Node* A, float x);

float* Eval_Arbre_Range_x(struct Node* Arbre, float x_min, float x_max, int n);

float* Eval_Arbre_Range_y(struct Node* Arbre, float x_min, float x_max, int n);





#endif
