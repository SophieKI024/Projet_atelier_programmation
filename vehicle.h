#pragma once

#include "box.h"
#include "tools.h"
#include "weapon.h"


/// **** Vehicle ****

class Vehicle{
public:
    Box body;
    Weapon* arsenal;
    int nb_weapons;

    // Constructeur
    Vehicle();
    Vehicle(Box body_, int nb_weapons_=0, Weapon* arsenal_ = new Weapon[0]);

    // Fonctions
    void Display();
    void Erase();
    void Move();
    void Accelerate();
    Vehicle copy();
    void groundBounce();
    bool stable();
    void movement_vehicle(vector<int> key);

    void arsenal_collide(Box &b);
    void angle_machine(int key);
    void fire(vector<int> keys);
};
