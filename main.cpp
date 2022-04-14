#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"

int main() {
    openWindow(300,300);
    Box b(Vector(80,80),20,20,1,BLACK,1);
    b.Display();
    endGraphics();
    return 0;
}
