#include "joint.h"
#include "vector.h"
#include "tools.h"


//////////////////////////JOINT////////////////////////////////////////////

void Joint::Display(Vector2D pos1, Vector2D pos2, double scale, Vector2D scroll){
    drawLine(scale*(pos1.x-scroll.x),scale*(pos1.y-scroll.y),scale*(pos2.x-scroll.x),scale*(pos2.y-scroll.y),Col,scale*e);
}

void Joint::Erase(Vector2D pos1, Vector2D pos2, double scale, Vector2D scroll){
    drawLine(scale*(pos1.x-scroll.x),scale*(pos1.y-scroll.y),scale*(pos2.x-scroll.x),scale*(pos2.y-scroll.y),backgroundColor,scale*e);
}

Joint::Joint(int type_a_, int a_, int type_b_, int b_, double l_, double e_, Color Col_,Vector2D pos_a_, Vector2D pos_b_){
    type_a = type_a_;
    a=a_;
    type_b = type_b_;
    b=b_;
    l = l_;
    e = e_;
    Col = Col_;
    pos_a = pos_a_;
    pos_b = pos_b_;
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

Spring::Spring(int type_a_, int a_, int type_b_, int b_, double l0_, double lmin_, double lmax_, double k_, double e0_, Color Col_, Vector2D pos_a_, Vector2D pos_b_){
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
    pos_a = pos_a_;
    pos_b = pos_b_;
}


void Spring::Display(Vector2D pos1, Vector2D pos2, double scale, Vector2D scroll){
    double e = e0*l0/(pos1-pos2).norme();
    drawLine(scale*(pos1.x-scroll.x),scale*(pos1.y-scroll.y),scale*(pos2.x-scroll.x),scale*(pos2.y-scroll.y),Col,scale*e);
}

void Spring::Erase(Vector2D pos1, Vector2D pos2, double scale, Vector2D scroll){
    double e = e0*l0/(pos1-pos2).norme();
    drawLine(scale*(pos1.x-scroll.x),scale*(pos1.y-scroll.y),scale*(pos2.x-scroll.x),scale*(pos2.y-scroll.y),backgroundColor,scale*e);
}

////////////////////////////////////// DAMPER //////////////////////////

Damper::Damper(){};

Damper::Damper(int type_a_, int a_, int type_b_, int b_, double lambda_, Vector2D pos_a_, Vector2D pos_b_){
    type_a = type_a_;
    a = a_;
    type_b = type_b_;
    b = b_;
    lambda = lambda_;
    pos_a = pos_a_;
    pos_b = pos_b_;
}
