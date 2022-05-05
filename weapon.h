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



    ////////////////////// PHYSIQUE /////////////////////////////////

    /// Applique les vitesses aux boulets pour les deplacer
    void Move();

    /// Applique les forces exterieures sur les boulets et modifie la vitesse
    void Accelerate();

    /// Effectue les collisions entre les boulets et une Box
    void Collide(Box& b);

    /// Effectue les collisions entre les boulets et le sol
    void groundBounce();

    /// Efface les boulets stables
    void stable();



    /////////////////////// GESTIONS INPUTS /////////////////////////

    /// Effectue un tir en fonction des inputs du joueur
    bool set_fire(vector<int> key, Vector2D vehicle_pos, double t);

    /// Modifie l'angle de visee en fonction des inputs du joueur
    void angle_machine(vector<int> key);


    ////////////////////// AUTRES /////////////////////////////////

    /// Copie l'arme
    Weapon copy();
};
