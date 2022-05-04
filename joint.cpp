#include "joint.h"
#include "vector.h"
#include "tools.h"


//////////////////////////JOINT////////////////////////////////////////////

void Joint::Display(Vector2D pos1, Vector2D pos2){
    drawLine(pos1.x,pos1.y,pos2.x,pos2.y,Col,e);
}

void Joint::Erase(Vector2D pos1, Vector2D pos2){
    drawLine(pos1.x,pos1.y,pos2.x,pos2.y,backgroundColor,e);
}

Joint::Joint(int type_a_, int a_, int type_b_, int b_, double l_, int e_, Color Col_){
    type_a = type_a_;
    a=a_;
    type_b = type_b_;
    b=b_;
    l = l_;
    e = e_;
    Col = Col_;
}

Joint::Joint(){}

double Joint::C(Vector2D pos1, Vector2D pos2){
    return (pos1-pos2).norme()-l;
}

Vector2D Joint::J(Vector2D pos1, Vector2D pos2){
    return (pos1-pos2).normalize();
}


Joint Joint::copy(){
    return Joint(type_a, a, type_b, b, l, e, Col);
}


/////////////////////////////////SPRING///////////////////////////////////

Spring::Spring(){}

Spring::Spring(int type_a_, int a_, int type_b_, int b_, double l0_, double lmin_, double lmax_, double k_, double e0_, Color Col_){
    type_a = type_a_;
    a = a_;
    type_b = type_b_;
    b = b_;
    l0 = l0_;
    lmin = lmin_;
    lmax = lmax_;
    k = k_;
    e0 = e0_;
    Col = Col_;
}


void Spring::Display(Vector2D pos1, Vector2D pos2){
    int e = e0*l0/(pos1-pos2).norme()+0.5;
    drawLine(pos1.x,pos1.y,pos2.x,pos2.y,Col,e);
}

void Spring::Erase(Vector2D pos1, Vector2D pos2){
    int e = e0*l0/(pos1-pos2).norme()+0.5;
    drawLine(pos1.x,pos1.y,pos2.x,pos2.y,backgroundColor,e);
}
