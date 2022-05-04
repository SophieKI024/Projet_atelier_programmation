#pragma once
#include "vector.h"
#include <iostream>
using namespace std;
#include <Imagine/Graphics.h>
using namespace Imagine;


class Ball{
public :
    Vector2D pos, v;
    double r, omega, m;
    Color Col;

    Ball();
    Ball(Vector2D pos_,double r_,double m_,Color Col_,Vector2D v_=Vector2D(0,0), double omega_ = 0.);

    double I();
    void Display();
    void Move();
    void stepBack();
    void Accelerate();
    bool Collide(Ball& b);
    void Erase();
    bool groundBounce();    // rebond contre le sol
    Ball copy();
};

