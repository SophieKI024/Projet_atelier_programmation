#include "level.h"

///////////////// *** PLAY *** ////////////////////////

void play(Structure& game, double t_max){
    Timer chrono;
    Structure old_game = game.copy();
    game.Display();
    double t=0;
    vector<int> keys;
    click();
    chrono.reset();
    for(int timeStep=0; t<t_max; timeStep++){
        keyboard(keys);
        if(fmod(timeStep,periodDisplay)<1){

            noRefreshBegin();

            old_game.Erase();

            game.Display();

            old_game = game.copy();

            noRefreshEnd();
            // on attend exactement ce qu'il faut pour que le jeu s'ecoule à une vitesse cohérente
            milliSleep(max(int(1000*(t-chrono.lap())),0));
        }
        game.set_fire(keys,game.boxes[0].pos,t);
        game.Accelerate(keys);
        game.solveConstraints();
        game.Move(keys);
        t+=dt;
    }
    game = old_game.copy(); // permet d'avoir la dernière image affichée en mémoire.
}

///////////////// *** LEVELS *** ////////////////////////

/// Default level
Structure level_1(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game(Box(Vector2D(x0+500,y0-150),200,30,2,BLUE));
    Weapon* arsenal = new Weapon[3];
    arsenal[0] = Weapon(Canon_standard(),100,Vector2D(-100,-40), 1000,-1000,0.1,1500,1,9,3);
    arsenal[1] = Weapon(Canon_standard(),100,Vector2D(0,-40), 1000,-1000,0.1,1500,1,9,3);
    arsenal[2] = Weapon(Canon_standard(),100,Vector2D(100,-40), 1000,-1000,0.1,1500,1,9,3);
    game.car = Vehicle(3,arsenal);
    game.add(Ball(Vector2D(x0+250,y0-75),50,3,RED));
    game.add(Ball(Vector2D(x0+550,y0-75),50,3,RED));
    game.add(Spring(0,0,1,0,300,0,1000,5e5,5,Color(20,20,20),Vector2D(95,0)));
    game.add(Spring(0,0,1,1,250,0,1000,5e5,5,Color(20,20,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,0,130,0,1000,5e5,5,Color(20,20,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,1,200,0,1000,5e5,5,Color(20,20,20),Vector2D(95,0)));

    game.add(Joint(1,0,1,1,300,5,BLACK));
    game.add(Damper(0,0,1,0,5e4,Vector2D(95,0)));
    game.add(Damper(0,0,1,1,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,0,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,1,5e4,Vector2D(95,0)));

    Box wall1(Vector2D(window_width/2,window_height-10),4000,20,1e100,BLACK);
    Box wall2(Vector2D(0,-20),20,2*window_height,1e100,BLACK);
    Box wall3(Vector2D(window_width,-20),20,2*window_height,1e100,BLACK);
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
    return game;
}

///////////////// *** TITLE SCREEN *** ////////////////////////


Structure title_screen(){
    // ********** Pontstructor **********
    Structure title_screen = Pontstructor();
    title_screen.Display();
    play(title_screen, 6.);
    title_screen.Erase();
    // ********** Select level **********
    Structure game;
    int select_level = 1;
//    while (select_level < 0){
//        int x,y;
//        getMouse(x,y);
//        select_level = 1;
//    }
    if (select_level == 1){
        game = level_1();
    }
    return game;
}

Structure Pontstructor(){
    Structure title_screen;
    int c = window_width/80; // On divise la largeur de l'écran en 80 carreaux
    Vector2D m(0,10*c); // Marge en haut

    Box P_1(m + Vector2D(10.5*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box P_2(m + Vector2D(11.25*c,0.5*c), 2.5*c, c, 1,BLACK);
    Box P_3(m + Vector2D(13.5*c,1.25*c), c, 2.5*c, 1,BLACK);
    Box P_4(m + Vector2D(12.75*c,3.5*c), 2.5*c, c, 1,BLACK);
    P_1.gravity=false;
    P_2.gravity=false;
    P_3.gravity=false;
    P_4.gravity=false;
    title_screen.add(P_1);
    title_screen.add(P_2);
    title_screen.add(P_3);
    title_screen.add(P_4);

    Box O_1(m + Vector2D(15.5*c,3*c), c, 3*c, 1, BLACK);
    Box O_2(m + Vector2D(17*c,0.5*c), 4*c, c, 1,BLACK);
    Box O_3(m + Vector2D(18.5*c,3*c), c, 3*c, 1,BLACK);
    Box O_4(m + Vector2D(17*c,5.5*c), 4*c, c, 1,BLACK);
    O_1.gravity=false;
    O_2.gravity=false;
    O_3.gravity=false;
    O_4.gravity=false;
    title_screen.add(O_1);
    title_screen.add(O_2);
    title_screen.add(O_3);
    title_screen.add(O_4);

    Box N_1(m + Vector2D(20.5*c,3.75*c), c, 4*c, 1, BLACK);
    Ball N_2(m + Vector2D(20.5*c,0.5*c), 0.5*c, 1,BLACK);
    Box N_3(m + Vector2D(22.5*c,3*c), 0.75*c, 4.5*c, 1,BLACK, convert_angle(35));
    Ball N_4(m + Vector2D(24.5*c,5.5*c), 0.5*c, 1,BLACK);
    Box N_5(m + Vector2D(24.5*c,2.25*c), 1*c, 4*c, 1,BLACK);
    N_1.gravity=false;
    N_2.gravity=false;
    N_3.gravity=false;
    N_4.gravity=false;
    N_5.gravity=false;
    title_screen.add(N_1);
    title_screen.add(N_2);
    title_screen.add(N_3);
    title_screen.add(N_4);
    title_screen.add(N_5);

    Box T_1(m + Vector2D(28*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box T_2(m + Vector2D(28*c,0.5*c), 4*c, c, 1,BLACK);
    T_1.gravity=false;
    T_2.gravity=false;
    title_screen.add(T_1);
    title_screen.add(T_2);

    Box S_1(m + Vector2D(33.75*c,0.5*c), 2.5*c, c, 1, BLACK);
    Box S_2(m + Vector2D(31.5*c,1*c), c, 2*c, 1,BLACK);
    Box S_3(m + Vector2D(32.25*c,3*c), 2.5*c, c, 1,BLACK);
    Box S_4(m + Vector2D(34.5*c,3.5*c), c, 2*c, 1,BLACK);
    Box S_5(m + Vector2D(33*c,5.5*c), 4*c, c, 1,BLACK);
    S_1.gravity=false;
    S_2.gravity=false;
    S_3.gravity=false;
    S_4.gravity=false;
    S_5.gravity=false;
    title_screen.add(S_1);
    title_screen.add(S_2);
    title_screen.add(S_3);
    title_screen.add(S_4);
    title_screen.add(S_5);

    Box T_3(m + Vector2D(38*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box T_4(m + Vector2D(38*c,0.5*c), 4*c, c, 1,BLACK);
    T_3.gravity=false;
    T_4.gravity=false;
    title_screen.add(T_3);
    title_screen.add(T_4);

    Box R_1(m + Vector2D(41.5*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box R_2(m + Vector2D(42.25*c,0.5*c), 2.5*c, c, 1, BLACK);
    Box R_3(m + Vector2D(44.5*c,c), c, 2*c, 1, BLACK);
    Box R_4(m + Vector2D(44.25*c,3*c), 1.5*c, c, 1, BLACK);
    Ball R_5(m + Vector2D(42.75*c,3*c), 0.5*c, 1,BLACK);
    Box R_6(m + Vector2D(44*c,5*c), 0.75*c, 3*c, 1,BLACK, convert_angle(40));
    R_1.gravity=false;
    R_2.gravity=false;
    R_3.gravity=false;
    R_4.gravity=false;
    R_5.gravity=false;
    R_6.gravity=false;
    title_screen.add(R_1);
    title_screen.add(R_2);
    title_screen.add(R_3);
    title_screen.add(R_4);
    title_screen.add(R_5);
    title_screen.add(R_6);

    Box U_1(m + Vector2D(46.5*c,2.25*c), c, 4.5*c, 1, BLACK);
    Box U_2(m + Vector2D(48*c,5.5*c), 4*c, c, 1,BLACK);
    Box U_3(m + Vector2D(49.5*c,2.25*c), c, 4.5*c, 1,BLACK);
    U_1.gravity=false;
    U_2.gravity=false;
    U_3.gravity=false;
    title_screen.add(U_1);
    title_screen.add(U_2);
    title_screen.add(U_3);

    Box C_1(m + Vector2D(53.75*c,0.5*c), 2.5*c, c, 1, BLACK);
    Box C_2(m + Vector2D(51.5*c,3*c), c, 6*c, 1,BLACK);
    Box C_3(m + Vector2D(53.75*c,5.5*c), 2.5*c, c, 1,BLACK);
    C_1.gravity=false;
    C_2.gravity=false;
    C_3.gravity=false;
    title_screen.add(C_1);
    title_screen.add(C_2);
    title_screen.add(C_3);

    Box T_5(m + Vector2D(58*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box T_6(m + Vector2D(58*c,0.5*c), 4*c, c, 1,BLACK);
    T_5.gravity=false;
    T_6.gravity=false;
    title_screen.add(T_5);
    title_screen.add(T_6);

    Box O_5(m + Vector2D(61.5*c,3*c), c, 3*c, 1, BLACK);
    Box O_6(m + Vector2D(63*c,0.5*c), 4*c, c, 1,BLACK);
    Box O_7(m + Vector2D(64.5*c,3*c), c, 3*c, 1,BLACK);
    Box O_8(m + Vector2D(63*c,5.5*c), 4*c, c, 1,BLACK);
    O_5.gravity=false;
    O_6.gravity=false;
    O_7.gravity=false;
    O_8.gravity=false;
    title_screen.add(O_5);
    title_screen.add(O_6);
    title_screen.add(O_7);
    title_screen.add(O_8);

    Box R_7(m + Vector2D(66.5*c,3.75*c), c, 4.5*c, 1, BLACK);
    Box R_8(m + Vector2D(67.25*c,0.5*c), 2.5*c, c, 1, BLACK);
    Box R_9(m + Vector2D(69.5*c,c), c, 2*c, 1, BLACK);
    Box R_10(m + Vector2D(69.25*c,3*c), 1.5*c, c, 1, BLACK);
    Ball R_11(m + Vector2D(67.75*c,3*c), 0.5*c, 1,BLACK);
    Box R_12(m + Vector2D(69*c,5*c), 0.75*c, 3*c, 1,BLACK, convert_angle(40));
    R_7.gravity=false;
    R_8.gravity=false;
    R_9.gravity=false;
    R_10.gravity=false;
    R_11.gravity=false;
    R_12.gravity=false;
    title_screen.add(R_7);
    title_screen.add(R_8);
    title_screen.add(R_9);
    title_screen.add(R_10);
    title_screen.add(R_11);
    title_screen.add(R_12);

    Ball destructor(m + Vector2D(-3*c,3*c), 2.1*c, 1000,RED, Vector2D(700,0),-5);
    destructor.gravity=false;
    title_screen.add(destructor);
    return title_screen;
}
