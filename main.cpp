#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"

int main() {
    openWindow(width,height);

    // INITIALIZATION
    Box b(Vector(800,height-h_ground-150),100,300,1,Color(140,108,66));
    Box b2(Vector(0,height-h_ground-150),20,20,10,Color(50,50,50),0,Vector(150,-40),0);
    Box old_b = b.copy();
    Box old_b2= b2.copy();
    b.Display();
    b2.Display();
    drawGround();

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){

        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();
            old_b.Erase();
            old_b2.Erase();
            b.Display();
            b2.Display();
            old_b = b.copy();
            old_b2 = b2.copy();
            noRefreshEnd();
            milliSleep(20);
        }

        b.Accelerate();
        b2.Accelerate();
        b.Move();
        b2.Move();
        b.Collide(b2);
        b.groundBounce();
        b2.groundBounce();
        if(b.stabile and b2.stabile) // plus rien ne bouge
            break;
    }
    cout<<"landing sucessfull"<<endl;
    endGraphics();
    return 0;
}
