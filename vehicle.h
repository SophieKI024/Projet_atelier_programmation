#pragma once

#include "box.h"
#include "tools.h"

/// **** Weapon ****

class Weapon{
public:
    Box* projectile;

    // Fonctions
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
};
