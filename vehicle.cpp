#include "vehicle.h"
#include "box.h"
#include "liste_des_skins.h"


// ===================== Vehicle ====================================================================================

// Constructeur


Vehicle::Vehicle(int nb_weapons_, Weapon* arsenal_, double acceleration_){
    nb_weapons = nb_weapons_;
    arsenal = new Weapon[nb_weapons_];
    acceleration = acceleration_;
    for (int i = 0; i < nb_weapons; i++){
        arsenal[i]=arsenal_[i];
    }
}

// Fonctions


void Vehicle::Display(Vector2D pos, double angle){;
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Display(pos,angle);
    }
}
void Vehicle::Erase(Vector2D pos, double angle){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Erase(pos,angle);
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

