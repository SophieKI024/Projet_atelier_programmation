#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include<string>
using namespace std;

#include "vector.h"

// simulation physique
const double dt = 0.006;
const double g = 10;
const double frottements_fluides = 0.1;
const double frottements_secs = 3e-8;

// affichage
const int h_ground = 50;
const int window_width = 1500;
const int window_height = 800;
const int periodDisplay =50;
const Color backgroundColor = Color(216,242, 255); // Light Blue

const double eps=0.5;

////////////////////////////// GESTION DU CLAVIER ////////////////////////////

/// Rempli le vecteur keys avec les touches actives
void keyboard(vector<int> &keys);

/// Verifie si une touche est active
bool isPressed(vector<int> keys, int key);

////////////////////////////// AUTRES ////////////////////////////////////////

/// Dessine le sol
void drawGround();

/// Renvoie 1 si a>0, -1 si a<0, et 0 si a=0
int sgn(double a);

/// ???
void InitRandom();
