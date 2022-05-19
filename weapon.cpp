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

Weapon::Weapon(Skin machine_, double length_, Vector2D pos_, double angle_min_, double angle_max_, double reload_time_, double fire_speed_, double rot_speed_, double r_ball_){
    machine = machine_;
    length = length_;
    pos = pos_;
    angle_min = angle_min_;
    angle_max = angle_max_;
    reload_time = reload_time_;
    t0 =0;
    fire_speed = fire_speed_;
    rot_speed = rot_speed_;
    r_ball = r_ball_;
}

/*
bool Weapon::set_fire(vector<int> keys, Vector2D vehicle_pos, double t){
    if (isPressed(keys,'z') and  (t-t0)>reload_time){
        Box projectile(pos+vehicle_pos+length*Vector2D(cos(machine.angle),sin(machine.angle)),10,10,100,BLACK, machine.angle, 180*Vector2D(cos(machine.angle),sin(machine.angle)),0);
        ammunition.push_back(projectile);
        t0=t;
        return true;
    }
    return false;
}
*/

void Weapon::Display(Vector2D vehicle_pos){
    machine.Display(vehicle_pos + pos);
}

void Weapon::Erase(Vector2D vehicle_pos){
    machine.Erase(vehicle_pos + pos);
}

/*
void Weapon::Collide(Box &b){
    for (unsigned long i = 0; i < ammunition.size(); i++){
        ammunition[i].Collide(b);
    }
}
*/

Weapon Weapon::copy(){
    Weapon copy;
    copy.machine = machine;
    copy.pos = pos;
    copy.length = length;
    return copy;
}

void Weapon::angle_machine(vector<int> keys){
    machine.angle += rot_speed*dt*(isPressed(keys,KEY_DOWN)-isPressed(keys,KEY_UP));
    if (!(machine.angle > angle_max && machine.angle < angle_min))
        machine.angle -= rot_speed*dt*(isPressed(keys,KEY_DOWN)-isPressed(keys,KEY_UP));
}
