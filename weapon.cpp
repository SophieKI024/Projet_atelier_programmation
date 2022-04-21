#include "tools.h"
#include "box.h"
#include "vehicle.h"

#include "weapon.h"

// ================================== Weapon ===========================================================


Weapon::Weapon(){

}

Weapon::Weapon(Box projectile_){
    ammunition.push_back(projectile_);
}

bool Weapon::set_fire(){

    int set_fire = keyboard();
    if (set_fire == KEY_SHIFT){
        cout<<"Feu !"<<endl;
        Box projectile(Vector(150+20,height-h_ground-150),20,20,10,Color(50,50,50), 0, Vector(150,-40),0);
        ammunition.push_back(projectile);
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
            ammunition[i].Erase();
        }
    }
}



