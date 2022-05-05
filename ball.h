#pragma once
#include "vector.h"
#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

/// Disque
class Ball{
public :
    Vector2D pos, v;
    double r, omega, m;
    Color Col;

    /////////////////////////  CONSTRUCTEURS //////////////////////

    /// Constructeur vide
    Ball();
    Ball(Vector2D pos_,double r_,double rho_,Color Col_,Vector2D v_=Vector2D(0,0), double omega_ = 0.);



    ///////////////////////// AFFICHAGE ///////////////////////////

    /// Affiche le disque
    void Display();

    /// Efface le disque
    void Erase();



    //////////////////////// PHYSIQUE ////////////////////////////

    /// Energie pour les chocs avec les ball
    double ballC(Ball b);

    /// Moment inertiel
    double I();

    /// Applique la vitesse et modifie la position et l'angle
    void Move();

    void stepBack();

    /// Applique les forces exterieures sur le disque
    void Accelerate();

    /// Teste les collisions avec un autre disque
    bool Collide(Ball& b);

    /// Applique les rebonds avec le sol
    bool groundBounce();



    /////////////////////////// AUTRES /////////////////////////

    /// Copie le disque
    Ball copy();
};

