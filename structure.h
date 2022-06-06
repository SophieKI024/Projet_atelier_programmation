#pragma once

#include "tools.h"
#include "box.h"
#include "ball.h"
#include "joint.h"
#include "vehicle.h"
#include "liste_des_skins.h"
#include <Imagine/LinAlg.h>
using namespace Imagine;

///////////////// *** STRUCTURE *** ////////////////////////

/// Permet de gerer tous les elements du jeu
class Structure{
public:
    /// Vehicule
    Vehicle car;
    /// Ensemble des rectangles
    vector<Box> boxes;
    /// Ensemble des disques
    vector<Ball> balls;
    /// Ensemble des barres rigides
    vector<Joint> joints;
    /// Ensemble des ressorts
    vector<Spring> springs;
    /// Ensemble des amortisseurs
    vector<Damper> dampers;
    /// Activation de la gravité
    bool gravite = true;

    ////////////////////////////// GESTION INPUTS ////////////////////////////////////////

    /// Gestion du mouvement du vehicule
    void movement_vehicle(vector<int> keys);

    /// Gestion des tirs
    void set_fire(vector<int> keys, Vector2D vehicle_pos, double t);

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

    /// Ajoute un amortisseur
    void add(Damper damp);

    /// Assure que les indices sont bien reajustes lorsqu'on retire un objet
    void removeObject(int type, int i);

    /// Retire un rectangle de la structure
    void removeBox(int i);

    /// Retire un disque de la structure
    void removeBall(int i);

    /// Retire une barre rigide de la structure
    void removeJoint(int i);

    /// Retire un ressort de la structure
    void removeSpring(int i);

    /// Retire un amortisseur de la structure
    void removeDamper(int i);

    ////////////////////////////// ACCESSEURS ////////////////////////////////////////////

    /// Retourne une reference de la position de l'objet correspondant
    Vector2D& getPosition(int type_a, int a);

    /// Retourne une reference de la vitesse de l'objet correspondant
    Vector2D& getSpeed(int type_a, int a);

    /// Retourne une reference de la vitesse angulaire de l'objet correspondant
    double& getOmega(int type_a, int a);

    ///Retourne la masse de l'objet correspondant
    double getMass(int type_a, int a);

    /// Retourne l'angle de l'objet correspondant
    double getAngle(int type_a, int a);

    /// Retourne le moment inertiel de l'objet correspondant
    double getInertialMoment(int type_a, int a);


    ///////////////////////////// AFFICHAGE /////////////////////////////////////////

    /// Affiche la structure
    void Display();

    /// Efface la structure
    void Erase();



    ///////////////////////////// PHYSIQUE ////////////////////////////////////////////

    /// Applique les vitesses a tous les objets pour les deplacer
    void Move(vector<int> keys);

    /// Applique les forces exterieures a tous les objets pour les deplacer
    void Accelerate(vector<int> keys);

    /// Renvoie une matrice de booleen qui indique quels objets sont en collision
    SymMatrix<bool> Collisions();

    /// Renvoie une matrice de vecteurs indiquant les points de contact et les direction pour en sortir
    Vector<Vector2D> collisionsInfo(const SymMatrix<bool>& Coll);

    /// Retourne le vecteur des energies associees au forces de reaction/tension
    Vector<double> constructC(Vector<Vector2D> &Infos,SymMatrix<bool>& Coll);

    /// Retourne le vecteur des vitesses et vitesses de rotation
    Vector<double> constructQ();

    /// Jacobienne dC/dQ
    Matrix<double> constructJ(Vector<Vector2D>& Infos,SymMatrix<bool>& Coll);

    /// Matrice diagonale des inverses des masses et moment inertiels
    Matrix<double> constructM();

    /// Modifie les vitesses et vitesses de rotation pour respecter les contraintes
    void solveConstraints();

    /// Applique les frottements secs
    void Friction(Vector<Vector2D>& Infos, SymMatrix<bool>& Coll, Vector<double> &E);

    /// Detruit les objets qui ont besoin d'être détruits
    void Solve_destruct(Vector<double>& dV, Matrix<double>& M);

    void Explosion(Vector2D pos, double energy = 1e10);



    //////////////////////////////// AUTRES /////////////////////////////////

    /// Copie une structure
    Structure copy();
};
