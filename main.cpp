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
    Structure game(Box(Vector2D(x0,y0-50),300,60,10,BLUE));
    Weapon* arsenal = new Weapon[1];
    arsenal[0] = Weapon(Canon_standard(),30,Vector2D(0,-50), convert_angle(0.),convert_angle(180.),1);
    game.car = Vehicle(1,arsenal);
    //game.add(Box(Vector2D(x0-100,y0-130),60,200,10,RED));
    //game.add(Box(Vector2D(x0+100,y0-130),60,200,10,RED));

    for(int i=0; i<8; i++){
        for(int j=0; j<12; j++){
            game.add(Ball(Vector2D(200+60*j,60*i),20+rand()%5,0.1,Color(rand()%255,rand()%255, rand()%255),Vector2D(rand()%200,rand()%200)));
        }
    }

    Structure old_game = game.copy();
    game.Display();
    //fillCircle(100,y0,r0,RED);
    Box wall1(Vector2D(window_width/2,window_height-50),4000,100,1e100,BLACK);
    Box wall2(Vector2D(0,window_height/2-101),100,window_height,1e100,BLACK);
    Box wall3(Vector2D(window_width,window_height/2-101),100,window_height,1e100,BLACK);
    wall1.gravity=false;
    wall2.gravity=false;
    wall3.gravity=false;
    game.add(wall1);
    game.add(wall2);
    game.add(wall3);

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
    /*
    // CONTROLS
    cout <<"Utiliser les flèches directionnelles pour bouger le véhicule et controler l'angle du canon, et Z pour tirer"<<endl;

    // INITIALIZATION


    Box wall(Vector2D(800,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall2(Vector2D(700,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall3(Vector2D(750,window_height-h_ground-150-250),150,50,5,Color(140,108,66));

    Structure game(wall);
    game.add(wall2);
    game.add(wall3);

    Weapon* arsenal = new Weapon[1];

    arsenal[0]= Weapon(Canon_standard(),30,Vector2D(0,-50), convert_angle(0.),convert_angle(180.),1);

    Box body(Vector2D(85,window_height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body,1,arsenal);

    Structure old_game = game.copy();
    Vehicle old_car = car.copy();

    game.Display();
    car.Display();

    drawGround();
    vector<int> keys;
    double t=0;

    // MAIN LOOP
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        keyboard(keys);
        // DISPLAY
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_game.Erase();
            old_car.Erase();

            game.Display();
            car.Display();

            old_game = game.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        car.fire(keys,t);

        game.Accelerate();
        car.Accelerate();

        car.movement_vehicle(keys);
        car.angle_machine(keys);

        game.Move();
        car.Move();

        car.arsenal_collide(game);
        game.AutoCollide();

        game.groundBounce();
        car.groundBounce();

        t+=dt;
    }
    */
    endGraphics();
    return 0;
}
