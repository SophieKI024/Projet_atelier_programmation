#pragma once

#include "box.h"
#include "tools.h"
#include "weapon.h"
#include "vehicle.h"

class Skin{
public:
    Vector* border;
    Color Col;
    double angle, scale_factor;
    Vector pos;
    int nb_points;
    Skin();
    Skin(Vector* border_,int nb_points_, Color Col_, Vector pos_,double scale_factor_ =20, double angle_ = 0);
    void Display();
    void Erase();
};
