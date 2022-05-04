#pragma once

#include "tools.h"
#include "box.h"
#include "ball.h"
#include "joint.h"
#include <Imagine/LinAlg.h>
using namespace Imagine;

class Structure{
public:
    vector<Box> boxes;
    vector<Ball> balls;
    vector<Joint> joints;
    vector<Spring> springs;

    // Constructeur
    Structure();
    Structure(Box box_);
    Structure(vector<Box> boxes_);

    // Fonctions
    void add(Box box);
    void add(Ball ball);
    void add(Joint joint);
    void add(Spring spring);

    Vector2D& getPosition(int type_a, int a);   // donne une reference de la position de l'objet correspondant
    Vector2D& getSpeed(int type_a, int a);      // donne une reference du vecteur vitesse de l'objet correspondant
    double getMass(int type_a, int a);   // donne la masse de l'objet correspondant
    void Display();
    void Erase();
    void Move();
    void Accelerate();
    Vector<double> constructC();     // fonction energie pour l'approche energetique des forces
    Vector<double> constructQ();     // vecteur des vitesses/ vitesse de rotation
    Matrix<double> constructJ();     // Jacobienne
    Matrix<double> constructM();     // Matrice de l'inverse des masses/ moments inertiels
    void solveConstraints();
    void AutoCollide();
    void Collide(Structure& S);
    Structure copy();
    void groundBounce();
};
