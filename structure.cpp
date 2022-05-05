#include "structure.h"
#include "vector.h"
#include <Imagine/LinAlg.h>

using namespace Imagine;
using namespace std;



Structure::Structure(){
}

Structure::Structure(Box box){
    boxes.push_back(box);
}

Structure::Structure(vector<Box> boxes_){
    for (unsigned long i = 0; i < boxes_.size(); i++){
        boxes.push_back(boxes_[i]);
    }
}


void Structure::add(Box box){
    boxes.push_back(box);
}


void Structure::add(Ball ball){
    balls.push_back(ball);
}


void Structure::add(Joint joint){
    joints.push_back(joint);
}


void Structure::add(Spring spring){
    springs.push_back(spring);
}


Vector2D& Structure::getPosition(int type_a, int a){
    if(type_a == 0)
        return boxes[a].pos;
    else
        return balls[a].pos;
}


Vector2D& Structure::getSpeed(int type_a, int a){
    if(type_a == 0)
        return boxes[a].v;
    else
        return balls[a].v;
}


double Structure::getMass(int type_a, int a){
    if(type_a == 0)
        return boxes[a].m;
    else
        return balls[a].m;
}

void Structure::Display(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Display();
    }
    for (unsigned long i = 0; i < balls.size(); i++){
        balls[i].Display();
    }
    for (unsigned long i = 0; i < joints.size(); i++){
        joints[i].Display(getPosition(joints[i].type_a,joints[i].a),getPosition(joints[i].type_b,joints[i].b));
    }
    for (unsigned long i = 0; i < springs.size(); i++){
        springs[i].Display(getPosition(springs[i].type_a,springs[i].a),getPosition(springs[i].type_b,springs[i].b));
    }
}


void Structure::Erase(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Erase();
    }
    for (unsigned long i = 0; i < balls.size(); i++){
        balls[i].Erase();
    }
    for (unsigned long i = 0; i < joints.size(); i++){
        joints[i].Erase(getPosition(joints[i].type_a,joints[i].a),getPosition(joints[i].type_b,joints[i].b));
    }
    for (unsigned long i = 0; i < springs.size(); i++){
        springs[i].Erase(getPosition(springs[i].type_a,springs[i].a),getPosition(springs[i].type_b,springs[i].b));
    }
}


void Structure::Move(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Move();
    }
    for (unsigned long i=0; i<balls.size();i++){
        balls[i].Move();
    }
}


void Structure::Accelerate(){
    // effet gravite
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Accelerate();
    }
    for(unsigned long i=0; i<balls.size();i++){
        balls[i].Accelerate();
    }
    Vector2D pos1,pos2;
    double m1,m2;

    // effet des ressorts/elastiques
    for(unsigned long i=0; i<springs.size(); i++){
        pos1 = getPosition(springs[i].type_a,springs[i].a);
        pos2 = getPosition(springs[i].type_b,springs[i].b);
        m1 = getMass(springs[i].type_a,springs[i].a);
        m2 = getMass(springs[i].type_b,springs[i].b);
        // dv1 = -k/m1*(l-l0)*e21
        getSpeed(springs[i].type_a,springs[i].a) += -dt*springs[i].k/m1*((pos1-pos2).norme()-springs[i].l0)*(pos1-pos2).normalize();
        getSpeed(springs[i].type_b,springs[i].b) += -dt*springs[i].k/m2*((pos2-pos1).norme()-springs[i].l0)*(pos2-pos1).normalize();
    }
}


void Structure::AutoCollide(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        for (unsigned long j = 0; j < i; j++){ // On parcourt le triangle strict
            boxes[i].Collide(boxes[j]);
        }
    }
}


void Structure::Collide(Structure &S){
    for (unsigned long i = 0; i < boxes.size(); i++){
        for (unsigned long j = 0; j < S.boxes.size(); j++){
            boxes[i].Collide(S.boxes[j]);
        }
    }
}


Structure Structure::copy(){
    Structure copy;
    for (unsigned long i = 0; i < boxes.size(); i++){
        copy.boxes.push_back(boxes[i]);
    }
    for(unsigned long i=0; i<balls.size();i++){
        copy.balls.push_back(balls[i]);
    }
    for(unsigned long i=0; i<joints.size();i++){
        copy.joints.push_back(joints[i]);
    }
    for(unsigned long i=0; i<springs.size();i++){
        copy.springs.push_back(springs[i]);
    }
    return copy;
}


void Structure::groundBounce(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].groundBounce();
    }
}

SymMatrix<bool> Structure::Collisions(){
    SymMatrix<bool> Coll(boxes.size()+balls.size());
    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            Coll(i,j) = boxes[i].Collide(boxes[j]);
        }
        for(unsigned long j=0; j<balls.size(); j++){
            Coll(i,j+boxes.size()) = boxes[i].Collide(balls[j]);
        }
    }
    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            Coll(i+boxes.size(),j+boxes.size()) = balls[i].Collide(balls[j]);
        }
    }
    return Coll;
}

Vector<Vector2D> Structure::collisionsInfo(const SymMatrix<bool>& Coll){
    int nb_collisions=0;
    for(int i=0; i<Coll.ncol(); i++){
        for(int j=i+1; j<Coll.nrow(); j++){
            nb_collisions += Coll(i,j);
        }
    }

    Vector<Vector2D> Infos(2*nb_collisions);
    int n = 0;

    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            if(Coll(i,j)){

                n+=2;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j)){

                n+=2;
            }
        }
    }

    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i,j)){
                // creation d'alias pour faciliter la lecture
                Ball& b1 = balls[i];
                Ball& b2 = balls[j];
                Infos[n] = 1/(b1.r+b2.r)*(b2.r*b1.pos+b1.r*b2.pos);
                Infos[n+1] = (b1.pos-b2.pos).normalize()*(b1.r+b2.r-(b1.pos-b2.pos).norme());
                n+=2;
            }
        }
    }
    return Infos;
}

Vector<double> Structure::constructC(Vector<Vector2D>& Infos){
    Vector<double> C(joints.size()+Infos.size()/2);
    for(unsigned long i=0; i<joints.size(); i++){
        C[i] = joints[i].C(getPosition(joints[i].type_a,joints[i].a), getPosition(joints[i].type_b,joints[i].b));
    }
    for(unsigned long i=0; i<Infos.size()/2; i++){
        C[i+joints.size()] = -Infos[2*i+1].norme();
    }
    return C;
}


Vector<double> Structure::constructQ(){
    Vector<double> Q(3*(boxes.size()+balls.size()));
    for(unsigned long i=0; i<boxes.size(); i++){
        Q[3*i] = boxes[i].v.x;
        Q[3*i+1] = boxes[i].v.y;
        Q[3*i+2] = boxes[i].omega;
    }
    int j;
    for(unsigned long i=0; i<balls.size(); i++){
        j = i+boxes.size();
        Q[3*j] = balls[i].v.x;
        Q[3*j+1] = balls[i].v.y;
        Q[3*j+2] = balls[i].omega;
    }
    return Q;
}


Matrix<double> Structure::constructJ(Vector<Vector2D>& Infos,SymMatrix<bool>& Coll){
    Matrix<double> J = Matrix<double>::Zero(joints.size()+Infos.size()/2,3*(balls.size()+boxes.size()));
    Vector2D pos1, pos2, dir;
    int i1,i2;
    for(unsigned long i=0; i<joints.size(); i++){
        pos1 = getPosition(joints[i].type_a,joints[i].a);
        pos2 = getPosition(joints[i].type_b,joints[i].b);
        i1 = joints[i].type_a*boxes.size()+joints[i].a;
        i2 = joints[i].type_b*boxes.size()+joints[i].b;
        dir = (pos1-pos2).normalize();
        J(i,3*i1) = dir.x;
        J(i,3*i1+1) = dir.y;
        J(i,3*i2) = -dir.x;
        J(i,3*i2+1) = -dir.y;
    }
    int n=0;
    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            if(Coll(i,j)){

                n++;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j)){

                n++;
            }
        }
    }

    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i,j)){
                i1 = i+boxes.size();
                i2 = j+boxes.size();
                dir = Infos[2*n+1].normalize();
                J(n+joints.size(),3*i1)= dir.x;
                J(n+joints.size(),3*i1+1)= dir.y;
                J(n+joints.size(),3*i2)= -dir.x;
                J(n+joints.size(),3*i2+1)= -dir.y;
                n++;
            }
        }
    }
    return J;
}

Matrix<double> Structure::constructM(){
    Vector<double> M(3*(balls.size()+boxes.size()));
    for(unsigned long i=0; i<boxes.size(); i++){
        M[3*i] = 1/boxes[i].m;
        M[3*i+1] = 1/boxes[i].m;
        M[3*i+2] = 1/boxes[i].I();
    }
    int j;
    for(unsigned long i=0; i<balls.size(); i++){
        j = i+boxes.size();
        M[3*j] = 1/balls[i].m;
        M[3*j+1] = 1/balls[i].m;
        M[3*j+2] = 1/balls[i].I();
    }
    return Diagonal(M);
}


void Structure::solveConstraints(){
    double beta = 0.5;  // a priori beta=1 ideal mais beta=0.5 limite les potentiels problemes de stabilite
    SymMatrix<bool> Coll(Collisions());
    Vector<Vector2D> Infos(collisionsInfo(Coll));
    if(joints.size()==0 and Infos.size()==0)
        return;
    Vector<double> C(constructC(Infos));
    Vector<double> Q(constructQ());
    Matrix<double> J(constructJ(Infos,Coll));
    Matrix<double> M(constructM());

    Vector<double> dV(M*transpose(J)*linSolve(J*M*transpose(J),-J*Q-beta/dt*C));
    for(unsigned long i=0; i<boxes.size(); i++){
        boxes[i].v.x += dV[3*i];
        boxes[i].v.y += dV[3*i+1];
        boxes[i].omega += dV[3*i+2];
    }
    int j;
    for(unsigned long i=0; i<balls.size(); i++){
        j=i+boxes.size();
        balls[i].v.x += dV[3*j];
        balls[i].v.y += dV[3*j+1];
        balls[i].omega += dV[3*j+2];
    }
}
