#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"
#include "liste_des_skins.h"

//Projectile Template

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box wall(Vector(800,height-h_ground-150),100,300,20,Color(140,108,66));
    Box projectile(Vector(150+20,height-h_ground-150),20,5,10,BLUE, 0, Vector(150,-40),0);
    Weapon cannon(Canon_standard(),30,Vector(0,-50));
    Weapon* arsenal = new Weapon[1];
    arsenal[0]=cannon;
    Box body(Vector(85,height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body,1,arsenal);

    Box old_wall = wall.copy();
    Weapon old_cannon = cannon.copy();
    Vehicle old_car = car.copy();

    wall.Display();
    cannon.Display();
    car.Display();

    drawGround();
    int key;

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        key = keyboard();
        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_wall.Erase();
            old_cannon.Erase();
            old_car.Erase();

            wall.Display();
            cannon.Display();
            car.Display();

            old_wall = wall.copy();
            old_cannon = cannon.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        cannon.set_fire(key,car.body.pos);

        wall.Accelerate();
        cannon.Accelerate();
        car.Accelerate();
        car.movement_vehicle(key);
        car.body.Move();
        wall.Move();
        cannon.Move();
        car.Move();

        cannon.Collide(wall);

        wall.groundBounce();
        cannon.groundBounce();
        car.groundBounce();


        cannon.stable();

        //if(wall.stable and car.stable()) // plus rien ne bouge
            //break;
    }
    cout<<"landing sucessfull"<<endl;
    endGraphics();
    return 0;
}
