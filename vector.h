#ifndef VECTOR_H
#define VECTOR_H

#endif // VECTOR_H
#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;

struct Vecteur {
    double x, y;

    Vecteur (double x_, double y_){
        x= x_;
        y= y_;
    }

    Vecteur () {
        x = 0; y=0;
    }

    double norme(){
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    double norme2(){
        return pow(x, 2) + pow(y, 2);
    }

    Vecteur operator+ (Vecteur autre) {
        return Vecteur (x + autre.x, y + autre.y);
    }

    void operator += (Vecteur autre) {
        x = x + autre.x;
        y = y + autre.y;
    }

    Vecteur operator- (Vecteur autre) {
        return Vecteur (x - autre.x, y - autre.y);
    }

    void operator -= (Vecteur autre) {
        x = x - autre.x;
        y = y - autre.y;
    }

    Vecteur operator* (double a){
        return Vecteur (x*a, y*a);
    }

    void operator*= (double a){
        x = x*a;
        y = y*a;
    }
};

Vecteur operator* (double a, Vecteur u);
