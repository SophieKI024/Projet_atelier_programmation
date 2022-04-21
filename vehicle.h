#pragma once

#include "box.h"
#include "tools.h"
#include "weapon.h"

int keyboard();

/// **** Vehicle ****

class Vehicle{
public:
    Box body;
    Weapon* arsenal;

    // Constructeur
    Vehicle();
    Vehicle(Box body_);

    // Fonctions
    void Display();
    void Erase();
    void Move();
    void Accelerate();
    Vehicle copy();
    void groundBounce();
    bool stable();
    bool move_right();
    bool move_left();
    void movement_vehicle();
};

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
