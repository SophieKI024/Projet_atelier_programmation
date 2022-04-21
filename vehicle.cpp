#include "vehicle.h"
#include "box.h"

// Constructeur


Vehicle::Vehicle(Box body_){
    body = body_.copy();
}

// Fonctions


void Vehicle::Display(){
    body.Display();
}

void Vehicle::Erase(){
    body.Erase();
}

