#include "tools.h"

/////////////////////////////// GESTION CLAVIER ///////////////////////////////////


void keyboard(vector<int>& keys){
        Event e;
        do {
            bool deja_vu;
            int j;
            getEvent(0,e);

            if(e.type==EVT_KEY_ON){
                deja_vu = false;
                for(unsigned long i=0; i<keys.size() and !deja_vu;i++){
                    deja_vu = keys[i]==e.key;
                }
                if(!deja_vu)
                    keys.push_back(e.key);
             }

            if(e.type==EVT_KEY_OFF){

                j=0;
                while(j<keys.size()){
                    if (keys[j]==e.key){
                        swap(keys[j],keys.back());
                        keys.pop_back();
                    }
                    else
                        j++;
                }
            }

        } while(e.type!=EVT_NONE);
}

bool isPressed(vector<int> keys, int key){
    for(unsigned long i=0; i<keys.size();i++){
        if(keys[i]==key){
            return true;
        }
    }
    return false;
}


/////////////////////////////// FONCTIONS UTILES/////////////////////////////////


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
