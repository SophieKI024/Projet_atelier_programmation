#pragma once

#include "box.h"
#include "tools.h"

class Skin{
public:
    Vector2D* border;
    Color Col;
    double angle, scale_factor;
    int nb_points;
    Skin();
    Skin(Vector2D* border_,int nb_points_, Color Col_,double scale_factor_ =20, double angle_ = 0);
    void Display(Vector2D pos);
    void Erase(Vector2D pos);
};
