#include "box.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <cmath>
using namespace std;


Box::Box(Vector pos_,double w_,double h_,double m_, Color Col_, double angle_, Vector v_, double omega_){
    pos=pos_;
    v = v_;
    w = w_;
    h = h_;
    omega = omega_;
    angle = angle_;
    m = m_;
    Col = Col_;
}

void Box::Display(bool erase){
    int x[4], y[4];
    corners(x,y);
    if(erase)
        fillPoly(x,y,4,WHITE);
    else
        fillPoly(x,y,4,Col);
}

void Box::Move(){
    pos = pos + dt*v;
    angle  = angle + dt*omega;
}

void Box::Accelerate(){
    v.y = v.y + dt*g;   // effet de la gravité
    groundBounce();
}

void Box::Collide(Box b){
}

void Box::Erase(){
    Display(true);
}

Box Box::copy(){
    return Box(pos,w,h,m, Col, angle);
}

void Box::groundBounce(){
    int x[4], y[4];
    corners(x,y);
    bool collide = false;
    for(int i=0; i<4 and !collide; i++){
        collide = (y[i]>height-h_ground);
    }
    if(collide){
        v.y = -v.y;
    }
}

void Box::corners(int x[4], int y[4]){
    double x1 = h/2.*cos(angle),
           x2 = w/2.*sin(angle),
           y1 = h/2.*sin(angle),
           y2 = w/2.*cos(angle);
    x[0] = int(x1+x2+pos.x);
    x[1] = int(x1-x2+pos.x);
    x[2] = int(-x1-x2+pos.x);
    x[3] = int(-x1+x2+pos.x);
    y[0] = int(y1-y2+pos.y);
    y[1] = int(y1+y2+pos.y);
    y[2] = int(-y1+y2+pos.y);
    y[3] = int(-y1-y2+pos.y);
}
