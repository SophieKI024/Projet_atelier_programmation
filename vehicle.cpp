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
// -------------- Gestion clavier ----------------------------------------------------------------------------------

char keyboard() {
    Event e;
    do {
        getEvent(0,e);
        if(e.type==EVT_KEY_ON)
            return e.key;
    } while(e.type!=EVT_NONE);
    return 0;
}



bool Vehicle::move_right(){
    int go_right = keyboard();
    if (go_right == KEY_RIGHT){
        return true;
    }
    return false;
}

bool Vehicle::move_left(){
    int go_left = keyboard();
    if (go_left == KEY_LEFT){
        return true;
    }
    return false;
}

void Vehicle::movement_vehicle(){
    if (move_right() == true){
        body.v.x+=0.1*dt;
    }
    if (move_left() == true){
        body.v.x-=0.1*dt;
    }
}

