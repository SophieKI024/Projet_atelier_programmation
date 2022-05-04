#include "liste_des_skins.h"

void Symmetry(Vector2D* border, int nb_points){
    for(int i=0; i<nb_points/2; i++){
        border[nb_points/2+i].x = border[nb_points/2-i-1].x;
        border[nb_points/2+i].y = -border[nb_points/2-i-1].y;
    }
}

Skin Canon_standard(){
    Vector2D* border_=new Vector2D[14];

    border_[0] = Vector2D(-1,0.5);
    border_[1] = Vector2D(0,1);
    border_[2] = Vector2D(1,0.5);
    border_[3] = Vector2D(3,0.5);
    border_[4] = Vector2D(3.5,1);
    border_[5] = Vector2D(4,0.5);
    border_[6] = Vector2D(4.5,0.5);
    Symmetry(border_,14);

    return Skin(border_,14,Color(50,50,50),20,-0.4);
}

Skin Gros_canon(){
    Vector2D* border_=new Vector2D[16];

    border_[0] = Vector2D(-1.5,1.5);
    border_[1] = Vector2D(-0.25,2.5);
    border_[2] = Vector2D(0.25,2.5);
    border_[3] = Vector2D(1.5,1.5);
    border_[4] = Vector2D(3,1.5);
    border_[5] = Vector2D(3.5,2);
    border_[6] = Vector2D(4,1.5);
    border_[7] = Vector2D(4.5,1.5);
    Symmetry(border_,16);

    return Skin(border_,16,Color(220,20,60),20,-0.4);
}
