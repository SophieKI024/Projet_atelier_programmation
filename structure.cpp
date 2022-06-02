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

void Structure::movement_vehicle(vector<int> keys){
    Ball& wheel1 = balls[0];
    Ball& wheel2 = balls[1];
    double dir = isPressed(keys,KEY_RIGHT)-isPressed(keys,KEY_LEFT);
    wheel1.omega += dt*car.power*(car.v_max-wheel1.omega*wheel1.r*dir)*dir/(wheel1.r*car.v_max);
    wheel2.omega += dt*car.power*(car.v_max-wheel2.omega*wheel2.r*dir)*dir/(wheel2.r*car.v_max);
}

void Structure::set_fire(vector<int> keys, Vector2D vehicle_pos, double t){
    Vector2D v,pos;
    for (int i=0; i<car.nb_weapons; i++){
        if (isPressed(keys,'z') and  (t-car.arsenal[i].t0)>car.arsenal[i].reload_time){
            Weapon& w = car.arsenal[i];
            v = w.fire_speed*rotation(Vector2D(cos(w.machine.angle),sin(w.machine.angle)),boxes[0].angle);
            pos = rotation(w.pos+w.length*Vector2D(cos(w.machine.angle),sin(w.machine.angle)),boxes[0].angle)+vehicle_pos;
            add(Ball(pos,w.r_ball,w.m_ball/(M_PI*w.r_ball*w.r_ball),BLACK,v,0));
            car.arsenal[i].t0=t;
            boxes[0].v -= w.m_ball/boxes[0].m*v;
            // pas forcement interessant etant donne la forme des vehicule
            //boxes[0].omega -= rotation(v,-M_PI/2)*(pos-vehicle_pos)*w.m_ball/boxes[0].I();
        }
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

void Structure::add(Damper damper){
    dampers.push_back(damper);
}

void Structure::removeBox(int i){
    int size = boxes.size();

    if(i>size){
        cout<<"WARNING : trying to remove a non existent Box"<<endl;
        return;
    }

    swap(boxes.back(),boxes[i]);
    boxes.pop_back();
    long unsigned j=0;
    while(j<joints.size()){

        // on supprime les barres qui etaient relies a la boite a supprimer
        if((joints[j].type_a==0 and joints[j].a==i) or (joints[j].type_b==0 and joints[j].b==i)){
            removeJoint(j);
            j--;
        }

        // on change les indices des barres reliees a la derniere Box
        else{
            if((joints[j].type_a==0 and joints[j].a==size))
                joints[j].a=i;
            if((joints[j].type_b==0 and joints[j].b==size))
                joints[j].b=i;
        }
        j++;
    }

    // idem pour les ressorts
    j=0;
    while(j<springs.size()){

        // on supprime les ressorts qui etaient relies a la boite a supprimer
        if((springs[j].type_a==0 and springs[j].a==i) or (springs[j].type_b==0 and springs[j].b==i)){
            removeSpring(j);
            j--;
        }

        // on change les indices des ressorts reliees a la derniere Box
        else{
            if((springs[j].type_a==0 and springs[j].a==size-1))
                springs[j].a=i;
            if((springs[j].type_b==0 and springs[j].b==size-1))
                springs[j].b=i;
        }
        j++;
    }
}

void Structure::removeBall(int i){
    int size = balls.size();

    if(i>size){
        cout<<"WARNING : trying to remove a non existent Ball"<<endl;
        return;
    }

    swap(balls.back(),balls[i]);
    balls.pop_back();
    long unsigned j=0;
    while(j<joints.size()){

        // on supprime les barres qui etaient relies a la boite a supprimer
        if((joints[j].type_a==1 and joints[j].a==i) or (joints[j].type_b==1 and joints[j].b==i)){
            removeJoint(j);
            j--;
        }

        // on change les indices des barres reliees a la derniere Box
        else{
            if((joints[j].type_a==1 and joints[j].a==size-1))
                joints[j].a=i;
            if((joints[j].type_b==1 and joints[j].b==size-1))
                joints[j].b=i;
        }
        j++;
    }

    // idem pour les ressorts
    j=0;
    while(j<springs.size()){

        // on supprime les ressorts qui etaient relies a la boite a supprimer
        if((springs[j].type_a==1 and springs[j].a==i) or (springs[j].type_b==1 and springs[j].b==i)){
            removeSpring(j);
            j--;
        }

        // on change les indices des ressorts reliees a la derniere Box
        else{
            if((springs[j].type_a==1 and springs[j].a==size))
                springs[j].a=i;
            if((springs[j].type_b==1 and springs[j].b==size))
                springs[j].b=i;
        }
        j++;
    }
}

void Structure::removeJoint(int i){
    if(i>int(joints.size())){
        cout<<"WARNING : trying to remove a non existent Joint"<<endl;
        return;
    }
    swap(joints[i],joints.back());
    joints.pop_back();
}

void Structure::removeSpring(int i){
    if(i>int(springs.size())){
        cout<<"WARNING : trying to remove a non existent Spring"<<endl;
        return;
    }
    swap(springs[i],springs.back());
    springs.pop_back();
}

void Structure::removeDamper(int i){
    if(i>int(dampers.size())){
        cout<<"WARNING : trying to remove a non existent Damper"<<endl;
        return;
    }
    swap(dampers[i],dampers.back());
    dampers.pop_back();
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
    car.Display(boxes[0].pos,boxes[0].angle);
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
    car.Erase(boxes[0].pos,boxes[0].angle);
}


void Structure::Move(vector<int> keys){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Move();
    }
    for (unsigned long i=0; i<balls.size();i++){
        balls[i].Move();
    }
    car.angle_machine(keys);
}


void Structure::Accelerate(vector<int> keys){

    // effet gravite
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Accelerate();
    }
    for(unsigned long i=0; i<balls.size();i++){
        balls[i].Accelerate();
    }

    Vector2D pos1,pos2,dir,delta_v;
    double m1,m2;

    // effet des ressorts
    for(unsigned long i=0; i<springs.size(); i++){
        pos1 = getPosition(springs[i].type_a,springs[i].a);
        pos2 = getPosition(springs[i].type_b,springs[i].b);
        m1 = getMass(springs[i].type_a,springs[i].a);
        m2 = getMass(springs[i].type_b,springs[i].b);
        // dv1 = -k/m1*(l-l0)*e21
        getSpeed(springs[i].type_a,springs[i].a) += -dt*springs[i].k/m1*((pos1-pos2).norme()-springs[i].l0)*(pos1-pos2).normalize();
        getSpeed(springs[i].type_b,springs[i].b) += -dt*springs[i].k/m2*((pos2-pos1).norme()-springs[i].l0)*(pos2-pos1).normalize();
    }

    // mouvement du vehicule
    movement_vehicle(keys);

    // effet des amortisseurs
    for(unsigned long i=0; i<dampers.size(); i++){
        pos1 = getPosition(springs[i].type_a,springs[i].a);
        pos2 = getPosition(springs[i].type_b,springs[i].b);
        dir = (pos2-pos1).normalize();
        m1 = getMass(springs[i].type_a,springs[i].a);
        m2 = getMass(springs[i].type_b,springs[i].b);
        Vector2D& v1 = getSpeed(springs[i].type_a,springs[i].a);
        Vector2D& v2 = getSpeed(springs[i].type_b,springs[i].b);
        delta_v = (v1-v2)*dir*dir;
        v1 -= min(1/m1*dampers[i].lambda*dt,1.)*delta_v;
        v2 += min(1/m2*dampers[i].lambda*dt,1.)*delta_v;
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
    copy.car = car.copy();
    return copy;
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
    vector<Vector2D> InfoBoxBox;
    int n = 0;

    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            if(Coll(i,j)){
                InfoBoxBox = boxes[i].collisionInfos(boxes[j]);
                Infos[2*n] = InfoBoxBox[0];
                Infos[2*n+1] = InfoBoxBox[1];
                n++;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j+boxes.size())){
                Box& b1 = boxes[i];
                Ball& b2 = balls[j];
                Vector2D v = b1.minimalDistance(b2.pos);
                Infos[2*n] = b2.pos+v;
                if(v*(b1.pos-b2.pos)>=0){
                    double norm = abs(v.norme()-b2.r);
                    Infos[2*n+1] = -norm*v.normalize();
                }
                else{
                    double norm = abs(v.norme()+b2.r);
                    Infos[2*n+1] = norm*v.normalize();
                }
                n++;
            }
        }
    }
    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i+boxes.size(),j+boxes.size())){
                // creation d'alias pour faciliter la lecture
                Ball& b1 = balls[i];
                Ball& b2 = balls[j];
                Infos[2*n] = 1/(b1.r+b2.r)*(b2.r*b1.pos+b1.r*b2.pos);
                double norm = abs(b1.r+b2.r-(b1.pos-b2.pos).norme());
                Infos[2*n+1] = (b2.pos-b1.pos).normalize()*max(norm,1e-2);
                n++;
            }
        }
    }
    return Infos;
}

Vector<double> Structure::constructC(Vector<Vector2D>& Infos, SymMatrix<bool> &Coll){
    Vector<double> C(joints.size()+Infos.size()/2);
    double seuil = 0.5;   // seuil au-delà duquel on considère qu'il faut bien écarter les objets
    double coeff = 2e-1;
    for(unsigned long i=0; i<joints.size(); i++){
        C[i] = joints[i].C(getPosition(joints[i].type_a,joints[i].a), getPosition(joints[i].type_b,joints[i].b));
    }
    int n=0;
    for(unsigned long i=0; i<boxes.size()+balls.size(); i++){
        for(unsigned long j=i+1; j<boxes.size()+balls.size(); j++){
            if(Coll(i,j)){
                C[n+joints.size()] = coeff*Infos[2*n+1].norme()*atan(Infos[2*n+1].norme()/seuil);
                n++;
            }
        }
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
    Vector2D pos1, pos2, dir,r1,r2;
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
                r1 = Infos[2*n]-boxes[i].pos;
                r2 =Infos[2*n]-boxes[j].pos;
                dir = Infos[2*n+1].normalize();
                J(n+joints.size(),3*i)= dir.x;
                J(n+joints.size(),3*i+1)= dir.y;
                J(n+joints.size(),3*i+2)= Vector2D(dir.y,-dir.x)*r1;
                J(n+joints.size(),3*j) = -dir.x;
                J(n+joints.size(),3*j+1) = -dir.y;
                J(n+joints.size(),3*j+2)= Vector2D(-dir.y,dir.x)*r2;
                n++;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j+boxes.size())){
                i2 = j+boxes.size();
                r1 = Infos[2*n]-boxes[i].pos;
                dir = Infos[2*n+1].normalize();
                J(n+joints.size(),3*i)= dir.x;
                J(n+joints.size(),3*i+1)= dir.y;
                J(n+joints.size(),3*i+2)= Vector2D(dir.y,-dir.x)*r1;
                J(n+joints.size(),3*i2)= -dir.x;
                J(n+joints.size(),3*i2+1)= -dir.y;
                n++;
            }
        }
    }

    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i+boxes.size(),j+boxes.size())){
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

void Structure::Friction(Vector<Vector2D>& Infos, SymMatrix<bool>& Coll){
    Vector2D pos,t,v1,v2;
    int n=0;
    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            if(Coll(i,j)){
                Box& b1 = boxes[i];
                Box& b2 = boxes[j];
                double coeff1 = b2.m/(b1.m+b2.m);
                double coeff2 = b2.I()/(b1.I()+b2.I());
                pos = Infos[2*n];
                t = rotation(Infos[2*n+1].normalize(),-M_PI/2);
                v1 = b1.v+b1.omega*rotation(pos-b1.pos,M_PI/2);
                v2 = b2.v+b2.omega*rotation(pos-b2.pos,M_PI/2);
                v1 = v1*t*t;
                v2 = v2*t*t;
                double dv = min(frottements_secs*dt,(v2-v1).norme())*(v2-v1).normalize()*t;
                b1.v += coeff1*dv*t;
                b2.v += (coeff1-1)*dv*t;
                b1.omega += coeff2*dv/(pos-b1.pos).norme();
                b2.omega += (coeff2-1)*dv/(pos-b2.pos).norme();
                n++;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j+boxes.size())){
                Box& b1 = boxes[i];
                Ball& b2 = balls[j];
                double coeff1 = b2.m/(b1.m+b2.m);
                double coeff2 = b2.I()/(b1.I()+b2.I());
                pos = Infos[2*n];
                t = rotation(Infos[2*n+1].normalize(),-M_PI/2);
                v1 = b1.v+b1.omega*rotation(pos-b1.pos,M_PI/2);
                v2 = b2.v+b2.omega*rotation(pos-b2.pos,M_PI/2);
                v1 = v1*t*t;
                v2 = v2*t*t;
                double dv = min(10*frottements_secs*dt,(v2-v1).norme())*(v2-v1).normalize()*t;
                b1.v += coeff1*dv*t;
                b2.v += (coeff1-1)*dv*t;
                b1.omega += coeff2*dv/(pos-b1.pos).norme();
                b2.omega += (coeff2-1)*dv/(pos-b2.pos).norme();
                n++;
            }
        }
    }
    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i+boxes.size(),j+boxes.size())){
                Ball& b1 = balls[i];
                Ball& b2 = balls[j];
                double coeff1 = b2.m/(b1.m+b2.m);
                double coeff2 = b2.I()/(b1.I()+b2.I());
                pos = Infos[2*n];
                t = rotation(Infos[2*n+1].normalize(),-M_PI/2);
                v1 = b1.v+b1.omega*rotation(pos-b1.pos,M_PI/2);
                v2 = b2.v+b2.omega*rotation(pos-b2.pos,M_PI/2);
                v1 = v1*t*t;
                v2 = v2*t*t;
                double dv = min(10*frottements_secs*dt,(v2-v1).norme())*(v2-v1).normalize()*t;
                b1.v += coeff1*dv*t;
                b2.v += (coeff1-1)*dv*t;
                b1.omega += coeff2*dv/(pos-b1.pos).norme();
                b2.omega += (coeff2-1)*dv/(pos-b2.pos).norme();
                n++;
            }
        }

    }

}

void Structure::solveConstraints(){
    double beta = 0.1;  // a priori beta=1 ideal mais beta=0.5 limite les potentiels problemes de stabilite
    SymMatrix<bool> Coll(Collisions());
    Vector<Vector2D> Infos(collisionsInfo(Coll));
    if(joints.size()==0 and Infos.size()==0)
        return;

    Friction(Infos,Coll);

    Vector<double> C(constructC(Infos,Coll));
    Vector<double> Q(constructQ());
    Matrix<double> J(constructJ(Infos,Coll));
    Matrix<double> M(constructM());

    Vector<double> E(linSolve(J*M*transpose(J),-J*Q-beta/dt*C));
    // On permet aux objets en collision de seulement s'écarter
    for(long unsigned i=joints.size(); i<E.size(); i++){
        E[i] = min(E[i],0.);
    }
    Vector<double> dV(M*transpose(J)*E);
    double coeff = 1.65;
    for(unsigned long i=0; i<boxes.size(); i++){
        boxes[i].v.x += coeff*dV[3*i];
        boxes[i].v.y += coeff*dV[3*i+1];
        boxes[i].omega += coeff*dV[3*i+2];
    }
    int j;
    for(unsigned long i=0; i<balls.size(); i++){
        j=i+boxes.size();
        balls[i].v.x += coeff*dV[3*j];
        balls[i].v.y += coeff*dV[3*j+1];
        balls[i].omega += coeff*dV[3*j+2];
    }
}
