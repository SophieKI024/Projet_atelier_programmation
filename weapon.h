#pragma once
#include <Imagine/Graphics.h>

#include "box.h"
#include "tools.h"
#include "skin.h"

/// **** Weapon ****///

class Weapon{
public:
    vector<Box> ammunition;
    Skin machine;
    double length;
    Vector pos;
    // Constructeur
    Weapon();
    Weapon(Box projectile_);
    Weapon(Skin machine_, double length_, Vector pos_);

    // Fonctions
    bool set_fire(int key, Vector vehicle_pos);

    void Display();
    void Erase();
    void Move();
    void Accelerate();
    void Collide(Box& b);
    Weapon copy();
    void groundBounce();
    void stable();
};
