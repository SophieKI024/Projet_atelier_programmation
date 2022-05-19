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


void Vehicle::Display(Vector2D pos){;
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].machine.Display(arsenal[i].pos + pos);
        arsenal[i].Display(pos);
    }
}
void Vehicle::Erase(Vector2D pos){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].machine.Erase(arsenal[i].pos + pos);
        arsenal[i].Erase(pos);
    }
}


Vehicle Vehicle::copy(){
    return Vehicle(nb_weapons,arsenal);
}

/*
void Vehicle::movement_vehicle(vector<int> keys){
    body.v.x += 0.05*(isPressed(keys,KEY_RIGHT)-isPressed(keys,KEY_LEFT));
    body.v.x = (1-frottements_fluides*dt)*sgn(body.v.x)*max(0.,abs(body.v.x)-body.m*frottements_secs*dt); //frotements fluides
}
*/

void Vehicle::angle_machine(vector<int> keys){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].angle_machine(keys);
    }
}

/*
void Vehicle::fire(vector<int> keys, double t){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].set_fire(keys,body.pos,t);
        arsenal[i].stable(); //Effacer les projectiles stables
    }
}
*/
