#pragma once

#include "tools.h"
#include "box.h"
#include "ball.h"
#include "joint.h"
#include <Imagine/LinAlg.h>
using namespace Imagine;


///////////////// *** STRUCTURE *** ////////////////////////

/// Permet de gerer tous les elements du jeu
class Structure{
public:
    vector<Box> boxes;
    vector<Ball> balls;
    vector<Joint> joints;
    vector<Spring> springs;

    /////////////////////////////// CONSTRUCTEURS ////////////////////////////////////////

    /// Constructeur vide
    Structure();

    Structure(Box box_);

    Structure(vector<Box> boxes_);



    ////////////////////////////// AJOUT D'ELEMENTS ///////////////////////////////////////

    /// Ajoute un rectangle a la structure
    void add(Box box);

    /// Ajoute un disque a la structure
    void add(Ball ball);

    /// Ajoute une barre rigide a la structure
    void add(Joint joint);

    /// Ajoute un ressort a la structure
    void add(Spring spring);



    ////////////////////////////// ACCESSEURS ////////////////////////////////////////////

    /// Retourne une reference de la position de l'objet correspondant
    Vector2D& getPosition(int type_a, int a);

    /// Retourne une reference de la vitesse de l'objet correspondant
    Vector2D& getSpeed(int type_a, int a);

    ///Retourne la masse de l'objet correspondant
    double getMass(int type_a, int a);



    ///////////////////////////// AFFICHAGE /////////////////////////////////////////

    /// Affiche la structure
    void Display();

    /// Efface la structure
    void Erase();



    ///////////////////////////// PHYSIQUE ////////////////////////////////////////////

    /// Applique les vitesses a tous les objets pour les deplacer
    void Move();

    /// Applique les forces exterieures a tous les objets pour les deplacer
    void Accelerate();

    /// Effectue les collisions internes
    void AutoCollide();

    /// Effectue les collisions avec une autre structure
    void Collide(Structure& S);

    /// Effectue les collisions avec le sol
    void groundBounce();

    /// Renvoie une matrice de booleen qui indique quels objets sont en collision
    SymMatrix<bool> Collisions();

    /// Renvoie une matrice de vecteurs indiquant les points de contact et les direction pour en sortir
    Vector<Vector2D> collisionsInfo(const SymMatrix<bool>& Coll);

    /// Retourne le vecteur des energies associees au forces de reaction/tension
    Vector<double> constructC(Vector<Vector2D> &Infos);

    /// Retourne le vecteur des vitesses et vitesses de rotation
    Vector<double> constructQ();

    /// Jacobienne dC/dQ
    Matrix<double> constructJ(Vector<Vector2D>& Infos,SymMatrix<bool>& Coll);

    /// Matrice diagonale des inverses des masses et moment inertiels
    Matrix<double> constructM();

    /// Modifie les vitesses et vitesses de rotation pour respecter les contraintes
    void solveConstraints();



    //////////////////////////////// AUTRES /////////////////////////////////

    /// Copie une structure
    Structure copy();
};
