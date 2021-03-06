#pragma once
#include "vector.h"
#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;

/// Disque
class Ball{
public :
    /// Position du centre du disque
    Vector2D pos;
    /// Angle important pour l'affichage
    double angle;
    /// Vitesse
    Vector2D v;
    /// Rayon
    double r;
    /// Vitesse angulaire
    double omega;
    /// Masse
    double m;
    /// Couleur du disque
    Color Col;
    ////// Energie nécéssaire pour détruire l'objet
    double breaking_energy;
    /// gravity = false => pas de poids
    bool gravity;
    /// affichage de la croix
    bool cross = false;
    /// coefficient de frottement sec
    double friction = 150;

    /////////////////////////  CONSTRUCTEURS //////////////////////

    /// Constructeur vide
    Ball();
    Ball(Vector2D pos_, double r_, double rho_, Color Col_, Vector2D v_=Vector2D(0,0), double omega_ = 0., double angle_=0);



    ///////////////////////// AFFICHAGE ///////////////////////////

    /// Affiche le disque
    void Display(double scale, Vector2D scroll);

    /// Efface le disque
    void Erase(double scale, Vector2D scroll);



    //////////////////////// PHYSIQUE ////////////////////////////

    /// Energie pour les chocs avec les ball
    double ballC(Ball b);

    /// Moment inertiel
    double I();

    /// Applique la vitesse et modifie la position et l'angle
    void Move();

    /// Fonction inverse de Move
    void stepBack();

    /// Applique les forces exterieures sur le disque
    void Accelerate();

    /// Renvoie un booleen indiquant s'il y a une collision avec une Ball b
    bool Collide(Ball& b);

    /// Applique la force f au point fp
    void applyForce(Vector2D f, Vector2D p);



    /////////////////////////// AUTRES /////////////////////////

    /// Copie le disque
    Ball copy();
};

