#pragma once
#include "vector.h"
#include "ball.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

/// Rectangle
class Box{
public :
    /// Position du centre du disque
    Vector2D pos;
    /// Vitesse
    Vector2D v;
    /// Longueur
    double w;
    /// Hauteur
    double h;
    /// Vitesse angulaire
    double omega;

    double angle;
    /// Masse
    double m;
    /// Couleur
    Color Col;
    /// Booléen indiquant si l'objet est stable
    bool stable;
    /// Booléen indiquant si l'objet subit la gravité
    bool gravity;
    /// Energie nécéssaire pour détruire l'objet
    double breaking_energy;
    /// coefficient de frottement sec
    double friction = 20;

    ///////////////////////////// CONSTRUCTEURS //////////////////////////

    /// Constructeur vide
    Box();

    Box(Vector2D pos_,double w_,double h_,double m_, Color Col_, double angle_=0, Vector2D v_ = Vector2D(0,0), double omega_=0);



    //////////////////////////// AFFICHAGE /////////////////////////////////

    /// Affiche le rectangle
    void Display(double scale, Vector2D scroll);

    /// Efface le rectangle
    void Erase(double scale, Vector2D scroll);



    /////////////////////////// PHYSIQUE //////////////////////////////////////

    /// moment inertiel
    double I();

    /// Applique la vitesse et modifie la position et l'angle
    void Move();

    /// Fonction inverse de Move
    void stepBack();

    /// Applique les forces exterieures sur le rectangle
    void Accelerate();

    /// Renvoie un booleen indiquant s'il y a une collision avec une Box b
    bool Collide(Box& b);

    /// Renvoie un booleen indiquant s'il y a une collision avec une Ball b
    bool Collide(Ball& b);

    /// Applique une force en un point
    void applyForce(Vector2D f, Vector2D p);



    ////////////////////////// AUTRES ///////////////////////////////////

    /// Copie le rectangle
    Box copy();

    /// Renvoie le vecteur de distance minimale entre un point et une Box
    Vector2D minimalDistance(Vector2D p);

    /// Renvoie le point de contact et le vecteur de distance minimale entre 2 Box en collision
    vector<Vector2D> collisionInfos(Box& b);

    /// Renvoie la position exacte des coins du rectangle
    void corners(double x[4], double y[4]);

    /// Renvoie la position arrondie des coins
    void corners(int x[4], int y[4]);

    /// Renvoie la position des coins et du centre de chaque segment
    void cornersExtended(double x[8], double y[8]);
};
