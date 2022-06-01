#pragma once
#include <Imagine/Graphics.h>

#include "box.h"
#include "tools.h"
#include "skin.h"


double convert_angle(double angle);

/// **** Weapon **** ///

class Weapon{
public:
    Skin machine;

    /// distance entre le centre de rotation et le bout du canon
    double length;

    double rot_speed;
    double r_ball;
    double m_ball;

    Vector2D pos;
    double angle_min;
    double angle_max;
    double reload_time;
    double fire_speed;

    /// instant du dernier tir
    double t0;

    //////////////////////// CONSTRUCTEURS //////////////////////////

    /// Constructeur vide
    Weapon();
    Weapon(Box projectile_);
    Weapon(Skin machine_, double length_, Vector2D pos_, double angle_min_, double angle_max_, double reload_time_, double fire_speed_ = 1800, double rot_speed_=2, double r_ball_ = 10, double rho=10);



    /////////////////////// AFFICHAGE //////////////////////////////

    /// Affiche les armes et les boulets
    void Display(Vector2D vehicle_pos, double angle);

    /// Efface les armes et les boulets
    void Erase(Vector2D vehicle_pos, double angle);


    /////////////////////// GESTIONS INPUTS /////////////////////////

    /// Modifie l'angle de visee en fonction des inputs du joueur
    void angle_machine(vector<int> key);


    ////////////////////// AUTRES /////////////////////////////////

    /// Copie l'arme
    Weapon copy();
};
