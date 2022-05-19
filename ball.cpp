#include "ball.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

double Ball::I(){
    return 0.5*r*r*m;
}

void Ball::Display(){
    fillCircle(pos.x,pos.y,r,Col);
}

void Ball::Erase(){
    fillCircle(pos.x,pos.y,r,backgroundColor);
}

void Ball::Move(){
    pos += v*dt;
}

void Ball::stepBack(){
    pos -= v*dt;
}

void Ball::Accelerate(){
    v = (1-frottements_fluides*dt)*v;
    v.y += g*dt;
}

bool Ball::Collide(Ball& b){
    return (pos-b.pos).norme()<=r+b.r+eps;
}

double Ball::ballC(Ball b){
    return max(0.,r+b.r-(pos-b.pos).norme());
}

Ball::Ball(Vector2D pos_,double r_,double rho_,Color Col_,Vector2D v_, double omega_){
    pos=pos_;
    r=r_;
    m=rho_*M_PI*r*r;
    Col=Col_;
    v = v_;
    omega = omega_;
}

Ball::Ball(){}

Ball Ball::copy(){
    return Ball(pos,r,m,Col,v,omega);
}
