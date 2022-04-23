#include "liste_des_skins.h"

void Symmetry(Vector* border, int nb_points){
    for(int i=0; i<nb_points/2; i++){
        border[nb_points/2+i].x = border[nb_points/2-i-1].x;
        border[nb_points/2+i].y = -border[nb_points/2-i-1].y;
    }
}

Skin Canon_standard(){
    Vector* border_=new Vector[14];

    border_[0] = Vector(-1,0.5);
    border_[1] = Vector(0,1);
    border_[2] = Vector(1,0.5);
    border_[3] = Vector(3,0.5);
    border_[4] = Vector(3.5,1);
    border_[5] = Vector(4,0.5);
    border_[6] = Vector(4.5,0.5);
    Symmetry(border_,14);

    return Skin(border_,14,Color(50,50,50),20,-0.4);
}
