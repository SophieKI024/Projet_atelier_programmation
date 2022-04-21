#include "vehicle.h"
#include "box.h"

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
