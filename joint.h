#pragma once
#include "vector.h"


///////////////////////////// JOINT /////////////////////////////////

/// Barre rigide
class Joint{
public:
    /// Type du 1er elt : 0=>Box, 1=>Ball
    int type_a;
    /// Type du 2e elt : 0=>Box, 1=>Ball
    int type_b;
    /// Indice du 1e elt relié
    int a;
    /// Indice du 2e elt relié
    int b;
    /// Position relative du point d'attache du 1er elt
    Vector2D pos_a;
    /// Position relative du point d'attache du 2e elt
    Vector2D pos_b;
    /// Longueur de la barre
    double l;
    /// Epaisseur de la barre
    int e;
    /// Couleur
    Color Col;
    //////////////////////////// CONSTRUCTEURS ////////////////////////////

    /// Constructeur vide
    Joint();
    Joint(int type_a_, int a_, int type_b_, int b_, double l_, int e_, Color Col_, Vector2D pos_a_ = Vector2D(0,0), Vector2D pos_b_ = Vector2D(0,0));



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
    /// Type du 1er elt : 0=>Box, 1=>Ball
    int type_a;
    /// Type du 2e elt : 0=>Box, 1=>Ball
    int type_b;
    /// Indice du 1e elt relié
    int a;
    /// Indice du 2e elt relié
    int b;
    /// Position relative du point d'attache du 1er elt
    Vector2D pos_a;
    /// Position relative du point d'attache du 2e elt
    Vector2D pos_b;
    /// Taille minimale du ressort
    double lmin;
    /// Taille maximale du ressort
    double lmax;
    /// Longueur à vide du ressort
    double l0;
    /// Constante de raideur
    double k;
    /// Epaisseur
    double e0;
    /// Couleur
    Color Col;

    ////////////////////////// CONSTRUCTEURS ////////////////////////////

    /// Constructeur vide
    Spring();
    Spring(int type_a_, int a_, int type_b_, int b_, double l0_, double lmin_, double lmax_, double k_, double e0_, Color Col_, Vector2D pos_a_ = Vector2D(0,0), Vector2D pos_b_ = Vector2D(0,0));



    ////////////////////////// AFFICHAGE ////////////////////////////////

    /// Affiche le ressort avec l'epaisseur variant en fonction de l'etirement
    void Display(Vector2D pos1, Vector2D pos2);

    /// Efface le ressort
    void Erase(Vector2D pos1, Vector2D pos2);
};

/// Amortisseur (généralement associé à un ressort)
class Damper{
public:
    /// Type du 1er elt : 0=>Box, 1=>Ball
    int type_a;
    /// Type du 2e elt : 0=>Box, 1=>Ball
    int type_b;
    /// Indice du 1e elt relié
    int a;
    /// Indice du 2e elt relié
    int b;
    /// Position relative du point d'attache du 1er elt
    Vector2D pos_a;
    /// Position relative du point d'attache du 2e elt
    Vector2D pos_b;
    /// Coefficient d'ammortissement
    double lambda;

    Damper();
    Damper(int type_a_, int a_, int type_b_, int b_,double lambda_,Vector2D pos_a_ = Vector2D(0,0), Vector2D pos_b_ = Vector2D(0,0));
};
