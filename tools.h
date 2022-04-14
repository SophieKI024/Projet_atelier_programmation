#pragma once

#include "vector.h"


//Déclaration des variables
const double dt = 0.01;

//Déclaration des fonctions de tools.cpp

void shock(double x,  double y,  double &vx,  double &vy,  double m,
           double x2, double y2, double &vx2, double &vy2, double m2);


void shockSimple(double x,  double y,  double &vx, double &vy, double m,
                 double x2, double y2, double vx2, double vy2);


bool collision(double x1, double y1, double vx1, double vy1, double r1,
               double x2, double y2, double vx2, double vy2, double r2);
