#include "vehicle.h"
#include "box.h"
#include "liste_des_skins.h"

// -------------- Gestion clavier ----------------------------------------------------------------------------------

int keyboard() {
    Event e;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON)
            return e.key;
    } while(e.type!=EVT_NONE);
    return 0;
}

// ===================== Vehicle ====================================================================================

// Constructeur


Vehicle::Vehicle(Box body_){
    body = body_.copy();
}

Vehicle::Vehicle(){
}


// Fonctions


void Vehicle::Display(){
    body.Display();
}
void Vehicle::Erase(){
    body.Erase();
}
void Vehicle::Move(){
    body.Move();
}
void Vehicle::Accelerate(){
    body.Accelerate();
}

Vehicle Vehicle::copy(){
    return Vehicle(body);
}

void Vehicle::groundBounce(){
    body.groundBounce();
}

bool Vehicle::stable(){
    return body.stable;
}



bool Vehicle::move_right(int key){
    return key == KEY_RIGHT;
}

bool Vehicle::move_left(int key){
    return key == KEY_LEFT;
}
void Vehicle::movement_vehicle(int key){
    body.v.x += (move_right(key)-move_left(key));

}

