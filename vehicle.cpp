#include "vehicle.h"
#include "box.h"
#include "liste_des_skins.h"


// ===================== Vehicle ====================================================================================

// Constructeur


Vehicle::Vehicle(Box body_, int nb_weapons_, Weapon* arsenal_){
    body = body_.copy();
    nb_weapons = nb_weapons_;
    arsenal = new Weapon[nb_weapons_];
    for (int i = 0; i < nb_weapons; i++){
        arsenal[i]=arsenal_[i];
    }
}

Vehicle::Vehicle(){
}


// Fonctions


void Vehicle::Display(){
    body.Display();
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].machine.Display(arsenal[i].pos + body.pos);
        arsenal[i].Display(body.pos);
    }
}
void Vehicle::Erase(){
    body.Erase();
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].machine.Erase(arsenal[i].pos + body.pos);
        arsenal[i].Erase(body.pos);
    }
}
void Vehicle::Move(){
    body.Move();
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Move();
    }
}
void Vehicle::Accelerate(){
    body.Accelerate();
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].Accelerate();
    }
}

Vehicle Vehicle::copy(){
    return Vehicle(body,nb_weapons,arsenal);
}


bool Vehicle::stable(){
    return body.stable;
}

void Vehicle::movement_vehicle(vector<int> keys){
    body.v.x += 0.05*(isPressed(keys,KEY_RIGHT)-isPressed(keys,KEY_LEFT));
    body.v.x = (1-frottements_fluides*dt)*sgn(body.v.x)*max(0.,abs(body.v.x)-body.m*frottements_secs*dt); //frotements fluides
}

void Vehicle::arsenal_collide(Structure &S){
    for(int i=0; i<nb_weapons; i++){
        for (unsigned long j = 0; j < S.boxes.size(); j++){
            arsenal[i].Collide(S.boxes[j]);
        }
    }
}

void Vehicle::angle_machine(vector<int> keys){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].angle_machine(keys);
    }
}

void Vehicle::fire(vector<int> keys, double t){
    for(int i=0; i<nb_weapons; i++){
        arsenal[i].set_fire(keys,body.pos,t);
        arsenal[i].stable(); //Effacer les projectiles stables
    }
}
