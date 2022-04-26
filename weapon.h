#pragma once
#include <Imagine/Graphics.h>

#include "box.h"
#include "tools.h"
#include "skin.h"


double convert_angle(double angle);

/// **** Weapon **** ///

class Weapon{
public:
    vector<Box> ammunition;
    Skin machine;
    double length;
    Vector pos;
    double angle_min;
    double angle_max;
    // Constructeur
    Weapon();
    Weapon(Box projectile_);
    Weapon(Skin machine_, double length_, Vector pos_, double angle_min_, double angle_max_);

    // Fonctions
    bool set_fire(int key, Vector vehicle_pos);

    void Display(Vector vehicle_pos);
    void Erase(Vector vehicle_pos);
    void Move();
    void Accelerate();
    void Collide(Box& b);
    Weapon copy();
    void groundBounce();
    void stable();

    bool raise(int key);
    bool lower(int key);
    void angle_machine(int key);

};
