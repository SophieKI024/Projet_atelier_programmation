#include "vehicle.h"
#include "box.h"
#include "liste_des_skins.h"


// ===================== Vehicle ====================================================================================

// Constructeur


Vehicle::Vehicle(int nb_weapons_, Weapon* arsenal_, double power_, double v_max_){
    nb_weapons = nb_weapons_;
    arsenal = new Weapon[nb_weapons_];
    power = power_;
    v_max = v_max_;
    for (int i = 0; i < nb_weapons; i++){
        arsenal[i]=arsenal_[i];
    }
}

// Fonctions


void Vehicle::Display(Vector2D pos, double angle, double scale, Vector2D scroll){;
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Display(pos,angle,scale,scroll);
    }
}
void Vehicle::Erase(Vector2D pos, double angle, double scale, Vector2D scroll){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Erase(pos,angle,scale,scroll);
    }
}

Vehicle Vehicle::copy(){
    return Vehicle(nb_weapons,arsenal);
}



void Vehicle::angle_machine(vector<int> keys){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].angle_machine(keys);
    }
}

