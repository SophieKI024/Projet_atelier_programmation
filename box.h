#pragma once
#include "vector.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

class Box{
public :
    Vector2D pos, v;
    double w, h, omega, angle, m;
    Color Col;
    bool stable, grounded;
    double I();
    void Display();
    void Move();
    void stepBack();
    void Accelerate();
    bool Collide(Box& b);
    Box(Vector2D pos_,double w_,double h_,double m_, Color Col_, double angle_=0, Vector2D v_ = Vector2D(0,0), double omega_=0);
    void Erase();
    Box copy();
    Box();
    bool groundBounce();    // rebond contre le sol
    void corners(double x[4], double y[4]); //position exacte des coins
    void corners(int x[4], int y[4]);       //position arrondie des coins
};
