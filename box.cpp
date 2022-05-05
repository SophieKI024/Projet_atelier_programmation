#include "box.h"
#include "vector.h"
#include "tools.h"
#include <Imagine/Graphics.h>
using namespace Imagine;
#include <cmath>
using namespace std;


Box::Box(Vector2D pos_,double w_,double h_,double rho_, Color Col_, double angle_, Vector2D v_, double omega_){
    pos=pos_;
    v = v_;
    w = w_;
    h = h_;
    omega = omega_;
    angle = angle_;
    m = rho_*w*h;
    Col = Col_;
    stable = false;
    grounded = false;
}

Box::Box(){
    //Box(Vector2D(0,0),0,0,0,backgroundColor);
}

double Box::I(){
    return m*(h*h+w*w)/12;
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
    v = (1-frottements_fluides*dt)*v;
    //if(!stable)
    //v.y = v.y + dt*g;   // effet de la gravité
}

Vector2D Box::minimalDistance(Vector2D p){

    double x[4], y[4];
    corners(x,y);
    Vector2D v_min(x[0]-p.x,y[0]-p.y);
    int i_min = 0;
    Vector2D v;
    for(int i=1; i<4; i++){
        v = Vector2D(x[i]-p.x,y[i]-p.y);
        if(v.norme2()<v_min.norme2()){
            i_min = i;
            v_min = v;
        }
    }
    Vector2D v2(x[(i_min+3)%4]-p.x,y[(i_min+3)%4]-p.y);
    Vector2D v3(x[(i_min+1)%4]-p.x,y[(i_min+1)%4]-p.y);

    double lambda2 = v_min*(v_min-v2)/(v_min-v2).norme2();
    double lambda3 = v_min*(v_min-v3)/(v_min-v3).norme2();
    if(lambda2<0){
        if(lambda3<0)
            return v_min;
        return v_min-lambda3*(v_min-v3);
    }
    if(lambda3<0)
        return v_min-lambda2*(v_min-v2);
    if((v_min-lambda3*(v_min-v3)).norme2()<(v_min-lambda2*(v_min-v2)).norme2())
        return v_min-lambda3*(v_min-v3);
    return v_min-lambda2*(v_min-v2);
}

bool Box::Collide(Box& b){

    // on recupere les coins de chaque Box
    double x1[4],y1[4],x2[4],y2[4];
    corners(x1,y1);
    b.corners(x2,y2);

    // on teste si les coins des boxs sont contenus dans les autres Box
    for(int i=0; i<4; i++){
        if(abs(cos(angle)*(x2[i]-pos.x)+sin(angle)*(y2[i]-pos.y))<=w/2. and abs(-sin(angle)*(x2[i]-pos.x)+cos(angle)*(y2[i]-pos.y))<=h/2.)
            return true;
        if(abs(cos(b.angle)*(x1[i]-b.pos.x)+sin(b.angle)*(y1[i]-b.pos.y))<=b.w/2. and abs(-sin(b.angle)*(x1[i]-b.pos.x)+cos(b.angle)*(y1[i]-b.pos.y))<=b.h/2.)
            return true;
    }
    return false;
}

bool Box::Collide(Ball& b){
    Vector2D v = minimalDistance(b.pos);
    double dist = sgn(v*(pos-b.pos))*v.norme();
    return dist<=b.r;
}

void Box::Erase(){
    int x[4], y[4];
    corners(x,y);
    fillPoly(x,y,4,backgroundColor);
}

Box Box::copy(){
    return Box(pos,w,h,m, Col, angle);
}

bool Box::groundBounce(){
    if(stable)
        return false;
    else{
        double coeff = 0.6; // sorte de coefficient de rebond, coeff=1 <=> pas de perte d'énergie
        double x[4], y[4];
        double treshold=1e-2;
        corners(x,y);
        vector<Vector2D> lst;
        for(int i=0; i<4; i++){
            if(y[i]>window_height-h_ground)
                lst.push_back(Vector2D(x[i],y[i]));
        }
        // rebond "simple"
        if(!lst.empty()){
            stepBack();
            double coeff = 0.6;
            double transfert = 0.5;
            Vector2D c=Vector2D(0,0);   // point de contact
            for(int i=0; i<lst.size(); i++){
                c += (1/double(lst.size()))*lst[i];
            }
            Vector2D delta_v = -2*( v + omega*Vector2D(-c.y+pos.y,c.x-pos.x));
            Vector2D t = 1/(c-pos).norme()*(c-pos);
            Vector2D n = Vector2D(-t.y,t.x);
            v += coeff*(delta_v*t*t +transfert*delta_v*n*n);
            omega += coeff*(1-transfert)/(c-pos).norme()*delta_v*n;
            Move();
            // condition pour qu'un objet reste collé au sol
            if(v.norme()<treshold and omega<treshold and abs(fmod(angle+1000*M_PI+M_PI/4.,M_PI/2.)-M_PI/4)*max(w,h)<treshold){
                stable = true;
                grounded = true;
                v=Vector2D(0,0);
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

void Box::cornersExtended(double x[8], double y[8]){
    double x1 = w/2.*cos(angle),
            x2 = h/2.*sin(angle),
            y1 = w/2.*sin(angle),
            y2 = h/2.*cos(angle);
    x[0] = x1+pos.x;
    x[1] = x2+pos.x;
    x[2] = -x1+pos.x;
    x[3] = -x2+pos.x;
    x[4] = x1+x2+pos.x;
    x[5] = x1-x2+pos.x;
    x[6] = -x1-x2+pos.x;
    x[7] = -x1+x2+pos.x;
    y[0] = y1+pos.y;
    y[1] = y2+pos.y;
    y[2] = -y1+pos.y;
    y[3] = -y2+pos.y;
    y[4] = y1-y2+pos.y;
    y[5] = y1+y2+pos.y;
    y[6] = -y1+y2+pos.y;
    y[7] = -y1-y2+pos.y;
}
