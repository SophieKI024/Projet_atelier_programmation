#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include<string>
using namespace std;

#include "vector.h"

const double dt = 0.006;
const double g = 10;
const int h_ground = 50;
const int window_width = 1500;
const int window_height = 800;
const int periodDisplay =50;
const double eps=1e-2;

const Color backgroundColor = Color(216,242, 255); // Light Blue


const double frottements_fluides = 0.03;
const double frottements_secs = 3e-8;


void keyboard(vector<int> &keys);

bool isPressed(vector<int> keys, int key);


//Déclaration

void drawGround();
int sgn(double a);
void InitRandom();

