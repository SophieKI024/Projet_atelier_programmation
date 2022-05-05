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
    double angle=-1;
    Ball wall(Vector2D(300,window_height-h_ground-25-300-100),10,10,Color(140,108,66),Vector2D(0,0));
    Ball wall2(Vector2D(300+400*cos(angle),window_height-h_ground-25-300-100+300*sin(angle)),10,10,Color(140,108,66),Vector2D(0,0));
    Ball wall3(Vector2D(300+400*cos(angle),window_height-h_ground-25-100+300*sin(angle)),10,10,Color(140,108,66),Vector2D(0,0));
    Box wall4(Vector2D(300,window_height-h_ground-25-100),50,50,10,Color(140,108,66),0,Vector2D(0,0));

    Ball testColl(Vector2D(300,320),30,10,BLUE,Vector2D(30,0));
    Ball testColl2(Vector2D(500,300),30,10,BLUE,Vector2D(-30,0));

    Structure house;
    house.add(testColl);
    house.add(testColl2);
    //house.add(wall);
    //house.add(wall2);
    //house.add(wall3);
    //house.add(wall4);

    Joint J1(1,0,1,1,400,3,BLACK);
    Joint J2(1,1,1,2,300,3,BLACK);
    Joint J3(1,2,0,0,400,3,BLACK);
    Joint J4(0,0,1,0,300,3,BLACK);
    Spring S1(1,0,1,2,500,0,1000,1000,4,RED);
    Spring S2(1,1,0,0,500,0,1000,1000,4,RED);
/*
    house.add(J1);
    house.add(J2);
    house.add(J3);
    house.add(J4);
    house.add(S1);
    house.add(S2);
*/
    Structure old_house = house.copy();
    house.Display();
    for(int timeStep=0; timeStep<10000*periodDisplay; timeStep++){
        if(timeStep%periodDisplay==0){
            noRefreshBegin();

            old_house.Erase();

            house.Display();

            old_house = house.copy();

            noRefreshEnd();
            milliSleep(20);
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
