#pragma once

#include "tools.h"
#include "box.h"

class Structure{
public:
    vector<Box> boxes;

    // Constructeur
    Structure();
    Structure(Box box_);
    Structure(vector<Box> boxes_);

    // Fonctions
    void add(Box box);

    void Display();
    void Erase();
    void Move();
    void Accelerate();
    void AutoCollide();
    void Collide(Structure& S);
    Structure copy();
    void groundBounce();
};
