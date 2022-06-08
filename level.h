#pragma once
#include "tools.h"
#include "structure.h"

///////////////// *** PLAY *** ////////////////////////
void play(Structure& game);

////////////////*** CONSTRUCTION *** /////////////////////

/// Ajoute une pyramide pleine
void addPyramid(Structure& game, double x0, double y0, double w, double h, double espacement, int taille);

/// Ajoute une pyramide vide
void addPyramid2(Structure& game, double x0, double y0, double w, double h, double espacement, int taille);

/// Ajoute une tour
void addTower(Structure& game, double x0, double y0, double w, double h, double espacement, int taille);

///////////////// *** LEVELS *** ////////////////////////

/// Demo des capacités du moteur physique (Balls)
Structure demoBall();

/// Demo des capacités du moteur physique (Structures)
Structure demoStructure();

Structure level_1();
Structure level_2();
Structure level_3();
Structure level_4();
Structure level_5();

Structure title_screen(bool& stop);
Structure Pontstructor(int choix);
Structure selector();

