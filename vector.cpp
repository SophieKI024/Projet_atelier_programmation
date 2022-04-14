#include <cmath>
using namespace std;
#include "vector.h"

Vector operator+(Vector a, Vector b){ //
    Vector sum = {a.x+b.x, a.y+b.y};
    return sum;
}

Vector operator-(Vector a, Vector b){
    Vector diff = {a.x-b.x, a.x-b.x};
    return diff;
}

double norm2(Vector a){
    return pow(pow(a.x,2) + pow(a.y,2),0.5);
}

Vector operator*(Vector a, double lambda){
    Vector u = {lambda*a.x , lambda*a.y};
    return u;
}

Vector operator*(double lambda, Vector a){
    return a*lambda;
}
