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
    Vector2D R = rotation(Vector2D(0.9*r,0),angle);
    Vector2D R2 = rotation(R,M_PI/2);
    Color Col_bis;
    Col_bis.r() = 255-Col.r();
    Col_bis.g() = 255-Col.g();
    Col_bis.b() = 255-Col.b();
    drawLine((pos+R).x,(pos+R).y,(pos-R).x,(pos-R).y,Col_bis,0.5+0.1*r);
    drawLine((pos+R2).x,(pos+R2).y,(pos-R2).x,(pos-R2).y,Col_bis,0.5+0.1*r);
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
    if (gravity){
        v.y += g*dt;
    }
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
    gravity = true;
}

Ball::Ball(){}

Ball Ball::copy(){
    return Ball(pos,r,m,Col,v,omega);
}

