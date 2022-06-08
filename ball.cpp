#include "ball.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;

double Ball::I(){
    return 0.5*r*r*m;
}

void Ball::Display(double scale, Vector2D scroll){
    fillCircle(scale*(pos.x-scroll.x),scale*(pos.y-scroll.y),scale*r,Col);
    Vector2D R = rotation(Vector2D(0.9*r,0),angle);
    Vector2D R2 = rotation(R,M_PI/2);
    Color Col_bis = Color(150,150,150);
    if(cross){
    drawLine(scale*((pos+R).x-scroll.x),scale*((pos+R).y-scroll.y),scale*((pos-R).x-scroll.x),scale*((pos-R).y-scroll.y),Col_bis,0.5+0.1*scale*r);
    drawLine(scale*((pos+R2).x-scroll.x),scale*((pos+R2).y-scroll.y),scale*((pos-R2).x-scroll.x),scale*((pos-R2).y-scroll.y),Col_bis,0.5+0.1*scale*r);
    }
}

void Ball::Erase(double scale, Vector2D scroll){
    fillCircle(scale*(pos.x-scroll.x),scale*(pos.y-scroll.y),scale*r,backgroundColor);
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
    return (pos-b.pos).norme()<=r+b.r;
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
    breaking_energy = INFINITY;
    gravity = true;
}

void Ball::applyForce(Vector2D f, Vector2D p){
    applyForceGeneric(f,p,pos,v,omega,m,I());
}

Ball::Ball(){}

Ball Ball::copy(){
    return Ball(pos,r,m,Col,v,omega);
}

