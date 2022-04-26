
#include "tools.h"

void drawGround(){
    fillRect(0,window_height-h_ground,window_width,h_ground,Color(88,41,0));
    fillRect(0,window_height-h_ground,window_width,h_ground/3,Color(107,202,35));
}

int sgn(double a){  // renvoie +1 si a>0, -1 si a<0 et 0 si a=0
    return (a>0)-(a<0);
}

void InitRandom(){
    srand((unsigned int) time(0));
}
