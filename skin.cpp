#include "skin.h"


///////////////////////////////////SKIN/////////////////////////////////////////


Skin::Skin(){}

Skin::Skin(Vector2D* border_, int nb_points_, Color Col_, double scale_factor_, double angle_){
    border = border_;
    Col = Col_;
    angle = angle_;
    nb_points = nb_points_;
    scale_factor = scale_factor_;
}

void Skin::Display(Vector2D pos, double scale, Vector2D scroll){
    int x[nb_points], y[nb_points];
    Vector2D rotX = Vector2D(cos(angle), -sin(angle));
    Vector2D rotY = Vector2D(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(scale*(pos.x + scale_factor*border[i]*rotX - scroll.x));
        y[i] = int(scale*(pos.y + scale_factor*border[i]*rotY - scroll.y));
    }
    fillPoly(x,y,nb_points,Col);
}

void Skin::Erase(Vector2D pos, double scale, Vector2D scroll){
    int x[nb_points], y[nb_points];
    Vector2D rotX = Vector2D(cos(angle), -sin(angle));
    Vector2D rotY = Vector2D(sin(angle),cos(angle));
    for(int i=0; i<nb_points; i++){
        x[i] = int(scale*(pos.x + scale_factor*border[i]*rotX - scroll.x));
        y[i] = int(scale*(pos.y + scale_factor*border[i]*rotY - scroll.y));
    }
    fillPoly(x,y,nb_points,backgroundColor);
}
