#include "structure.h"
#include "vector.h"
#include <Imagine/LinAlg.h>

using namespace Imagine;
using namespace std;

///////////////// *** STRUCTURE *** ////////////////////////

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
    double dir = isPressed(keys,KEY_RIGHT)-isPressed(keys,KEY_LEFT);
    for(long unsigned i=0; i<car.i_wheels.size(); i++){
        Ball& wheel = balls[car.i_wheels[i]];
        wheel.omega += dt*car.power*(car.v_max-wheel.omega*wheel.r*dir)*dir/(wheel.r*car.v_max);
    }
}

void Structure::set_fire(vector<int> keys, Vector2D vehicle_pos, double t){
    Vector2D v,pos;
    for (int i=0; i<car.nb_weapons; i++){
        if (isPressed(keys,'z') and  (t-car.arsenal[i].t0)>car.arsenal[i].reload_time){
            Weapon& w = car.arsenal[i];
            v = w.fire_speed*rotation(Vector2D(cos(w.machine.angle),sin(w.machine.angle)),boxes[0].angle);
            pos = rotation(w.pos+w.length*Vector2D(cos(w.machine.angle),sin(w.machine.angle)),boxes[0].angle)+vehicle_pos;
            Ball b(pos,w.r_ball,w.m_ball/(M_PI*w.r_ball*w.r_ball),BLACK,v,0);
            b.breaking_energy = 0;
            add(b);
            car.arsenal[i].t0=t;
            boxes[0].v -= w.m_ball/boxes[0].m*v;
            boxes[0].omega -= rotation(v,-M_PI/2)*(pos-vehicle_pos)*w.m_ball/boxes[0].I();
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

void Structure::removeObject(int type, int i){
    int size = boxes.size()*(1-type)+balls.size()*type;
    long unsigned j=0;
    while(j<joints.size()){

        // on supprime les barres qui etaient relies a l'objet a supprimer
        if((joints[j].type_a==type and joints[j].a==i) or (joints[j].type_b==type and joints[j].b==i)){
            removeJoint(j);
            j--;
        }

        // on change les indices des barres reliees au dernier objet
        else{
            if((joints[j].type_a==type and joints[j].a==size))
                joints[j].a=i;
            if((joints[j].type_b==type and joints[j].b==size))
                joints[j].b=i;
        }
        j++;
    }

    // idem pour les ressorts
    j=0;
    while(j<springs.size()){

        // on supprime les ressorts qui etaient relies a la boite a supprimer
        if((springs[j].type_a==type and springs[j].a==i) or (springs[j].type_b==type and springs[j].b==i)){
            removeSpring(j);
            j--;
        }

        // on change les indices des ressorts reliees a la derniere Box
        else{
            if((springs[j].type_a==type and springs[j].a==size))
                springs[j].a=i;
            if((springs[j].type_b==type and springs[j].b==size))
                springs[j].b=i;
        }
        j++;
    }

    // idem pour les amortisseurs
    j=0;
    while(j<dampers.size()){

        // on supprime les ressorts qui etaient relies a la boite a supprimer
        if((dampers[j].type_a==type and dampers[j].a==i) or (dampers[j].type_b==type and dampers[j].b==i)){
            removeDamper(j);
            j--;
        }

        // on change les indices des ressorts reliees a la derniere Box
        else{
            if((dampers[j].type_a==type and dampers[j].a==size))
                dampers[j].a=i;
            if((dampers[j].type_b==type and dampers[j].b==size))
                dampers[j].b=i;
        }
        j++;
    }
}

void Structure::removeBox(int i){
    if(i>=int(boxes.size())){
        cout<<"WARNING : trying to remove a non existent Box"<<endl;
        return;
    }
    swap(boxes.back(),boxes[i]);
    boxes.pop_back();
    removeObject(0,i);
}

void Structure::removeBall(int i){
    if(i>=int(balls.size())){
        cout<<"WARNING : trying to remove a non existent Ball"<<endl;
        return;
    }
    swap(balls.back(),balls[i]);
    balls.pop_back();
    removeObject(1,i);
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

double& Structure::getOmega(int type_a, int a){
    if(type_a == 0)
        return boxes[a].omega;
    else
        return balls[a].omega;
}

double Structure::getAngle(int type_a, int a){
    if(type_a ==0)
        return boxes[a].angle;
    else
        return balls[a].angle;
}


double Structure::getInertialMoment(int type_a, int a){
    if(type_a ==0)
        return boxes[a].I();
    else
        return balls[a].I();
}


double Structure::getMass(int type_a, int a){
    if(type_a == 0)
        return boxes[a].m;
    else
        return balls[a].m;
}

void Structure::Display(){
    Vector2D pos1,pos2;
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Display(scale,scroll);
    }
    for (unsigned long i = 0; i < balls.size(); i++){
        balls[i].Display(scale,scroll);
    }
    for (unsigned long i = 0; i < joints.size(); i++){
        pos1 = getPosition(joints[i].type_a,joints[i].a)+ rotation(joints[i].pos_a,getAngle(joints[i].type_a,joints[i].a));
        pos2 = getPosition(joints[i].type_b,joints[i].b)+ rotation(joints[i].pos_b,getAngle(joints[i].type_b,joints[i].b));
        joints[i].Display(pos1,pos2,scale,scroll);
    }
    for (unsigned long i = 0; i < springs.size(); i++){
        pos1 = getPosition(springs[i].type_a,springs[i].a)+ rotation(springs[i].pos_a,getAngle(springs[i].type_a,springs[i].a));
        pos2 = getPosition(springs[i].type_b,springs[i].b)+ rotation(springs[i].pos_b,getAngle(springs[i].type_b,springs[i].b));
        springs[i].Display(pos1,pos2,scale,scroll);
    }
    // affiche les armes
    car.Display(boxes[0].pos,boxes[0].angle,scale,scroll);
}


void Structure::Erase(){
    Vector2D pos1, pos2;
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Erase(scale,scroll);
    }
    for (unsigned long i = 0; i < balls.size(); i++){
        balls[i].Erase(scale,scroll);
    }
    for (unsigned long i = 0; i < joints.size(); i++){
        pos1 = getPosition(joints[i].type_a,joints[i].a)+ rotation(joints[i].pos_a,getAngle(joints[i].type_a,joints[i].a));
        pos2 = getPosition(joints[i].type_b,joints[i].b)+ rotation(joints[i].pos_b,getAngle(joints[i].type_b,joints[i].b));
        joints[i].Erase(pos1,pos2,scale,scroll);
    }
    for (unsigned long i = 0; i < springs.size(); i++){
        pos1 = getPosition(springs[i].type_a,springs[i].a)+ rotation(springs[i].pos_a,getAngle(springs[i].type_a,springs[i].a));
        pos2 = getPosition(springs[i].type_b,springs[i].b)+ rotation(springs[i].pos_b,getAngle(springs[i].type_b,springs[i].b));
        springs[i].Erase(pos1,pos2,scale,scroll);
    }
    car.Erase(boxes[0].pos,boxes[0].angle,scale,scroll);
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
    if(gravite){
        for (unsigned long i = 0; i < boxes.size(); i++){
            boxes[i].Accelerate();
        }
        for(unsigned long i=0; i<balls.size();i++){
            balls[i].Accelerate();
        }
    }

    Vector2D pos1,pos2,f1,f2,p_f1,p_f2,dir,delta_v;
    double m1,m2,I1,I2;

    // effet des ressorts
    for(unsigned long i=0; i<springs.size(); i++){
        Spring& S = springs[i];
        pos1 = getPosition(S.type_a,S.a);
        pos2 = getPosition(S.type_b,S.b);
        p_f1 = pos1 + rotation(S.pos_a,getAngle(S.type_a,S.a));
        p_f2 = pos2 + rotation(S.pos_b,getAngle(S.type_b,S.b));;
        m1 = getMass(S.type_a,S.a);
        m2 = getMass(S.type_b,S.b);
        I1 = getInertialMoment(S.type_a,S.a);
        I2 = getInertialMoment(S.type_b,S.b);
        Vector2D& v1 = getSpeed(S.type_a,S.a);
        Vector2D& v2 = getSpeed(S.type_b,S.b);
        double& omega1 = getOmega(S.type_a,S.a);
        double& omega2 = getOmega(S.type_b,S.b);
        // f1 = -k*(l-l0)*e21
        f1 = -S.k*((pos1-pos2).norme()-S.l0)*(pos1-pos2).normalize();
        f2 = -1*f1;
        applyForceGeneric(f1,p_f1,pos1,v1,omega1,m1,I1);
        applyForceGeneric(f2,p_f2,pos2,v2,omega2,m2,I2);
    }

    // mouvement du vehicule
    movement_vehicle(keys);

    // effet des amortisseurs
    for(unsigned long i=0; i<dampers.size(); i++){
        Damper& D = dampers[i];
        pos1 = getPosition(D.type_a,D.a);
        pos2 = getPosition(D.type_b,D.b);
        p_f1 = pos1 + rotation(D.pos_a,getAngle(D.type_a,D.a));
        p_f2 = pos2 + rotation(D.pos_b,getAngle(D.type_b,D.b));;
        m1 = getMass(D.type_a,D.a);
        m2 = getMass(D.type_b,D.b);
        I1 = getInertialMoment(D.type_a,D.a);
        I2 = getInertialMoment(D.type_b,D.b);
        Vector2D& v1 = getSpeed(D.type_a,D.a);
        Vector2D& v2 = getSpeed(D.type_b,D.b);
        double& omega1 = getOmega(D.type_a,D.a);
        double& omega2 = getOmega(D.type_b,D.b);
        dir = (p_f2-p_f1).normalize();
        delta_v = (v1+omega1*rotation(p_f1-pos1,M_PI/2)-v2-omega2*rotation(p_f2-pos2,M_PI/2))*dir*dir;
        f1 = -D.lambda*delta_v;
        f2 = -1*f1;
        applyForceGeneric(f1,p_f1,pos1,v1,omega1,m1,I1);
        applyForceGeneric(f2,p_f2,pos2,v2,omega2,m2,I2);
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
    copy.scale = scale;
    copy.scroll = scroll;

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
    Vector2D pos1,pos2;
    for(unsigned long i=0; i<joints.size(); i++){
        pos1 = getPosition(joints[i].type_a,joints[i].a) + rotation(joints[i].pos_a,getAngle(joints[i].type_a,joints[i].a));
        pos2 = getPosition(joints[i].type_b,joints[i].b) + rotation(joints[i].pos_b,getAngle(joints[i].type_b,joints[i].b));
        C[i] = 0.8*joints[i].C(pos1,pos2);
    }
    int n=0;
    for(unsigned long i=0; i<boxes.size()+balls.size(); i++){
        for(unsigned long j=i+1; j<boxes.size()+balls.size(); j++){
            if(Coll(i,j)){
                C[n+joints.size()] = 1.2*Infos[2*n+1].norme();
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
    Vector2D pos1, pos2 , OM1,OM2, dir,r1,r2;
    int i1,i2;
    for(unsigned long i=0; i<joints.size(); i++){
        pos1 = getPosition(joints[i].type_a,joints[i].a) + rotation(joints[i].pos_a,getAngle(joints[i].type_a,joints[i].a));
        pos2 = getPosition(joints[i].type_b,joints[i].b) + rotation(joints[i].pos_b,getAngle(joints[i].type_b,joints[i].b));
        OM1 = rotation(joints[i].pos_a,getAngle(joints[i].type_a,joints[i].a));
        OM2 = rotation(joints[i].pos_b,getAngle(joints[i].type_b,joints[i].b));
        i1 = joints[i].type_a*boxes.size()+joints[i].a;
        i2 = joints[i].type_b*boxes.size()+joints[i].b;
        dir = (pos1-pos2).normalize();
        J(i,3*i1) = dir.x;
        J(i,3*i1+1) = dir.y;
        J(i,3*i1+2) = dir*rotation(OM1,M_PI/2);
        J(i,3*i2) = -dir.x;
        J(i,3*i2+1) = -dir.y;
        J(i,3*i2+2) = -(dir*rotation(OM2,M_PI/2));
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

void Structure::Friction(Vector<Vector2D>& Infos, SymMatrix<bool>& Coll, Vector<double>& E){
    Vector2D f,p_f,N,t,v1,v2;
    double seuil;
    double coeff = 0.7;
    int n=0;
    for(unsigned long i=0; i<boxes.size(); i++){
        for(unsigned long j=i+1; j<boxes.size(); j++){
            if(Coll(i,j)){
                Box& b1 = boxes[i];
                Box& b2 = boxes[j];
                p_f = Infos[2*n];
                t = rotation(Infos[2*n+1].normalize(),-M_PI/2);
                v1 = (b1.v+b1.omega*rotation(p_f-b1.pos,M_PI/2))*t*t;
                v2 = (b2.v+b2.omega*rotation(p_f-b2.pos,M_PI/2))*t*t;
                seuil = 1/b1.m+1/b2.m+pow(N*(p_f-b1.pos),2)/b1.I()+pow(N*(p_f-b2.pos),2)/b2.I();
                f  = min(-b1.friction*b2.friction*E[n+joints.size()],coeff*(v1-v2).norme()/(dt*seuil))*(v2-v1).normalize();
                b1.applyForce(f,p_f);
                b2.applyForce(-1*f,p_f);
                n++;
            }
        }
        for(unsigned long j=0; j<balls.size(); j++){
            if(Coll(i,j+boxes.size())){
                Box& b1 = boxes[i];
                Ball& b2 = balls[j];
                p_f = Infos[2*n];
                N = Infos[2*n+1].normalize();
                t = rotation(N,-M_PI/2);
                v1 = (b1.v+b1.omega*rotation(p_f-b1.pos,M_PI/2))*t*t;
                v2 = (b2.v+b2.omega*rotation(p_f-b2.pos,M_PI/2))*t*t;
                seuil = 1/b1.m+1/b2.m+pow(N*(p_f-b1.pos),2)/b1.I()+pow(N*(p_f-b2.pos),2)/b2.I();
                f  = min(-b1.friction*b2.friction*E[n+joints.size()],coeff*(v1-v2).norme()/(dt*seuil))*(v2-v1).normalize();
                b1.applyForce(f,p_f);
                b2.applyForce(-1*f,p_f);
                n++;
            }
        }
    }
    for(unsigned long i=0; i<balls.size(); i++){
        for(unsigned long j=i+1; j<balls.size(); j++){
            if(Coll(i+boxes.size(),j+boxes.size())){
                Ball& b1 = balls[i];
                Ball& b2 = balls[j];
                p_f = Infos[2*n];
                t = rotation(Infos[2*n+1].normalize(),-M_PI/2);
                v1 = (b1.v+b1.omega*rotation(p_f-b1.pos,M_PI/2))*t*t;
                v2 = (b2.v+b2.omega*rotation(p_f-b2.pos,M_PI/2))*t*t;
                seuil = 1/b1.m+1/b2.m+pow(N*(p_f-b1.pos),2)/b1.I()+pow(N*(p_f-b2.pos),2)/b2.I();
                f  = min(-b1.friction*b2.friction*E[n+joints.size()],coeff*(v1-v2).norme()/(dt*seuil))*(v2-v1).normalize();
                b1.applyForce(f,p_f);
                b2.applyForce(-1*f,p_f);
                n++;
            }
        }

    }
}

void Structure::Solve_destruct(Vector<double> &dV, Matrix<double>& M){
    Vector<bool> Destruct(boxes.size()+balls.size());
    Destruct.fill(false);
    double energie, energie_seuil;
    for(long unsigned i=0; i<boxes.size()+balls.size(); i++){
        energie = 0;
        for (int j=0; j<3; j++){
            energie += 0.5*pow(dV[3*i+j],2)/M(3*i+j,3*i+j);
        }
        if(i<boxes.size())
            energie_seuil = boxes[i].breaking_energy;
        else
            energie_seuil = balls[i-boxes.size()].breaking_energy;
        Destruct[i] = energie > energie_seuil;
    }
    for(int i=Destruct.size()-1; i>=0; i--){
        if(Destruct[i]){
            if(i>=int(boxes.size()))
                removeBall(i-boxes.size());
            else
                removeBox(i);
        }
    }
}

void Structure::solveConstraints(){
    double beta = 1;  // a priori beta=1 ideal mais beta=0.5 limite les potentiels problemes de stabilite
    SymMatrix<bool> Coll(Collisions());
    Vector<Vector2D> Infos(collisionsInfo(Coll));
    if(joints.size()==0 and Infos.size()==0)
        return;

    Vector<double> C(constructC(Infos,Coll));
    Vector<double> Q(constructQ());
    Matrix<double> J(constructJ(Infos,Coll));
    Matrix<double> M(constructM());

    Matrix<double> Sol(pseudoInverse(J*M*transpose(J)));
    Vector<double> E1(Sol*(-J*Q));
    // On permet aux objets en collision de seulement s'écarter
    for(long unsigned i=joints.size(); i<E1.size(); i++){
        E1[i] = min(E1[i],0.);
    }

    Vector<double> dV(M*transpose(J)*E1);
    Vector<double> dQ(-beta*M*transpose(J)*Sol*C);
    double coeff = 1.6;
    for(unsigned long i=0; i<boxes.size(); i++){
        boxes[i].v.x += coeff*dV[3*i];
        boxes[i].v.y += coeff*dV[3*i+1];
        boxes[i].omega += coeff*dV[3*i+2];
        boxes[i].pos.x += dQ[3*i];
        boxes[i].pos.y += dQ[3*i+1];
        boxes[i].angle += dQ[3*i+2];
    }
    int j;
    for(unsigned long i=0; i<balls.size(); i++){
        j=i+boxes.size();
        balls[i].v.x += coeff*dV[3*j];
        balls[i].v.y += coeff*dV[3*j+1];
        balls[i].omega += coeff*dV[3*j+2];
        balls[i].pos.x += dQ[3*j];
        balls[i].pos.y += dQ[3*j+1];
        balls[i].angle += dQ[3*j+2];
    }
    Friction(Infos,Coll,E1);
    Solve_destruct(dV,M);
}

void Structure::Explosion(Vector2D pos, double energy){
    Vector2D r,dv;
    for(unsigned long i=0; i<boxes.size(); i++){
        Box& b = boxes[i];
        r = b.minimalDistance(pos);
        if(r.norme()>1e-2){
            dv = energy/r.norme2()*r.normalize();
            dv = dv.normalize()*min(0.04*energy,dv.norme());// on limite la force de l'explosion
            b.v += 1/b.m*dv;
            b.omega += 1/b.I()*dv*(r+pos-b.pos);
        }
    }
    for(unsigned long i=0; i<balls.size(); i++){
        Ball& b = balls[i];
        r = (b.pos-pos);
        if(r.norme()>1e-2){
            dv = energy/r.norme2()*r.normalize();
            dv = dv.normalize()*min(0.04*energy,dv.norme());
            b.v += 1/b.m*dv;
        }
    }
}
