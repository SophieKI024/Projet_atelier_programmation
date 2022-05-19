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

    Vector2D pos;
    double angle_min;
    double angle_max;
    double reload_time;

    /// instant du dernier tir
    double t0;

    //////////////////////// CONSTRUCTEURS //////////////////////////

    /// Constructeur vide
    Weapon();
    Weapon(Box projectile_);
    Weapon(Skin machine_, double length_, Vector2D pos_, double angle_min_, double angle_max_, double reload_time_);



    /////////////////////// AFFICHAGE //////////////////////////////

    /// Affiche les armes et les boulets
    void Display(Vector2D vehicle_pos);

    /// Efface les armes et les boulets
    void Erase(Vector2D vehicle_pos);


    /////////////////////// GESTIONS INPUTS /////////////////////////

    /// Modifie l'angle de visee en fonction des inputs du joueur
    void angle_machine(vector<int> key);


    ////////////////////// AUTRES /////////////////////////////////

    /// Copie l'arme
    Weapon copy();
};
