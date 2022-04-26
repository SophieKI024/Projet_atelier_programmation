#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include<string>
using namespace std;

#include "vector.h"

const double dt = 0.006;
const double g = 10;
const int h_ground = 50;
const int window_width = 1024;
const int window_height = 512;
const int periodDisplay =50;
const double eps=1e-2;

const Color backgroundColor = Color(216,242, 255); // Light Blue

//Déclaration

void drawGround();
int sgn(double a);
void InitRandom();

