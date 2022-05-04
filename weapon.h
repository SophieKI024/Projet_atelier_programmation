#pragma once
#include <Imagine/Graphics.h>

#include "box.h"
#include "tools.h"
#include "skin.h"


double convert_angle(double angle);

/// **** Weapon **** ///

class Weapon{
public:
    vector<Box> ammunition;
    Skin machine;
    double length;
    Vector2D pos;
    double angle_min;
    double angle_max;
    double reload_time;
    double t0;
    // Constructeur
    Weapon();
    Weapon(Box projectile_);
    Weapon(Skin machine_, double length_, Vector2D pos_, double angle_min_, double angle_max_, double reload_time_);

    // Fonctions
    bool set_fire(vector<int> key, Vector2D vehicle_pos, double t);

    void Display(Vector2D vehicle_pos);
    void Erase(Vector2D vehicle_pos);
    void Move();
    void Accelerate();
    void Collide(Box& b);
    Weapon copy();
    void groundBounce();
    void stable();

    bool raise(int key);
    bool lower(int key);
    void angle_machine(vector<int> key);

};
