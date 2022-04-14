#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"

const int width = 512;
const int height = 512;
const int periodDisplay =100;

int main() {
    openWindow(300,300);

    // INITIALIZATION
    Box b(Vector(80,80),20,20,1,BLACK,1,Vector(1,0),0.1);
    Box old_b = b.copy();
    b.Display();

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
