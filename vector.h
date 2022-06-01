#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

struct Vector2D {
    double x, y;

    Vector2D (double x_, double y_){
        x= x_;
        y= y_;
    }

    Vector2D () {
        x = 0; y=0;
    }

    double norme(){
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    double norme2(){
        return pow(x, 2) + pow(y, 2);
    }

    Vector2D operator+ (Vector2D autre) {
        return Vector2D (x + autre.x, y + autre.y);
    }

    void operator += (Vector2D autre) {
        x = x + autre.x;
        y = y + autre.y;
    }

    Vector2D operator- (Vector2D autre) {
        return Vector2D (x - autre.x, y - autre.y);
    }

    void operator -= (Vector2D autre) {
        x = x - autre.x;
        y = y - autre.y;
    }

    Vector2D operator* (double a){
        return Vector2D (x*a, y*a);
    }

    void operator*= (double a){
        x = x*a;
        y = y*a;
    }

    double operator*(Vector2D u){
        return x*u.x+y*u.y;
    }
    Vector2D normalize(){
        if (norme2()==0)
            return Vector2D(0,0);
        return Vector2D(x,y)*(1/norme());
    }
};

Vector2D operator* (double a, Vector2D u);

Vector2D rotation(Vector2D v, double angle);
