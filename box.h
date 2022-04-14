#pragma once
#include "vector.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Box{
public :
    Vector pos, v;
    double w, h, rot, angle, m;
    Color Col;
    void Display();
    void Move();
    void Accelerate();
    void Collide(Box b);
    Box(Vector pos_,double w_,double h_,double m_, Color Col_, double angle_=0);
    void Erase();
};
