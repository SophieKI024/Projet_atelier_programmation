#pragma once

#include "box.h"
#include "tools.h"

class Skin{
public:
    Vector2D* border;
    Color Col;
    double angle, scale_factor;
    int nb_points;

    ////////////////////// CONSTRUCTEURS /////////////////////////////////

    /// Constructeur vide
    Skin();
    Skin(Vector2D* border_,int nb_points_, Color Col_,double scale_factor_ =20, double angle_ = 0);




    ////////////////////// AFFICHAGE /////////////////////////////////

    /// Affiche le Skin
    void Display(Vector2D pos, double scale, Vector2D scroll);

    /// Efface le Skin
    void Erase(Vector2D pos, double scale, Vector2D scroll);
};
