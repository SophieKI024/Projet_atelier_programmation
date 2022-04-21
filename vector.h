#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

struct Vector {
    double x, y;

    Vector (double x_, double y_){
        x= x_;
        y= y_;
    }

    Vector () {
        x = 0; y=0;
    }

    double norme(){
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    double norme2(){
        return pow(x, 2) + pow(y, 2);
    }

    Vector operator+ (Vector autre) {
        return Vector (x + autre.x, y + autre.y);
    }

    void operator += (Vector autre) {
        x = x + autre.x;
        y = y + autre.y;
    }

    Vector operator- (Vector autre) {
        return Vector (x - autre.x, y - autre.y);
    }

    void operator -= (Vector autre) {
        x = x - autre.x;
        y = y - autre.y;
    }

    Vector operator* (double a){
        return Vector (x*a, y*a);
    }

    void operator*= (double a){
        x = x*a;
        y = y*a;
    }

    double operator*(Vector u){
        return x*u.x+y*u.y;
    }
};

Vector operator* (double a, Vector u);
