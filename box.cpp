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
    gravity = true;
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
    if(gravity)
    v.y = v.y + dt*g;   // effet de la gravité
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

vector<Vector2D> Box::collisionInfos(Box& b){
    double x1[4],y1[4],x2[4],y2[4];
    corners(x1,y1);
    b.corners(x2,y2);
    vector<Vector2D> output;
    vector<Vector2D> intersections;
    double alpha,beta;
    int i2,j2;
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            i2=(i+1)%4;
            j2=(j+1)%4;
            if(solve(x1[i2]-x1[i],x2[j]-x2[j2],y1[i2]-y1[i],y2[j]-y2[j2],x2[j]-x1[i],y2[j]-y1[i],alpha,beta)){
                if(0<=alpha and alpha<=1 and 0<=beta and beta<=1)
                intersections.push_back( Vector2D(x1[i]+alpha*(x1[i2]-x1[i]), y1[i]+alpha*(y1[i2]-y1[i])) );
            }
        }
    }
    Vector2D P,t,n;
    // cas impossibles en principes mais traités par prudence
    if(intersections.size()==0){
        P = 0.5*(pos+b.pos);
        n = (b.pos-pos).normalize();
    }
    //idem
    else if(intersections.size()==1){
        P = intersections[0];
        n = (b.pos-pos).normalize();
    }
    // seul cas possible a priori
    else{
    P = 0.5*(intersections[0]+intersections[1]);
    t = (intersections[0]-intersections[1]).normalize();//vecteur tangent de la collision
    n = Vector2D(-t.y,t.x).normalize();
    n = sgn(n*(P-pos))*n;
    }
    output.push_back(P);
    output.push_back(n);

    return output;
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
    if(max(w,h)+b.r<(pos-b.pos).norme())
        return false;

    Vector2D v = minimalDistance(b.pos);
    double dist = sgn(v*(pos-b.pos))*v.norme();
    return dist<=b.r+eps;
}

void Box::Erase(){
    int x[4], y[4];
    corners(x,y);
    fillPoly(x,y,4,backgroundColor);
}

Box Box::copy(){
    return Box(pos,w,h,m, Col, angle);
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
