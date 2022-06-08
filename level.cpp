#include "level.h"

///////////////// *** PLAY *** ////////////////////////

/// Fait jouer au jeu pendant un temps au plus t_max
void play(Structure& game, double t_max){
    Timer chrono;
    if(game.scrolling)
    game.scroll = game.boxes[0].pos- 1/game.scale*Vector2D(window_width/2.,0.7*window_height);
    Structure old_game = game.copy();
    game.Display();
    double t=0;
    vector<int> keys;
    double v_scroll= 3*dt;

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

        if(game.scrolling)
        game.scroll = (1-v_scroll)*game.scroll + v_scroll*(game.boxes[0].pos + Vector2D(sgn(game.boxes[0].v.x)*min(0.004*pow(game.boxes[0].v.x,2),0.4*window_width/game.scale),sgn(game.boxes[0].v.x)*min(0.004*pow(game.boxes[0].v.y,2),0.4*window_height/game.scale)) - 1/game.scale*Vector2D(window_width/2.,0.7*window_height));

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
    Structure game(Box(Vector2D(x0+500,y0-150),200,30,2,Color(40,70,40)));
    Weapon* arsenal = new Weapon[3];
    arsenal[0] = Weapon(Canon_standard(),100,Vector2D(-100,-40), 1000,-1000,0.1,1500,1,9,3);
    arsenal[1] = Weapon(Canon_standard(),100,Vector2D(0,-40), 1000,-1000,0.1,1500,1,9,3);
    arsenal[2] = Weapon(Canon_standard(),100,Vector2D(100,-40), 1000,-1000,0.1,1500,1,9,3);
    game.car = Vehicle(3,arsenal);
    Ball roue1(Vector2D(x0+250,y0-75),50,3,Color(30,30,30));
    Ball roue2(Vector2D(x0+550,y0-75),50,3,Color(30,30,30));
    roue1.cross = true;
    roue2.cross = true;
    game.add(roue1);
    game.car.i_wheels.push_back(0);
    game.add(roue2);
    game.car.i_wheels.push_back(1);
    game.add(Spring(0,0,1,0,300,0,1000,5e5,5,Color(20,30,20),Vector2D(95,0)));
    game.add(Spring(0,0,1,1,250,0,1000,5e5,5,Color(20,30,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,0,130,0,1000,5e5,5,Color(20,30,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,1,200,0,1000,5e5,5,Color(20,30,20),Vector2D(95,0)));

    game.add(Joint(1,0,1,1,300,5,BLACK));
    game.add(Damper(0,0,1,0,5e4,Vector2D(95,0)));
    game.add(Damper(0,0,1,1,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,0,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,1,5e4,Vector2D(95,0)));

    Box wall1(Vector2D(0.5,700.5),4000,20,1e100,BLACK);
    Box wall2(Vector2D(20.5,-20.5),20,1420,1e100,BLACK);
    Box wall3(Vector2D(1980.5,-20.5),20,1420,1e100,BLACK);
    wall1.gravity=false;
    wall2.gravity=false;
    wall3.gravity=false;
    game.add(wall1);
    game.add(wall2);
    game.add(wall3);

    game.add(Box(Vector2D(300,y0-101),50,200,2,Color(132,46,27)));
    game.add(Box(Vector2D(500,y0-101),50,200,2,Color(220,85,57)));
    game.add(Box(Vector2D(400,y0-230),300,50,2,Color(188,73,33)));
    game.add(Box(Vector2D(300,y0-360),50,200,2,Color(154,66,37)));
    game.add(Box(Vector2D(500,y0-360),50,200,2,Color(201,80,45)));
    game.add(Box(Vector2D(400,y0-490),300,50,2,Color(142,56,30)));

    game.scale = 0.9;
    return game;
}

///////////////// *** TITLE SCREEN *** ////////////////////////


Structure title_screen(){

    int choix = 2;

    // ********** Pontstructor **********
    Structure title_screen = Pontstructor(choix);

    title_screen.Display();
    click();
    if(choix==2){
        Vector2D pos = title_screen.balls[2].pos;
        double r = title_screen.balls[2].r;
        for(int i=16; i>4; i--){
            fillCircle(pos.x+0.5,pos.y+0.5,r,BLACK);
            milliSleep(i*max(i,8));
            fillCircle(pos.x+0.5,pos.y+0.5,r,RED);
            milliSleep(i*max(i,8));
        }
        fillCircle(window_width/2,window_height/2,10,backgroundColor);
    }
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

Structure Pontstructor(int choix){

    Structure title_screen;
    title_screen.gravite = false;
    title_screen.scrolling = false;
    int c = window_width/80; // On divise la largeur de l'écran en 80 carreaux
    Vector2D m(0,10*c); // Marge en haut

    // P
    title_screen.add(Box(m + Vector2D(10.5*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(11.25*c,0.5*c), 2.5*c, c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(13.5*c,1.25*c), c, 2.5*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(12.75*c,3.5*c), 2.5*c, c, 1,BLACK));

    // O
    title_screen.add(Box(m + Vector2D(15.5*c,3*c), c, 3*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(17*c,0.5*c), 4*c, c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(18.5*c,3*c), c, 3*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(17*c,5.5*c), 4*c, c, 1,BLACK));

    // N
    title_screen.add(Box(m + Vector2D(20.5*c,3.75*c), c, 4*c, 1, BLACK));
    title_screen.add(Ball(m + Vector2D(20.5*c,0.5*c), 0.5*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(22.5*c,3*c), 0.75*c, 4.5*c, 1,BLACK, convert_angle(35)));
    title_screen.add(Ball(m + Vector2D(24.5*c,5.5*c), 0.5*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(24.5*c,2.25*c), 1*c, 4*c, 1,BLACK));

    // T
    title_screen.add(Box(m + Vector2D(28*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(28*c,0.5*c), 4*c, c, 1,BLACK));

    // S
    title_screen.add(Box(m + Vector2D(33.75*c,0.5*c), 2.5*c, c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(31.5*c,1*c), c, 2*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(32.25*c,3*c), 2.5*c, c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(34.5*c,3.5*c), c, 2*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(33*c,5.5*c), 4*c, c, 1,BLACK));

    // T
    title_screen.add(Box(m + Vector2D(38*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(38*c,0.5*c), 4*c, c, 1,BLACK));

    // R
    title_screen.add(Box(m + Vector2D(41.5*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(42.25*c,0.5*c), 2.5*c, c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(44.5*c,c), c, 2*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(44.25*c,3*c), 1.5*c, c, 1, BLACK));
    title_screen.add(Ball(m + Vector2D(42.75*c,3*c), 0.5*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(44*c,5*c), 0.75*c, 3*c, 1,BLACK, convert_angle(40)));

    // U
    title_screen.add(Box(m + Vector2D(46.5*c,2.25*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(48*c,5.5*c), 4*c, c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(49.5*c,2.25*c), c, 4.5*c, 1,BLACK));

    // C
    title_screen.add(Box(m + Vector2D(53.75*c,0.5*c), 2.5*c, c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(51.5*c,3*c), c, 6*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(53.75*c,5.5*c), 2.5*c, c, 1,BLACK));

    // T
    title_screen.add(Box(m + Vector2D(58*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(58*c,0.5*c), 4*c, c, 1,BLACK));

    // O
    title_screen.add(Box(m + Vector2D(61.5*c,3*c), c, 3*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(63*c,0.5*c), 4*c, c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(64.5*c,3*c), c, 3*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(63*c,5.5*c), 4*c, c, 1,BLACK));

    // R
    title_screen.add(Box(m + Vector2D(66.5*c,3.75*c), c, 4.5*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(67.25*c,0.5*c), 2.5*c, c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(69.5*c,c), c, 2*c, 1, BLACK));
    title_screen.add(Box(m + Vector2D(69.25*c,3*c), 1.5*c, c, 1, BLACK));
    title_screen.add(Ball(m + Vector2D(67.75*c,3*c), 0.5*c, 1,BLACK));
    title_screen.add(Box(m + Vector2D(69*c,5*c), 0.75*c, 3*c, 1,BLACK, convert_angle(40)));

    if(choix == 1){
        Ball destructor(m + Vector2D(-3*c,3*c), 2.1*c, 1000,RED, Vector2D(700,0),-5);
        destructor.gravity=false;
        title_screen.add(destructor);
    }
    if(choix == 2)
        title_screen.Explosion(title_screen.balls[2].pos,7e8);
    return title_screen;
}
