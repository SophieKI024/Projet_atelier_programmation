#include "tools.h"
#include "box.h"
#include "vehicle.h"
#include "skin.h"
#include "weapon.h"

// ================================== Weapon ===========================================================


Weapon::Weapon(){

}

Weapon::Weapon(Box projectile_){
    ammunition.push_back(projectile_);
}

Weapon::Weapon(Skin machine_, double length_, Vector pos_){
    machine = machine_;
    length = length_;
    pos = pos_;
}

bool Weapon::set_fire(int key, Vector vehicle_pos){
    if (key == KEY_UP){
        Box projectile(pos+vehicle_pos+length*Vector(cos(machine.angle),sin(machine.angle)),4,4,6,BLUE, machine.angle, 180*Vector(cos(machine.angle),sin(machine.angle)),0);
        ammunition.push_back(projectile);
        cout <<"nombre de projectiles : "<<ammunition.size()<<endl;
        return true;
    }
    else{
        return false;
    }
}

void Weapon::Display(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Display();
    }
    machine.Display(pos);
}
void Weapon::Erase(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Erase();
    }
}
void Weapon::Move(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Move();
    }
}
void Weapon::Accelerate(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Accelerate();
    }
}
void Weapon::Collide(Box &b){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Collide(b);
    }
}
Weapon Weapon::copy(){
    Weapon copy;
    for (unsigned long i = 0; i < ammunition.size(); i++){
        copy.ammunition.push_back(ammunition[i]);
    }
    return copy;
}
void Weapon::groundBounce(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].groundBounce();
    }
}
void Weapon::stable(){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        if (ammunition[i].stable){
            ammunition.erase(ammunition.begin()+i);
            cout <<"nombre de projectiles : "<<ammunition.size()<<endl;
            ammunition[i].Erase();
        }
    }
}



