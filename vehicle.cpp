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


// ==================================== Skin =============================================================

Skin::Skin(){}

Skin::Skin(Vector* border_, int nb_points_, Color Col_, Vector pos_, double scale_factor_, double angle_){
    border = border_;
    Col = Col_;
    pos = pos_;
    angle = angle_;
    nb_points = nb_points_;
    scale_factor = scale_factor_;
}

void Skin::Display(){
    int x[nb_points], y[nb_points];
    Vector rotX = Vector(cos(angle), -sin(angle));
    Vector rotY = Vector(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(pos.x + scale_factor*border[i]*rotX);
        y[i] = int(pos.y + scale_factor*border[i]*rotY);
    }
    fillPoly(x,y,nb_points,Col);
}

void Skin::Erase(){
    int x[nb_points], y[nb_points];
    Vector rotX = Vector(cos(angle), -sin(angle));
    Vector rotY = Vector(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(pos.x + scale_factor*border[i]*rotX);
        y[i] = int(pos.y + scale_factor*border[i]*rotY);
    }
    fillPoly(x,y,nb_points,WHITE);
}

