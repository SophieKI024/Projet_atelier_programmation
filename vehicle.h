#pragma once

#include "box.h"
#include "tools.h"
#include "weapon.h"

//////////////////////// *** VEHICLE *** //////////////////////////////////

/// Permet de gerer le vehicule du joueur
class Vehicle{
public:
    Weapon* arsenal;
    int nb_weapons;
    double power, v_max;
    vector<int> i_wheels;

    //////////////////// CONSTRUCTEURS //////////////////////////////////////

    /// Constructeur
    Vehicle(int nb_weapons_=0, Weapon* arsenal_ = new Weapon[0], double power_ = 1200, double v_max_ = 700);

    //////////////////// AFFICHAGE /////////////////////////////////////////

    /// Affiche le vehicule
    void Display(Vector2D pos, double angle, double scale, Vector2D scroll);

    /// Efface le vehicule
    void Erase(Vector2D pos, double angle, double scale, Vector2D scroll);


    ///////////////////////// GESTIONS INPUTS ///////////////////////////////

    /// Gere l'angle des canons en fonction des inputs du joueur
    void angle_machine(vector<int> keys);

    ///////////////////////////// AUTRE //////////////////////////////////////

    /// Copie du vehicule avec de la memoire toute fraiche !
    Vehicle copy();
};
