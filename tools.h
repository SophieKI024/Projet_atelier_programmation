#ifndef TOOLS_H
#define TOOLS_H

#endif // TOOLS_H
#pragma once

#include <Imagine/Graphics.h>
using namespace Imagine;
#include<string>
using namespace std;

#include "vector.h"

const double dt = 0.003;
const double g = 1;
const int h_sol = 20;

struct Ball {
    Vector pos;
    Vector vitesse;
    double rayon;
    Color col;
    double masse;

    Ball (Vector pos_, Vector vitesse_, double rayon_, Color col_, double masse_){
        pos = pos_; vitesse = vitesse_; rayon = rayon_; col = col_; masse = masse_;
    }

    Ball () {
        Ball(Vector(), Vector(), 0, WHITE, 0);
    }

    void display(){
        fillCircle(int(pos.x), int(pos.y), int(rayon), col);
    }

    void erase(){
        fillCircle(int(pos.x), int(pos.y), int(rayon), WHITE);
    }

    Ball copy() {
        return Ball(pos, vitesse, rayon, col, masse);
    }

};

//Déclaration

void InitRandom();
void shock(double x,  double y,  double &vx,  double &vy,  double m, double x2, double y2, double &vx2, double &vy2, double m2);
void shock(Ball &D, Ball &S);
void shockSimple(double x,  double y,  double &vx, double &vy, double m, double x2, double y2, double vx2, double vy2);
void shockSimple(Ball &D, Ball S);
bool collision(double x1, double y1, double vx1, double vy1, double r1, double x2, double y2, double vx2, double vy2, double r2, float dt);
bool collision(Ball &D, Ball &S, float dt);
void Gravitation(Ball sun, Ball &D, int G, double dt);
void Gravitation_bis(Ball &sun, Ball &D, int G, double dt);
void Display_tour(int tour, string nom_joueur_1, string nom_joueur_2, int width, int height);
void Soleils(int nbSoleils, Ball soleils[], Ball super_sun, Ball Joueur_1, Ball Joueur_2, int width, int height);
