#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"

//Projectile Template

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box wall(Vector(800,height-h_ground-150),100,300,3,Color(140,108,66));
    Box projectile(Vector(150+20,height-h_ground-150),20,20,10,Color(50,50,50), 0, Vector(150,-40),0);
    Weapon cannon;
    Box body(Vector(85,height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body);

    Box old_wall = wall.copy();
    Weapon old_cannon = cannon.copy();
    Vehicle old_car = car.copy();

    wall.Display();
    cannon.Display();
    car.Display();

    drawGround();

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){

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
        cannon.set_fire();

        wall.Accelerate();
        cannon.Accelerate();
        car.Accelerate();

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
