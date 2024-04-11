/**************************
   * Includes
   *
   **************************/
#include <windows.h>
#include <math.h>
#include<string.h>

#include "graph.h"
#include "glut.h"
#include"evaluateur.h"
#include "syntaxique.h"
#include "lexical.h"

//using namespace std;
float func[5000][2];
//les variables ci dessus permettent de cadrer l'interface graphique et de créer des effets d'homothétie 
float xmin = -20;
float xmax = 20;
float ymin = -20;
float ymax = 20;
float a = 1.5; //coefficient d'homothétie
float b = 1;
float r = 0;
float t; // = 4 * ymax - a * 3.6;
float pas = 1.0;
/**
* myKey
*
* Gestion des touches du clavier
*
* @parma c code ascci definissant une touche du clavier
*
*/
void myKey(int c)
{

    switch (c)
    {
    case '+':
        xmin = xmin / a;
        ymin = ymin / a;
        ymax = ymax / a;
        xmax = xmax / a;/* La bascule passe alternativement de 0 a 1 */
        t /= a;
        b /= a;
        break;
    case '-':
        xmin *= a;
        xmax *= a;
        ymin *= a;
        ymax *= a;
        t *= 1.25;
        b *= a;
        break;
    case '6':
        xmin += b * 0.4;
        xmax += b * 0.4;
        r += a * 1.6;
        break;
    case '4':
        xmin -= b * 0.4;
        xmax -= b * 0.4;
        r -= a * 1.6;

        break;
    case '8':
        ymin += b * 0.4;
        ymax += b * 0.4;
        t += 1.6 * a;

        break;
    case '5':
        ymin -= b * 0.4;
        ymax -= b * 0.4;
        t -= 1.6 * a;
        break;



    }
}


/**
* myDraw
*
* Procédure
*
*/
static void Begin2DDisplay(void)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(xmin, xmax, ymin, ymax, 0.5, 1.5);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.0F, 0.0F, -1.0F);
}

void myDraw(void)
{

    Begin2DDisplay();
    /* trace l'axe*/
    setcolor(0.0F, 0.0F, 0.0F);
    line(0, ymin, 0, ymax);
    setcolor(0.0F, 0.0F, 0.0F);
    line(xmin, 0, xmax, 0);


    /*tracer graduations*/
    if ((xmax - xmin) < 50)
    {
        pas = 1;

    }
    else if ((xmax - xmin) < 170) { pas = 10; }
    else if (xmax < 200) { pas = 100; }
    else { pas = 200; }
    float mm = round(xmin / pas) * pas;
    int count = mm;
    while (mm < xmax) {
        if (mm != 0) {
            setcolor(0.8F, 0.8F, 0.8F);
            line(mm, ymin, mm, ymax);
            setcolor(0.0F, 0.0F, 0.0F);
            if (b < 1) {
                line(mm, -pas * b / 3, mm, pas * b / 3);


            }
            if (b > 1) {
                line(mm, -pas / b / 3, mm, pas / b / 3);
            }



        }
        char str[10];
        sprintf(str, "%d", count); 

        if (mm != 0) { outtextxy(mm, pas / 3, str); };
        count += pas;
        mm += pas;
    }
    float nn = round(ymin / pas) * pas;
    count = nn;
    while (nn < ymax) {
        if (nn != 0) {
            setcolor(0.8F, 0.8F, 0.8F);
            line(xmin, nn, xmax, nn);
            setcolor(0.0F, 0.0F, 0.0F);
            if (b > 1) {
                line(-pas / b / 3, nn, pas / b / 3, nn);
            }
            else {
                line(-pas * b / 3, nn, pas * b / 3, nn);
            }

        }
        char str[10];
        sprintf(str, "%d", count);
        outtextxy(pas / 3, nn, str);
        count += pas;
        int arrondi = floor(abs(xmax));
        nn += pas;


    }
    /*flèche*/
    setcolor(0.0F, 0.0F, 0.0F);
    line(xmax, 0, xmax - b, -b);
    line(xmax, 0, xmax - b, b);
    line(0, ymax, -b, (ymax - b));
    line(0, ymax, b, (ymax - b));

    /*tracer courbe*/
    int k = 1;

    while (func[k][0] != '\0'){
        setcolor(1.0F, 0.0F, 0.0F);
        line(func[k - 1][0], func[k - 1][1], func[k][0], func[k][1]);
        k++;
        
    }

            
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
int main(int ac, char* av[]){

    t = 4 * ymax - a * 3.6;
    
    
    float step;
    float x_min;
    float x_max;
    int nb_echantillon;

    printf("Choississez votre x minimum : ");
    scanf("%f", &x_min);
    printf("Choississez votre x maximum : ");
    scanf("%f", &x_max);
    printf("Choississez le pas : ");
    scanf("%f", &step);
    


    //génération du tableau qui permettra de dessiner la fonction
   
   
    typeerreur erreur = OK; //Dernière erreur detectée
    char fonction[200]; // Allouer de la mémoire pour stocker la chaîne de caractères
  
    printf("Enter an equation: \n");
    scanf("%s", fonction);  
    typejeton jeton[200]; // Tableau pour stocker les jetons
  
    int nb_jetons = lire_jeton(fonction, jeton, &erreur);
    afficher_jeton(jeton, nb_jetons);
    
    Node* arbre = arbre_binaire(jeton, nb_jetons);
    afficher_arbre(arbre);
    float aljmin = x_min;
    int i = 0;
    while (aljmin <= x_max) {
        func[i][0] = aljmin;
        func[i][1] = Evaluateur(arbre, aljmin);
        printf("%f \n", func[i][0]);
        printf("%f \n", func[i][1]);
        aljmin += step;
        i++;

    }
    

   InitGraph(ac, av, "Graphic Output", 640, 480, myDraw, myKey);
    return 0;
}
