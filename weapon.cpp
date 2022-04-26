#include "tools.h"
#include "box.h"
#include "vehicle.h"
#include "skin.h"
#include "weapon.h"

// ===================== Convertir les angles =======================================================================

//Convertir les angles de degrés dans le sens trigo à rad dans le sens horaire
//Origine l'axe des x
double convert_angle(double angle){
    return -angle*M_PI/180.;
}



// ================================== Weapon ===========================================================


Weapon::Weapon(){

}

Weapon::Weapon(Box projectile_){
    ammunition.push_back(projectile_);
}

Weapon::Weapon(Skin machine_, double length_, Vector pos_, double angle_min_, double angle_max_){
    machine = machine_;
    length = length_;
    pos = pos_;
    angle_min = angle_min_;
    angle_max = angle_max_;
}

bool Weapon::set_fire(int key, Vector vehicle_pos){
    if (key == 'z'){
        Box projectile(pos+vehicle_pos+length*Vector(cos(machine.angle),sin(machine.angle)),10,10,100,BLACK, machine.angle, 180*Vector(cos(machine.angle),sin(machine.angle)),0);
        ammunition.push_back(projectile);
        return true;
    }
    return false;
}

void Weapon::Display(Vector vehicle_pos){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Display();
    }
    machine.Display(vehicle_pos + pos);
}
void Weapon::Erase(Vector vehicle_pos){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Erase();
    }
    machine.Erase(vehicle_pos + pos);
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
    copy.machine = machine;
    copy.pos = pos;
    copy.length = length;
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
            ammunition[i].Erase();
        }
    }
}

bool Weapon::raise(int key){
    return key == KEY_UP;
}

bool Weapon::lower(int key){
    return key == KEY_DOWN;
}
void Weapon::angle_machine(int key){
    machine.angle += 0.03*(lower(key)-raise(key));
    if (!(machine.angle > angle_max && machine.angle < angle_min))
        machine.angle -= 0.03*(lower(key)-raise(key));
}
