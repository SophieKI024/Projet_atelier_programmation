#pragma once
#include "vector.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Box{
public :
    Vector pos, v;
    double w, h, omega, angle, m;
    Color Col;
    void Display(bool erase=false);
    void Move();
    void Accelerate();
    void Collide(Box b);
    Box(Vector pos_,double w_,double h_,double m_, Color Col_, double angle_=0, Vector v_ = Vector(0,0), double omega_=0);
    void Erase();
    Box copy();
    Box();
    void groundBounce();
    void corners(int x[4], int y[4]);
};
