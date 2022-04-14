#include "box.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <cmath>;
using namespace std;

Box::Box(Vector pos_,double w_,double h_,double m_, Color Col_, double angle_){
    pos=pos_;
    v = Vector(0,0);
    w = w_;
    h = h_;
    rot = 0;
    angle = angle_;
    m = m_;
    Col = Col_;
}

void Box::Display(){
    int x[4], y[4];
    double x1 = h/2.*cos(angle),
           x2 = w/2.*sin(angle),
           y1 = h/2.*sin(angle),
           y2 = w/2.*cos(angle);
    x[0] = x1+x2+pos.x;
    x[1] = x1-x2+pos.x;
    x[2] = -x1-x2+pos.x;
    x[3] = -x1+x2+pos.x;
    y[0] = y1-y2+pos.y;
    y[1] = y1+y2+pos.y;
    y[2] = -y1+y2+pos.y;
    y[3] = -y1-y2+pos.y;
    fillPoly(x,y,4,Col);
}

void Box::Move(){
    pos = pos + dt*v;
}

void Box::Accelerate(){
    v.y = v.y - dt*g;   // effet de la gravité
}

void Box::Collide(Box b){
}
