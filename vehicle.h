#pragma once

#include "box.h"
#include "tools.h"
#include "weapon.h"
#include "structure.h"

//////////////////////// *** VEHICLE *** //////////////////////////////////

/// Permet de gerer le vehicule du joueur
class Vehicle{
public:
    Box body;
    Weapon* arsenal;
    int nb_weapons;

    //////////////////// CONSTRUCTEURS //////////////////////////////////////

    /// Constructeur vide
    Vehicle();
    Vehicle(Box body_, int nb_weapons_=0, Weapon* arsenal_ = new Weapon[0]);

    //////////////////// AFFICHAGE /////////////////////////////////////////

    /// Affiche le vehicule
    void Display();

    /// Efface le vehicule
    void Erase();

    //////////////////// PHYSIQUE //////////////////////////////////////////

    /// Applique les vitesses au vehicule et aux armes
    void Move();

    /// Applique les forces exterieures et modifie la vitesse du vehicule
    void Accelerate();

    /// Applique les collisions avec le sol
    void groundBounce();

    /// Applique les collisions entre l'arsenal et la structure S
    void arsenal_collide(Structure &S);

    /// Teste la stabilite du body
    bool stable();

    ///////////////////////// GESTIONS INPUTS ///////////////////////////////

    /// Gere le deplacement du vehicule en fonction des inputs du joueur
    void movement_vehicle(vector<int> key);

    /// Gere l'angle des canons en fonction des inputs du joueur
    void angle_machine(vector<int> keys);

    /// Gere le declenchement des armes en fonction des inputs du joueur
    void fire(vector<int> keys, double t);


    ///////////////////////////// AUTRE //////////////////////////////////////

    /// Copie du vehicule avec de la memoire toute fraiche !
    Vehicle copy();
};
