#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box b(Vector(80,80),20,20,1,BLACK,1,Vector(1,0),0.1);
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
            milliSleep(50);
        }

        b.Accelerate();
        b.Move();
    }

    endGraphics();
    return 0;
}
