#include <cmath>
#include <ctime>
using namespace std;
#include "vector.h"

Vector2D operator* (double a, Vector2D u){
    return u * a;
}

Vector2D rotation(Vector2D v, double angle){
    return Vector2D(cos(angle)*v.x-sin(angle)*v.y, sin(angle)*v.x+cos(angle)*v.y);
}
