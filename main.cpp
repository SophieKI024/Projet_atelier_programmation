#include <iostream>
using namespace std;
#include "vector.h"
#include "box.h"
#include "tools.h"
#include "vehicle.h"
#include "liste_des_skins.h"
#include "structure.h"
#include "ball.h"


int main() {

    openWindow(window_width,window_height);
    setBackGround(backgroundColor);
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game(Box(Vector2D(x0+500,y0-400),10,10,20,BLUE));
    Weapon* arsenal = new Weapon[1];
    arsenal[0] = Weapon(Canon_standard(),100,Vector2D(0,0), 1000,-1000,0.5,1800,2,15,3);
    game.car = Vehicle(1,arsenal);
    game.add(Ball(Vector2D(x0+400,y0-325),50,3,RED));
    game.add(Ball(Vector2D(x0+600,y0-325),30,3,RED));
    game.add(Spring(0,0,1,0,sqrt(100*100+75*75),0,1000,2e6,5,Color(20,20,20)));
    game.add(Spring(0,0,1,1,sqrt(100*100+75*75),0,1000,2e6,5,Color(20,20,20)));
    game.add(Joint(1,0,1,1,200,5,BLACK));
    game.add(Damper(0,0,1,0,5e4));
    game.add(Damper(0,0,1,1,5e4));

    Box wall1(Vector2D(window_width/2,window_height-50),4000,100,1e100,BLACK);
    Box wall2(Vector2D(0,window_height/2-101),100,window_height,1e100,BLACK);
    Box wall3(Vector2D(window_width,window_height/2-101),100,window_height,1e100,BLACK);
    wall1.gravity=false;
    wall2.gravity=false;
    wall3.gravity=false;
    game.add(wall1);
    game.add(wall2);
    game.add(wall3);

    game.add(Box(Vector2D(300,y0-101),50,200,2,BLUE));
    game.add(Box(Vector2D(500,y0-101),50,200,2,BLUE));
    game.add(Box(Vector2D(400,y0-230),300,50,2,RED));
    game.add(Box(Vector2D(300,y0-360),50,200,2,BLUE));
    game.add(Box(Vector2D(500,y0-360),50,200,2,BLUE));
    game.add(Box(Vector2D(400,y0-490),300,50,2,RED));

    Structure old_game = game.copy();
    game.Display();
    cout<<"periode d'affichage = "<<periodDisplay<<endl;
    cout<<"nombre d'entites : "<<game.boxes.size()+game.balls.size()+game.joints.size()+game.springs.size()<<endl;
    Timer chrono;
    double t=0;
    vector<int> keys;
    click();
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        keyboard(keys);
        if(timeStep%periodDisplay==0){
            game.boxes[0].omega=0;
            game.boxes[0].angle=0;
            double time = chrono.lap();
            noRefreshBegin();

            old_game.Erase();

            game.Display();

            old_game = game.copy();

            noRefreshEnd();
            // on attend exactement ce qu'il faut pour que le jeu s'ecoule a une vitesse coherente
            milliSleep(max(int(1000*(dt*periodDisplay-time)),0));
            chrono.reset();
        }
        game.set_fire(keys,game.boxes[0].pos,t);
        game.Accelerate(keys);
        game.solveConstraints();
        game.Move(keys);
        t+=dt;
    }
    endGraphics();
    return 0;
}
