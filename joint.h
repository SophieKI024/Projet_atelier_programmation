#pragma once
#include "vector.h"


///////////////////////////// JOINT /////////////////////////////////

/// Barre rigide
class Joint{
public:
    int type_a, type_b, a, b;
    double l;
    int e;
    Color Col;
    //////////////////////////// CONSTRUCTEURS ////////////////////////////

    /// Constructeur vide
    Joint();
    Joint(int type_a_, int a_, int type_b_, int b_, double l_, int e_, Color Col_);



    //////////////////////////// AFFICHAGE //////////////////////////////////

    /// Affiche la barre
    void Display(Vector2D pos1, Vector2D pos2);

    /// Efface la barre
    void Erase(Vector2D pos1, Vector2D pos2);



    //////////////////////////// PHYSIQUE ////////////////////////////////////

    /// Fonction energie pour la resolution de contraintes
    double C(Vector2D pos1, Vector2D pos2);

    /// Gradient de la fonction energie
    Vector2D J(Vector2D pos1, Vector2D pos2);



    //////////////////////////// AUTRE ////////////////////////////////

    Joint copy();
};

/// Ressort ideal
class Spring{
public:
    int type_a, type_b, a,b;
    double lmin,lmax,l0, k, e0;
    Color Col;

    ////////////////////////// CONSTRUCTEURS ////////////////////////////

    /// Constructeur vide
    Spring();
    Spring(int type_a_, int a_, int type_b_, int b_, double l0_, double lmin_, double lmax_, double k_, double e0_, Color Col_);



    ////////////////////////// AFFICHAGE ////////////////////////////////

    /// Affiche le ressort avec l'epaisseur variant en fonction de l'etirement
    void Display(Vector2D pos1, Vector2D pos2);

    /// Efface le ressort
    void Erase(Vector2D pos1, Vector2D pos2);
};
