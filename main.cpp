#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box b(Vector(400,100),40,60,100,BLACK,1,Vector(20,-25),0.8);
    Box old_b = b.copy();
    b.Display();
    drawGround();

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){

        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();
            old_b.Erase();
            b.Display();
            old_b = b.copy();
            noRefreshEnd();
            milliSleep(20);
        }

        b.Accelerate();
        b.Move();
    }

    endGraphics();
    return 0;
}
