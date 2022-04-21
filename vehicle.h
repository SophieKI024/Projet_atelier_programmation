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
    bool set_fire();
    void fire();
};


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
