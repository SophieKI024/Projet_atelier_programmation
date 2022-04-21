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
