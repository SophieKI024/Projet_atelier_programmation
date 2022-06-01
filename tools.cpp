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

int sgn(double a){  // renvoie +1 si a>0, -1 si a<0 et 0 si a=0
    return (a>0)-(a<0);
}

void InitRandom(){
    srand((unsigned int) time(0));
}

bool solve(double a, double b, double c, double d, double alpha, double beta, double& x, double& y){
    double det = a*d-b*c;
    if(det==0)
        return false;
    x = (alpha*d-b*beta)/det;
    y = (a*beta-alpha*c)/det;
    return true;
}
