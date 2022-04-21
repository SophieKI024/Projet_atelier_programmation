#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box wall(Vector(800,height-h_ground-150),100,300,1,Color(140,108,66));
    Box projectile(Vector(150+20,height-h_ground-150),20,20,10,Color(50,50,50));
    Box body(Vector(85,height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body);

    Box old_wall = wall.copy();
    Box old_projectile= projectile.copy();
    Vehicle old_car = car.copy();

    wall.Display();
    projectile.Display();
    car.Display();
    drawGround();

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){

        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_wall.Erase();
            old_projectile.Erase();
            old_car.Erase();

            wall.Display();
            projectile.Display();
            car.Display();

            old_wall = wall.copy();
            old_projectile = projectile.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        wall.Accelerate();
        projectile.Accelerate();
        car.Accelerate();

        wall.Move();
        projectile.Move();
        car.Move();

        wall.Collide(projectile);

        wall.groundBounce();
        projectile.groundBounce();
        car.groundBounce();

        if(wall.stable and projectile.stable and car.stable()) // plus rien ne bouge
            break;
    }
    cout<<"landing sucessfull"<<endl;
    endGraphics();
    return 0;
}
