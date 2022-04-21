#pragma once

#include "box.h"
#include "tools.h"

class Skin{
public:
    Vector* border;
    Color Col;
    double angle, scale_factor;
    int nb_points;
    Skin();
    Skin(Vector* border_,int nb_points_, Color Col_,double scale_factor_ =20, double angle_ = 0);
    void Display(Vector pos);
    void Erase(Vector pos);
};
