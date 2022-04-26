#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"
#include "liste_des_skins.h"
#include "structure.h"


int main() {
    openWindow(window_width,window_height);
    setBackGround(backgroundColor);

    // CONTROLS
    cout <<"Utiliser les flèches directionnelles pour bouger le véhicule et controler l'angle du canon, et Z pour tirer"<<endl;

    // INITIALIZATION


    Box wall(Vector(800,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall2(Vector(700,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall3(Vector(750,window_height-h_ground-150-250),150,50,5,Color(140,108,66));

    Structure house(wall);
    house.add(wall2);
    house.add(wall3);

    Weapon* arsenal = new Weapon[1];

    arsenal[0]= Weapon(Canon_standard(),30,Vector(0,-50), convert_angle(0.),convert_angle(180.));

    Box body(Vector(85,window_height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body,1,arsenal);

    Structure old_house = house.copy();
    Vehicle old_car = car.copy();

    house.Display();
    car.Display();

    drawGround();
    vector<int> keys;

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        keyboard(keys);
        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_house.Erase();
            old_car.Erase();

            house.Display();
            car.Display();

            old_house = house.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        car.fire(keys);

        house.Accelerate();
        car.Accelerate();

        car.movement_vehicle(keys);
        //car.angle_machine(key);

        house.Move();
        car.Move();

        car.arsenal_collide(house);
        house.AutoCollide();

        house.groundBounce();
        car.groundBounce();
    }
    endGraphics();
    return 0;
}
