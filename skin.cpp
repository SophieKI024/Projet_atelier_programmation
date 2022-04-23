#include "skin.h"


// ==================================== Skin =============================================================

Skin::Skin(){}

Skin::Skin(Vector* border_, int nb_points_, Color Col_, double scale_factor_, double angle_){
    border = border_;
    Col = Col_;
    angle = angle_;
    nb_points = nb_points_;
    scale_factor = scale_factor_;
}

void Skin::Display(Vector pos){
    int x[nb_points], y[nb_points];
    Vector rotX = Vector(cos(angle), -sin(angle));
    Vector rotY = Vector(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(pos.x + scale_factor*border[i]*rotX);
        y[i] = int(pos.y + scale_factor*border[i]*rotY);
    }
    fillPoly(x,y,nb_points,Col);
}

void Skin::Erase(Vector pos){
    int x[nb_points], y[nb_points];
    Vector rotX = Vector(cos(angle), -sin(angle));
    Vector rotY = Vector(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(pos.x + scale_factor*border[i]*rotX);
        y[i] = int(pos.y + scale_factor*border[i]*rotY);
    }
    fillPoly(x,y,nb_points,backgroundColor);
}
