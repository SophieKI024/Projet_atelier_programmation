#include "box.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <cmath>
using namespace std;


Box::Box(Vector pos_,double w_,double h_,double rho_, Color Col_, double angle_, Vector v_, double omega_){
    pos=pos_;
    v = v_;
    w = w_;
    h = h_;
    omega = omega_;
    angle = angle_;
    m = rho_*w*h;
    Col = Col_;
    stabile = false;
}

Box::Box(){
    //Box(Vector(0,0),0,0,0,WHITE);
}

void Box::Display(){
    int x[4], y[4];
    corners(x,y);
    fillPoly(x,y,4,Col);
}

void Box::Move(){
    pos += dt*v;
    angle  += dt*omega;
}

void Box::stepBack(){
    pos -= dt*v;
    angle  -= dt*omega;
}

void Box::Accelerate(){
    if(!stabile)
    v.y = v.y + dt*g;   // effet de la gravité
}

bool Box::Collide(Box& b){
    double x1[4],y1[4],x2[4],y2[4];
    corners(x1,y1);
    b.corners(x2,y2);
    double treshold=1e-2;
    vector<Vector> lst; // on stocke tous les coins qui sont rentres dans l'autre rectangle
    for(int i=0; i<4; i++){
        if(abs(cos(angle)*(x2[i]-pos.x)+sin(angle)*(y2[i]-pos.y))<=w/2. and abs(-sin(angle)*(x2[i]-pos.x)+cos(angle)*(y2[i]-pos.y))<=h/2.)
            lst.push_back(Vector(x2[i],y2[i]));
    }
    for(int i=0; i<4; i++){
        if(abs(cos(b.angle)*(x1[i]-b.pos.x)+sin(b.angle)*(y1[i]-b.pos.y))<=b.w/2. and abs(-sin(b.angle)*(x1[i]-b.pos.x)+cos(b.angle)*(y1[i]-b.pos.y))<=b.h/2.)
            lst.push_back(Vector(x1[i],y1[i]));
    }
    if(!lst.empty()){
        double coeff = 0.6;
        double transfert = 0.5;
        Vector c;
        // disjonction de cas pour eviter des pb dans des cas particuliers
        if(lst.size()==1)
            c=lst[0];
        else if(lst.size()==2 or (lst[0]-lst[1]).norme()>dt*max(v.norme(),b.v.norme()))
            c=0.5*(lst[1]+lst[0]);
        else
            c=0.5*(lst[0]+lst[2]);
        stepBack();
        b.stepBack();
        Vector w1 = v + omega*Vector(-c.y+pos.y,c.x-pos.x);
        Vector w2 = b.v + b.omega*Vector(-c.y+b.pos.y,c.x-b.pos.x);
        Vector delta_v1 = 2.*b.m/(m+b.m)*(w2-w1);
        Vector delta_v2 = 2.*m/(m+b.m)*(w1-w2);
        Vector t1,t2,n1,n2;
        t1 = 1/(c-pos).norme()*(c-pos);
        n1 = Vector(-t1.y,t1.x);
        t2 = 1/(c-b.pos).norme()*(c-b.pos);
        n2 = Vector(-t2.y,t2.x);
        v += coeff*(delta_v1*t1*t1 +transfert*delta_v1*n1*n1);
        omega += coeff*(1-transfert)/(c-pos).norme()*delta_v1*n1;
        b.v += coeff*(delta_v2*t2*t2+transfert*delta_v2*n2*n2);
        b.omega += coeff*(1-transfert)/(c-b.pos).norme()*delta_v2*n2;
        Move();
        b.Move();
        stabile = false;
        b.stabile = false;
        return true;
    }
    return false;
}

void Box::Erase(){
    int x[4], y[4];
    corners(x,y);
    fillPoly(x,y,4,WHITE);
}

Box Box::copy(){
    return Box(pos,w,h,m, Col, angle);
}

bool Box::groundBounce(){
    if(stabile)
        return false;
    else{
        double coeff = 0.6; // sorte de coefficient de rebond, coeff=1 <=> pas de perte d'énergie
        double x[4], y[4];
        double treshold=1e-2;
        corners(x,y);
        vector<Vector> lst;
        for(int i=0; i<4; i++){
            if(y[i]>height-h_ground)
                lst.push_back(Vector(x[i],y[i]));
        }
        // rebond "simple"
        if(!lst.empty()){
            stepBack();
            double coeff = 0.6;
            double transfert = 0.5;
            Vector c=Vector(0,0);   // point de contact
            for(int i=0; i<lst.size(); i++){
                c += (1/double(lst.size()))*lst[i];
            }
            Vector delta_v = -2*( v + omega*Vector(-c.y+pos.y,c.x-pos.x));
            Vector t = 1/(c-pos).norme()*(c-pos);
            Vector n = Vector(-t.y,t.x);
            v += coeff*(delta_v*t*t +transfert*delta_v*n*n);
            omega += coeff*(1-transfert)/(c-pos).norme()*delta_v*n;
            Move();
            // condition pour qu'un objet reste collé au sol
            if(v.norme()<treshold and omega<treshold and abs(fmod(angle+1000*M_PI+M_PI/4.,M_PI/2.)-M_PI/4)*max(w,h)<treshold){
                stabile = true;
                v=Vector(0,0);
                omega =0;
            }
            return true;
        }
        return false;
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
