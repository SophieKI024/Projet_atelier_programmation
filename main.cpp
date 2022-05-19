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
    Structure house;
    double x0 = 600;
    double y0 = window_height-100;


    house.add(Box(Vector2D(x0-100,y0-130),60,200,10,RED));
    house.add(Box(Vector2D(x0+100,y0-130),60,200,10,RED));
    house.add(Box(Vector2D(x0,y0-300),300,60,10,BLUE));

    Structure old_house = house.copy();
    house.Display();
    //fillCircle(100,y0,r0,RED);
    Box wall1(Vector2D(window_width/2,window_height-50),2000,100,1e100,BLACK);
    Box wall2(Vector2D(x0-300,window_height/2-101),100,window_height,1e100,BLACK);
    Box wall3(Vector2D(x0+300,window_height/2-101),100,window_height,1e100,BLACK);
    wall1.gravity=false;
    wall2.gravity=false;
    wall3.gravity=false;
    house.add(wall1);
    house.add(wall2);
    house.add(wall3);

    house.Display();
    cout<<"nombre d'entites : "<<house.boxes.size()+house.balls.size()+house.joints.size()+house.springs.size()<<endl;
    Timer t;
    click();
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        if(timeStep%periodDisplay==0){
            int time = t.lap();
            noRefreshBegin();

            old_house.Erase();

            house.Display();

            old_house = house.copy();

            noRefreshEnd();
            // on attend exactement ce qu'il faut pour que le jeu s'ecoule a une vitesse coherente
            milliSleep(max(int(1000*(dt*periodDisplay-time)),1));
            t.reset();
        }

        house.Accelerate();
        house.solveConstraints();
        house.Move();
    }
    /*
    // CONTROLS
    cout <<"Utiliser les flèches directionnelles pour bouger le véhicule et controler l'angle du canon, et Z pour tirer"<<endl;

    // INITIALIZATION


    Box wall(Vector2D(800,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall2(Vector2D(700,window_height-h_ground-150),50,300,20,Color(140,108,66));
    Box wall3(Vector2D(750,window_height-h_ground-150-250),150,50,5,Color(140,108,66));

    Structure house(wall);
    house.add(wall2);
    house.add(wall3);

    Weapon* arsenal = new Weapon[1];

    arsenal[0]= Weapon(Canon_standard(),30,Vector2D(0,-50), convert_angle(0.),convert_angle(180.),1);

    Box body(Vector2D(85,window_height-h_ground-50),150,75,1,Color(50,50,50));
    Vehicle car(body,1,arsenal);

    Structure old_house = house.copy();
    Vehicle old_car = car.copy();

    house.Display();
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

            old_house.Erase();
            old_car.Erase();

            house.Display();
            car.Display();

            old_house = house.copy();
            old_car = car.copy();

            noRefreshEnd();
            milliSleep(20);
        }
        car.fire(keys,t);

        house.Accelerate();
        car.Accelerate();

        car.movement_vehicle(keys);
        car.angle_machine(keys);

        house.Move();
        car.Move();

        car.arsenal_collide(house);
        house.AutoCollide();

        house.groundBounce();
        car.groundBounce();

        t+=dt;
    }
    */
    endGraphics();
    return 0;
}
