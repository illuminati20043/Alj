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
float pas_graduation = (taille_ecran * 2) / 10; // Variable permettant de savoir la distance en pixel entre deux graduations
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
int keyUp = 0;
int keyDown = 0;
int keyLeft = 0;
int keyRight = 0;
int clickDown = 0;
int pos_x = 0;
int pos_y = 0;
char fonction[200];
int chgt_fonction = 0;

void ProcessSpecialKeys(unsigned char key, int x, int y){
    // "key" est un caractère correspondant à l'appui d'une des flèches directionnelles
    switch (key) {
        case 'e': // Flèche du haut
            keyUp = 1;
            break;
        case 'd': // Flèche de gauche
            keyLeft = 1;
            break;
        case 'g': // Flèche du bas
            keyDown = 1;
            break;
        case 'f': // Flèche de droite
            keyRight = 1;
            break;
    }
}

void ProcessMouseClick(int button, int state, int x, int y) {
    if (state == 1) { // Si le bouton de la souris est enfoncé
        switch (button) {
            case 0: // Si c'est le clic gauche
                clickDown = 1;
                pos_x = x/2;
                pos_y = y;
                break;
        }
    }
}

/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
**/

void myKey(int c)
{
    /*
    switch (c)
    {
    case 'a':
        bascule ^= 1;  La bascule passe alternativement de 0 a 1 
        break;
    }
*/
    printf("%c", c);
}


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
    // Les chaines de caractères value_grad_x et value_grad_y servent à contenir les valeurs des graduations
    char value_grad_x[100];
    char value_grad_y[100];
    for (int i = 0; i < 10; i++) {
        // Traçage des lignes gris clair
        glColor4f(0.8F, 0.8F, 0.8F, 0.8F);
        line(-taille_ecran + pas_graduation * i, -taille_ecran, -600 + pas_graduation * i, taille_ecran);
        line(-taille_ecran, -taille_ecran + pas_graduation * i, taille_ecran, -600 + pas_graduation * i);

        // Traçage des petits traits pour les graduations
        glColor4f(0.0F, 0.0F, 0.0F, 0.0F);
        line(- taille_ecran + pas_graduation * i, pos_axe_largeur - 10, -600 + pas_graduation * i, pos_axe_largeur + 10);
        line(pos_axe_hauteur - 5, - taille_ecran + pas_graduation * i, pos_axe_hauteur + 5, -600 + pas_graduation * i);

        // Affichage des valeurs des graduations suivant x
        if ((xmin + (10 * pas) * i) == 0.0) {
            sprintf(&value_grad_x, "");
        }
        else {
            sprintf(&value_grad_x, "%.2f", (xmin + ((xmax-xmin)/10 * i)));
        }
        outtextxy(pas_graduation * i - 15 - taille_ecran, pos_axe_largeur - 50, value_grad_x);

        // Affichage des valeurs des graduations suivant y
        if ((ymin + (10 * pas) * i) == 0.0) {
            sprintf(&value_grad_y, "");
        }
        else {
            sprintf(&value_grad_y, "%0.2f", (ymin + ((ymax - ymin) / 10 * i)));
        }
        outtextxy(pos_axe_hauteur - 30, pas_graduation * i - 5 - taille_ecran, value_grad_y);
        outtextxy(pos_axe_hauteur - 30, pos_axe_largeur - 25, "0.00");
    }
}

void affichage_fonction(float xy[2][1001]) {
    // Les variables scale_x et scale_y correspondent à la taille d'une unité en pixel
    float scale_x = (float)2 * taille_ecran / abs(xmax - xmin);
    float scale_y = (float)2 * taille_ecran / abs(ymax - ymin);

    // Les variables offset_x et offset_y permettent de décaler la fonction pour la déplacer vers les axes
    float offset_x = (float)(xmin + xmax) / 2 * scale_x;
    float offset_y = (float)(ymin + ymax) / 2 * scale_y;

    // On itère sur tous les points de la fonction
    for (int i = 1; i < nbValues + 1; i++) {
        // On calcule les coordonnées des deux points de la ligne
        int xi1 = (int)((xy[0][i - 1]) * scale_x) - offset_x;
        int xi2 = (int)((xy[0][i]) * scale_x) - offset_x;
        int yi1 = (int)((xy[1][i - 1]) * scale_y) - offset_y;
        int yi2 = (int)((xy[1][i]) * scale_y) - offset_y;

        // On trace la droite entre les deux points
        setcolor(1.0F, 0.0F, 0.0F);
        line(xi1, yi1, xi2, yi2);
    }
}


/**
* myDraw
*
* Procédure
*
*/

void myDraw(){
    // On créé un rectangle blanc sur tout l'écran
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-taille_ecran, -taille_ecran, taille_ecran, taille_ecran);

    // On calcule le décalage en x et en y. Ce dernier correspondant à un dixième de la distance entre les extrèmes
    float decalage_x = (xmax - xmin) / 10;
    float decalage_y = (ymax - ymin) / 10;

    // On effectue diverses actions suivant les flèches appuyées
    if (keyUp) {
        ymin += decalage_y;
        ymax += decalage_y;
        keyUp = 0;
    } 
    if (keyDown) {
        ymin -= decalage_y;
        ymax -= decalage_y;
        keyDown = 0;
    } 
    if (keyLeft) {
        xmin -= decalage_x;
        xmax -= decalage_x;
        keyLeft = 0;
    } 
    if (keyRight) {
        xmin += decalage_x;
        xmax += decalage_x;
        keyRight = 0;
    }

    // Si le clic de la souris est enfoncé, on regarde ses coordonnées et on effectue diverses actions suivant ces dernières
    if (clickDown) {
        //printf("%d | %d\n", pos_x, pos_y);
        if ((6 <= pos_x && pos_x <= 36) && (13 <= pos_y && pos_y <= 36)) {
            xmin += decalage_x;
            xmax -= decalage_x;
            ymin += decalage_y;
            ymax -= decalage_y;
        }
        else if ((6 <= pos_x && pos_x <= 36) && (51 <= pos_y && pos_y <= 74)) {
            xmin -= decalage_x;
            xmax += decalage_x;
            ymin -= decalage_y;
            ymax += decalage_y;
        }
        else if ((6 <= pos_x && pos_x <= 49) && (563 <= pos_y && pos_y <= 585)) {
            chgt_fonction = 1;
            while (chgt_fonction) {
                printf("Veuillez entrer votre fonction : ");
                scanf("%s", &fonction);
                chgt_fonction = 0;
            }
            printf("Vous avez entrer la fonction suivante : %s\n", fonction);
        }
        clickDown = 0;
    }

    // On calcule le pas entre 2 valeurs de x
    pas = (xmax - xmin) / ((float)nbValues);

    // Test avec une fonction sinus
    float xy[2][1001];
    for (int i = 0; i < nbValues + 1; i++) {
        xy[0][i] = xmin + pas * i;
        xy[1][i] = 10*sin(xy[0][i]);
        //printf("\nx : %f | y : %f", xy[0][i], xy[1][i]);
    }

    // On calcule la position des axes
    float pas_unite_x = (taille_ecran * 2) / (xmax - xmin);
    float pas_unite_y = (taille_ecran * 2) / (ymax - ymin);
    pos_axe_hauteur = - xmin * pas_unite_x - 600;
    pos_axe_largeur = - ymin * pas_unite_y - 600;

    // On trace la graduation et les lignes des axes
    graduation();
    glColor4f(0.0F, 0.0F, 0.0F, 0.0F);
    line(-taille_ecran, pos_axe_largeur, taille_ecran, pos_axe_largeur);
    line(pos_axe_hauteur, -taille_ecran, pos_axe_hauteur, taille_ecran);

    // Rectangle servant à zoomer
    setcolor(0.0F, 0.0F, 0.0F);
    bar(-590, 575, -525, 525);
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-588, 573, -527, 527);

    // Affichage du texte : "ZOOM"
    setcolor(0.0F, 0.0F, 0.0F);
    outtextxy(-573, 543, "ZOOM");

    // Rectangle servant à dé-zoomer
    setcolor(0.0F, 0.0F, 0.0F);
    bar(-590, 500, -525, 450);
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-588, 498, -527, 452);

    // Affichage du texte : "DEZOOM"
    setcolor(0.0F, 0.0F, 0.0F);
    outtextxy(-580, 468, "DEZOOM");

    // Rectangle servant à changer de fonctions
    setcolor(0.0F, 0.0F, 0.0F);
    bar(-590, -575, -500, -525);
    setcolor(1.0F, 1.0F, 1.0F);
    bar(-588, -573, -502, -527);

    // Affichage du texte : "Changer Fonction"
    setcolor(0.0F, 0.0F, 0.0F);
    outtextxy(-580, -550, "Changer Fonction");

    // On trace la fonction
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

int main(int ac,char *av[])
{
    def_vars(); // On appelle une fonction permettant de demander à l'utilisateur diverses valeurs
    printf("Vous avez choisi : xmin = %f, xmax = %f, ymin = %f, ymax = %f, nb_valeurs = %d et pas = %f", xmin, xmax, ymin, ymax, nbValues, pas);
    InitGraph(ac, av, "Calculateur Graphique", window_width, window_height, myDraw, myKey, ProcessSpecialKeys, ProcessMouseClick);
    return 0;
}


