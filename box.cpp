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

void Box::Display(){
    int x[4], y[4];
    corners(x,y);
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
    int x[4], y[4];
    corners(x,y);
        fillPoly(x,y,4,WHITE);
}

Box Box::copy(){
    return Box(pos,w,h,m, Col, angle);
}

void Box::groundBounce(){
    double coeff = 0.6; // sorte de coefficient de rebond, coeff=1 <=> pas de perte d'énergie
    double x[4], y[4];
    corners(x,y);
    bool collide = false;
    for(int i=0; i<4 and !collide; i++){
        collide = (y[i]>height-h_ground);
    }
    // rebond "simple"
    if(collide){
        double R = sqrt(pow(w,2)+pow(h,2));
        double omega_y = -2*v.y/pow(R,2)*(cos(fmodf(angle+1000*M_PI,M_PI))*w-sin(fmodf(angle+1000*M_PI+M_PI/2,M_PI)-M_PI/2)*h);
        if(abs(fmod(angle+1000*M_PI+M_PI/4,M_PI/2)-M_PI/4)<=1e-4) //cas ou l'oblet tombe tout droit
            omega_y=0;
        double omega_x =  2*v.x/pow(R,2)*abs(cos(fmodf(angle+1000*M_PI,M_PI))*h-sin(fmodf(angle+1000*M_PI+M_PI/2,M_PI)-M_PI/2)*w);
        pos.y -= v.y*dt;    // permet de ne pas avoir de probleme de bloc coincee dans le sol
        v.y = (-v.y +0.1*(omega_y-omega)*sgn(fmodf(angle+1000*M_PI+M_PI/2,M_PI)-M_PI/2)*R)*coeff;  //coeff mis un peu au pif pour que ca fasse realiste
        v.x = (v.x - 0.2*(omega_x-omega)*R)*coeff;
        omega =omega_x+omega_y;
    }
}

void Box::corners(double x[4], double y[4]){
    double x1 = w/2.*cos(angle),
            x2 = h/2.*sin(angle),
            y1 = w/2.*sin(angle),
            y2 = h/2.*cos(angle);
    x[0] = x1+x2+pos.x;
    x[1] = x1-x2+pos.x;
    x[2] = -x1-x2+pos.x;
    x[3] = -x1+x2+pos.x;
    y[0] = y1-y2+pos.y;
    y[1] = y1+y2+pos.y;
    y[2] = -y1+y2+pos.y;
    y[3] = -y1-y2+pos.y;
}

void Box::corners(int x[4], int y[4]){
    double x1 = w/2.*cos(angle),
            x2 = h/2.*sin(angle),
            y1 = w/2.*sin(angle),
            y2 = h/2.*cos(angle);
    x[0] = int(x1+x2+pos.x+0.5);    // +0.5 pour faire un arrondi plutot que de tronquer
    x[1] = int(x1-x2+pos.x+0.5);
    x[2] = int(-x1-x2+pos.x+0.5);
    x[3] = int(-x1+x2+pos.x+0.5);
    y[0] = int(y1-y2+pos.y+0.5);
    y[1] = int(y1+y2+pos.y+0.5);
    y[2] = int(-y1+y2+pos.y+0.5);
    y[3] = int(-y1-y2+pos.y+0.5);
}
