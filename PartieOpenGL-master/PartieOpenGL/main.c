/**************************
 * Includes
 *
 **************************/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "graph.h"
#include "glut.h"

int window_width = 1200;
int window_height = 600;
float xmin = -5;
float xmax = 5;
float ymin = -5;
float ymax = 5;
int nbValues = 100;
float pos_axe_hauteur;
float pos_axe_largeur;
float pas;
int xi1 = 0;
int xi2 = 0;
int yi1 = 0;
int yi2 = 0;

/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
*/

/**
* myDraw
*
* Procédure
*
*/


/**
* main
*
* La fonction principale avec deux arguments permettant de récupérer les éléments en ligne de comment.
*
* Dans  cet  exemple  les  fonctions  (dites  callback)  myDraw  et  myKey  sont  installées  ici  par
* l'appel  InitGraph  en  tant  que fonctions  réagissantes  aux  évènements  de  "re-dessinage"  (pour  myDraw)
* et  aux  évènements  d'appui  sur  une  touche  du
* clavier (myKey).
µ
* @parma ac : nombre de parametres
* @parma av : tableau contenant les parametres
*
*/

void graduation() {
    float pas_graduation = (taille_ecran * 2) / 10;
    char value_grad_x[100];
    char value_grad_y[100];
    setcolor(0.0F, 0.0F, 0.0F);
    for (int i = 0; i < 10; i++) {
        line(-taille_ecran + pas_graduation * i, pos_axe_largeur - 10, -600 + pas_graduation * i, pos_axe_largeur + 10);
        line(pos_axe_hauteur - 5, -taille_ecran + pas_graduation * i, pos_axe_hauteur + 5, -600 + pas_graduation * i);
        if ((xmin + (10 * pas) * i) == 0.0) {
            sprintf(&value_grad_x, "");

        }
        else {
            sprintf(&value_grad_x, "%.2f", (xmin + ((xmax - xmin) / 10 * i)));
        }
        printf("\n%f, %d, %f, %f", (xmin + ((xmax - xmin) / 10 * i)), i, xmin, ((xmax - xmin) / 10 * i));
        //printf("%f\n", (xmin + (5 * pas)*i));
        // settextstyle(0, 0, 5);
        outtextxy(pas_graduation * i - 15 - taille_ecran, pos_axe_largeur - 50, value_grad_x);

        if ((ymin + (10 * pas) * i) == 0.0) {
            sprintf(&value_grad_y, "");
        }
        else {
            sprintf(&value_grad_y, "%0.2f", (ymin + ((ymax - ymin) / 10 * i)));
        }
        //printf("%f\n", (xmin + (5 * pas) * i));
        //settextstyle(0, 0, 5);
        //printf("%s\n", value_grad_y);
        outtextxy(pos_axe_hauteur - 30, pas_graduation * i - 5 - taille_ecran, value_grad_y);
        outtextxy(pos_axe_hauteur - 30, pos_axe_largeur - 25, "0.00");
    }
}

void affichage_fonction(float xy[2][1000]) {
    // Rajouter le décalage si les axes sont pas centrés
    for (int i = 1; i < nbValues; i++) {
        xi1 = (int)((xy[0][i - 1]) * taille_ecran / abs(xmin));
        xi2 = (int)((xy[0][i]) * taille_ecran / abs(ymin));
        yi1 = (int)((xy[1][i - 1]) * taille_ecran / abs(xmax));
        yi2 = (int)((xy[1][i]) * taille_ecran / abs(ymax));
        setcolor(0.0F, 0.0F, 0.0F);
        line(xi1, yi1, xi2, yi2);
        printf("\n%f | %d | %d", xy[0][i - 1]);
        printf("\n%d : %d | %d | %d | %d", i, xi1, yi1, xi2, yi2);
        //line(i, i*i, (i+1), (i+1)* (i + 1));
    }
    /*
    line(-600, 115, -588, 117);
    line(-588, 117, -576, 119);
    line(-576, 119, -564, 119);
    */
}

void myDraw() {

    float xy[2][1000];
    for (int i = 0; i < nbValues; i++) {
        xy[0][i] = xmin + pas * i;
        xy[1][i] = sin(xy[0][i]);
        //printf("\nx : %f | y : %f", xy[0][i], xy[1][i]);
    }

    float pas_unite_x = (taille_ecran * 2) / (xmax - xmin);
    float pas_unite_y = (taille_ecran * 2) / (ymax - ymin);
    pos_axe_hauteur = -xmin * pas_unite_x - 600;
    pos_axe_largeur = -ymin * pas_unite_y - 600;
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-taille_ecran, -taille_ecran, taille_ecran, taille_ecran);

    setcolor(0.0F, 0.0F, 0.0F);
    line(-taille_ecran, pos_axe_largeur, taille_ecran, pos_axe_largeur);
    line(pos_axe_hauteur, -taille_ecran, pos_axe_hauteur, taille_ecran);

    graduation();
    affichage_fonction(xy);
}

void def_vars() {
    printf("Veuillez entre la valeur minimale de l'axe des abscisses : ");
    scanf("%f", &xmin);
    printf("\n");
    printf("Veuillez entre la valeur maximale de l'axe des abscisses : ");
    scanf("%f", &xmax);
    printf("\n");
    printf("Veuillez entre la valeur minimale de l'axe des ordonnées : ");
    scanf("%f", &ymin);
    printf("\n");
    printf("Veuillez entre la valeur maximale de l'axe des ordonnées : ");
    scanf("%f", &ymax);
    printf("\n");
    printf("Veuillez entre le nombre de valeurs : ");
    scanf("%d", &nbValues);
    pas = (xmax - xmin) / ((float)nbValues);
}

int main(int ac, char* av[])
{
    def_vars();
    printf("Vous avez choisi : xmin = %d, xmax = %d, ymin = %d, ymax = %d, nb_valeurs = %d et pas = %f", xmin, xmax, ymin, ymax, nbValues, pas);
    InitGraph(ac, av, "Calculateur Graphique", window_width, window_height, myDraw);
    return 0;
}


