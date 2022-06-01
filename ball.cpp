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
    Vector2D R = pos + rotation(Vector2D(0.78*r,0),angle);
    Color Col_bis;
    Col_bis.r() = min(Col.r()+50,255);
    Col_bis.g() = min(Col.g()+50,255);
    Col_bis.b() = min(Col.b()+50,255);
    fillRect(R.x-0.1*r,R.y-0.1*r,0.2*r,0.2*r,Col_bis);
}

void Ball::Erase(){
    fillCircle(pos.x,pos.y,r,backgroundColor);
}

void Ball::Move(){
    pos += v*dt;
    angle += omega*dt;
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

Ball::Ball(Vector2D pos_, double r_, double rho_, Color Col_, Vector2D v_, double omega_, double angle_){
    pos=pos_;
    r=r_;
    m=rho_*M_PI*r*r;
    Col=Col_;
    v = v_;
    omega = omega_;
    angle = angle_;
}

Ball::Ball(){}

Ball Ball::copy(){
    return Ball(pos,r,m,Col,v,omega);
}

