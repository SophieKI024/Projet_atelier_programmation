#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include<string>
using namespace std;
#include <iostream>
using namespace std;

#include "vector.h"

// simulation physique
/// pas de temps
const double dt = 0.0015;
/// Constante gravitationelle de pesanteur
const double g = 600;
const double frottements_fluides = 0.2;
const double frottements_secs = 700;

// affichage
const double fps = 30;
const int h_ground = 50;
const int window_width = 1900;
const int window_height = 1000;
const double periodDisplay =1/(fps*dt); // periode d'affichage adaptée
const Color backgroundColor = Color(216,242, 255); // Light Blue
const Color golden_egg = Color(255,215,0);

////////////////////////////// GESTION DU CLAVIER ////////////////////////////

/// Rempli le vecteur keys avec les touches actives
void keyboard(vector<int> &keys);

/// Verifie si une touche est active
bool isPressed(vector<int> keys, int key);

////////////////////////////// AUTRES ////////////////////////////////////////

/// Renvoie 1 si a>0, -1 si a<0, et 0 si a=0
int sgn(double a);

/// Initialise le générateur de nombre aléatoires
void InitRandom();

/// resoud un systeme de Cramer 2*2 et renvoie true ssi il y a une unique solution.
bool solve(double a, double b, double c, double d, double alpha, double beta, double& x, double& y);

/// applique une force à un objet
void applyForceGeneric(Vector2D f, Vector2D p_f, Vector2D pos, Vector2D& v, double& omega, double m, double I);

