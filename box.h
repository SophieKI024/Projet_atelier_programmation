#pragma once
#include "vector.h"
#include "ball.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

/// Rectangle
class Box{
public :
    Vector2D pos, v;
    double w, h, omega, angle, m;
    Color Col;
    bool stable, grounded;

    ///////////////////////////// CONSTRUCTEURS //////////////////////////

    Box();
    Box(Vector2D pos_,double w_,double h_,double m_, Color Col_, double angle_=0, Vector2D v_ = Vector2D(0,0), double omega_=0);



    //////////////////////////// AFFICHAGE /////////////////////////////////

    /// Affiche le rectangle
    void Display();

    /// Efface le rectangle
    void Erase();



    /////////////////////////// PHYSIQUE //////////////////////////////////////

    /// moment inertiel
    double I();

    /// Applique la vitesse et modifie la position et l'angle
    void Move();

    void stepBack();

    /// Applique les forces exterieures sur le rectangle
    void Accelerate();

    /// Renvoie un booleen indiquant s'il y a une collision avec une Box
    bool Collide(Box& b);

    /// Renvoie un booleen indiquant s'il y a une collision avec une Ball
    bool Collide(Ball& b);

    /// Applique les collisions avec le sol
    bool groundBounce();



    ////////////////////////// AUTRES ///////////////////////////////////

    /// Copie le rectangle
    Box copy();

    /// Renvoie le vecteur de distance minimale entre un point et une Box
    Vector2D minimalDistance(Vector2D p);

    /// Renvoie la position exacte des coins du rectangle
    void corners(double x[4], double y[4]);

    /// Renvoie la position arrondie des coins
    void corners(int x[4], int y[4]);

    /// Renvoie la position des coins et du centre de chaque segment
    void cornersExtended(double x[8], double y[8]);
};
