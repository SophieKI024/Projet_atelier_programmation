#pragma once
#include "vector.h"

class Joint{
public:
    int type_a, type_b, a, b;
    double l;
    int e;
    Color Col;

    Joint();
    Joint(int type_a_, int a_, int type_b_, int b_, double l_, int e_, Color Col_);

    void Display(Vector2D pos1, Vector2D pos2);
    void Erase(Vector2D pos1, Vector2D pos2);
    double C(Vector2D pos1, Vector2D pos2);
    Vector2D J(Vector2D pos1, Vector2D pos2);
    Vector2D solveConstraint();
    Joint copy();
};

class Spring{
public:
    int type_a, type_b, a,b;
    double lmin,lmax,l0, k, e0;
    Color Col;

    Spring();
    Spring(int type_a_, int a_, int type_b_, int b_, double l0_, double lmin_, double lmax_, double k_, double e0_, Color Col_);
    void Display(Vector2D pos1, Vector2D pos2);
    void Erase(Vector2D pos1, Vector2D pos2);
};
