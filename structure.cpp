#include "structure.h"

// Constructeurs

Structure::Structure(){
}

Structure::Structure(Box box){
    boxes.push_back(box);
}

Structure::Structure(vector<Box> boxes_){
    for (unsigned long i = 0; i < boxes_.size(); i++){
        boxes.push_back(boxes_[i]);
    }
}

// Fonctions

void Structure::add(Box box){
    boxes.push_back(box);
}


void Structure::Display(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Display();
    }
}
void Structure::Erase(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Erase();
    }
}
void Structure::Move(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Move();
    }
}
void Structure::Accelerate(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].Accelerate();
    }
}

void Structure::AutoCollide(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        for (unsigned long j = 0; j < i; j++){ // On parcourt le triangle strict
                    boxes[i].Collide(boxes[j]);
        }
    }
}

void Structure::Collide(Structure &S){
    for (unsigned long i = 0; i < boxes.size(); i++){
        for (unsigned long j = 0; j < S.boxes.size(); j++){
            boxes[i].Collide(S.boxes[j]);
        }
    }
}
Structure Structure::copy(){
    Structure copy;
    for (unsigned long i = 0; i < boxes.size(); i++){
        copy.boxes.push_back(boxes[i]);
    }
    return copy;
}
void Structure::groundBounce(){
    for (unsigned long i = 0; i < boxes.size(); i++){
        boxes[i].groundBounce();
    }
}
