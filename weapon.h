#pragma once

#include "box.h"
#include "tools.h"

/// **** Weapon ****

class Weapon{
public:
    vector<Box> ammunition;

    // Constructeur
    Weapon();
    Weapon(Box projectile_);

    // Fonctions
    bool set_fire(int key);

    void Display();
    void Erase();
    void Move();
    void Accelerate();
    void Collide(Box& b);
    Weapon copy();
    void groundBounce();
    void stable();
};
