#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"
#include "liste_des_skins.h"


int main() {
    openWindow(window_width,window_height);
    setBackGround(backgroundColor);

    // CONTROLS
    cout <<"Utiliser les flèches directionnelles pour bouger le véhicule et controler l'angle du canon, et Z pour tirer"<<endl;

    // INITIALIZATION
    Box wall(Vector(800,window_height-h_ground-150),100,300,20,Color(140,108,66));
    Weapon* arsenal = new Weapon[1];
    arsenal[0]= Weapon(Canon_standard(),30,Vector(0,-50));
    Box body(Vector(85,window_height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body,1,arsenal);

    Box old_wall = wall.copy();
    Vehicle old_car = car.copy();

    wall.Display();
    car.Display();

    drawGround();
    vector<int> keys;

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        keyboard(keys);
        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_wall.Erase();
            old_car.Erase();

            wall.Display();
            car.Display();

            old_wall = wall.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        car.fire(keys);

        wall.Accelerate();
        car.Accelerate();

        car.movement_vehicle(keys);
        //car.angle_machine(key);

        wall.Move();
        car.Move();

        car.arsenal_collide(wall);

        wall.groundBounce();
        car.groundBounce();

    }
    endGraphics();
    return 0;
}
