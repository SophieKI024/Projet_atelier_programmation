#include "level.h"

///////////////// *** PLAY *** ////////////////////////

/// Fait jouer au jeu pendant un temps au plus t_max

void play(Structure& game){
    Timer chrono;
    if(game.scrolling)
        game.scroll = game.boxes[0].pos- 1/game.scale*Vector2D(window_width/2.,0.7*window_height);
    Structure old_game = game.copy();
    game.Display();
    double t=0;
    vector<int> keys;
    double v_scroll= 3*dt;
    int t0 = -1000;

    chrono.reset();
    for(int timeStep=0; t<game.duration and ((!game.you_lose and !game.you_win) or game.demo); timeStep++){
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
        if(isPressed(keys,'g') and t-t0>5){
            game.gravite = false;
            t0 = t;
        }
        if(!game.gravite and t0>0){
            game.gravite = (t>t0+5);
        }
        if(game.scrolling and t>1)
            game.scroll = (1-v_scroll)*game.scroll + v_scroll*(game.boxes[0].pos + Vector2D(sgn(game.boxes[0].v.x)*min(0.004*pow(game.boxes[0].v.x,2),0.4*window_width/game.scale),sgn(game.boxes[0].v.y)*min(0.004*pow(game.boxes[0].v.y,2),0.4*window_height/game.scale)) - 1/game.scale*Vector2D(window_width/2.,(0.7-0.5*(game.boxes[0].v.y>300))*window_height));

        game.set_fire(keys,game.boxes[0].pos,t);
        game.Accelerate(keys);
        game.solveConstraints();
        game.Move(keys);
        t+=dt;
    }
    old_game.Erase();
    game.Display();
    if(!game.demo){
    if(game.you_lose){
        drawString(window_width/3,window_height/2,"Perdu ...",RED,72);
    }

    else if(game.you_win){
        drawString(window_width/3,window_height/2,"Gagné !",GREEN,72);
    }
    milliSleep(5000);
    }
}

///////////////// *** LEVELS *** ////////////////////////

Structure begin_level(){
    double x0 = 600;
    double y0 = window_height-100;
    Structure game(Box(Vector2D(x0+500,y0-150),200,30,2,Color(40,70,40)));

    Ball objectif(Vector2D(400,y0-550),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.add(objectif);

    Box wall1(Vector2D(0.5,700.5),4000,200,1e100,BLACK);
    Box wall2(Vector2D(-1980.5,-20.5),20,1420,1e100,BLACK);
    Box wall3(Vector2D(1980.5,-20.5),20,1420,1e100,BLACK);
    wall1.gravity=false;
    wall2.gravity=false;
    wall3.gravity=false;
    game.add(wall1);
    game.add(wall2);
    game.add(wall3);
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
    game.car.i_wheels.push_back(1);
    game.add(roue2);
    game.car.i_wheels.push_back(2);
    game.add(Spring(0,0,1,1,300,0,1000,5e5,5,Color(20,30,20),Vector2D(95,0)));
    game.add(Spring(0,0,1,2,250,0,1000,5e5,5,Color(20,30,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,1,130,0,1000,5e5,5,Color(20,30,20),Vector2D(-95,0)));
    game.add(Spring(0,0,1,2,200,0,1000,5e5,5,Color(20,30,20),Vector2D(95,0)));

    game.add(Joint(1,1,1,2,300,5,BLACK));
    game.add(Damper(0,0,1,1,5e4,Vector2D(95,0)));
    game.add(Damper(0,0,1,2,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,1,5e4,Vector2D(-95,0)));
    game.add(Damper(0,0,1,2,5e4,Vector2D(95,0)));
    return game;
}

/// Default level
Structure level_1(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game = begin_level();

    Ball objectif(Vector2D(400,y0-550),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.balls[0] = objectif;

    addPyramid2(game,400,y0,50,200,200,2);

    game.scale = 0.5;
    return game;
}

Structure level_2(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game = begin_level();

    Ball objectif(Vector2D(400,y0-550),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.balls[0] = objectif;

    addTower(game,400,y0,50,200,200,3);

    game.scale = 0.5;
    return game;
}

Structure level_3(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game = begin_level();

    Ball objectif(Vector2D(400,y0-550),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.balls[0] = objectif;

    game.boxes[1].friction = 1.5;
    game.boxes[1].Col = Color(0,207,255);

    addPyramid2(game,400,y0,50,200,200,3);

    game.scale = 0.5;
    return game;
}

Structure level_4(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game = begin_level();

    Ball objectif(Vector2D(400,y0-600),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.balls[0] = objectif;


    addTower(game,400,y0,50,200,200,3);
    game.add(Spring(0,game.boxes.size()-1,1,0,100,0,200,5e5,10,BLACK));
    game.add(Damper(0,game.boxes.size()-1,1,0,5e4));
    game.add(Spring(0,game.boxes.size()-2,1,0,100,0,200,5e5,10,BLACK));
    game.add(Damper(0,game.boxes.size()-2,1,0,5e4));
    game.add(Spring(0,game.boxes.size()-3,1,0,100,0,200,5e5,10,BLACK));
    game.add(Damper(0,game.boxes.size()-3,1,0,5e4));


    game.scale = 0.5;
    return game;
}

Structure level_5(){
    double x0 = 600;
    double y0 = window_height-100;
    //On rajoute le vehicule en 1er
    Structure game = begin_level();

    Ball objectif(Vector2D(400,y0-1350),50,5,golden_egg);
    objectif.cross = true;
    objectif.breaking_energy = 2e9;
    game.balls[0] = objectif;


    addTower(game,400,y0,50,200,200,5);

    game.scale = 0.5;
    return game;
}

Structure demoBall(){
    Structure Demo;
    Box wall1(Vector2D(100.5,510.5),220,20,1e100,BLACK);
    Box wall2(Vector2D(-4.5,200.5),20,600,1e100,BLACK);
    Box wall3(Vector2D(205.5,200.5),20,600,1e100,BLACK);
    wall1.gravity = false;
    wall2.gravity = false;
    wall3.gravity = false;
    Demo.add(wall1);
    Demo.add(wall2);
    Demo.add(wall3);
    srand(0);
    for(int i=0; i<5; i++){
        for(int j=0; j<8; j++){
            Demo.add(Ball(Vector2D(50+30*i+5*doubleRandom(),100+30*j+5*doubleRandom()),10,1,Color(rand()%255,rand()%255,rand()%255)));
        }
    }

    Demo.demo = true;
    Demo.scale = 3;
    return Demo;
}

int r_base =164;
int g_base =116;
int b_base =73;
int r_var = 60;
int g_var = 40;
int b_var = 30;

Color aleatColor(){
    return Color(r_base+(rand()%r_var-0.5*r_var),g_base+(rand()%g_var-0.5*g_var),b_base+(rand()%b_var-0.5*b_var));
}

void addPyramid(Structure& game, double x0, double y0, double w, double h, double espacement, int taille){
    for(int i=0; i<taille; i++){
        for(int j=taille-i; j>=0; j--){
            game.add(Box(Vector2D((j-(taille-i)/2.)*espacement+x0,y0-0.5*h-(w+h+0.5)*i),w,h,pow(1.2,taille-i),aleatColor()));
        }
        game.add(Box(Vector2D(x0,y0-h-w/2.-(h+w+.5)*i),1.5*w+espacement*(taille-i),w,pow(1.2,taille-i),aleatColor()));
    }
}

void addPyramid2(Structure& game, double x0, double y0, double w, double h, double espacement, int taille){
    for(int i=0; i<taille; i++){
        game.add(Box(Vector2D(((taille-i)/2.)*espacement+x0,y0-0.5*h-(w+h+0.5)*i),w,h,pow(1.2,taille-i),aleatColor()));
        game.add(Box(Vector2D((-(taille-i)/2.)*espacement+x0,y0-0.5*h-(w+h+0.5)*i),w,h,pow(1.2,taille-i),aleatColor()));
        game.add(Box(Vector2D(x0,y0-h-w/2.-(h+w+.5)*i),1.5*w+espacement*(taille-i),w,pow(1.2,taille-i),aleatColor()));
    }
}

void addTower(Structure& game, double x0, double y0, double w, double h, double espacement, int taille){
    for(int i=0; i<taille;i++){
        game.add(Box(Vector2D(0.5*espacement+x0,y0-0.5*h-(w+h+0.5)*i),w,h,pow(1.2,taille-i),aleatColor()));
        game.add(Box(Vector2D(-0.5*espacement+x0,y0-0.5*h-(w+h+0.5)*i),w,h,pow(1.2,taille-i),aleatColor()));
        game.add(Box(Vector2D(x0,y0-h-w/2.-(h+w+.5)*i),1.5*w+espacement,w,pow(1.2,taille-i),aleatColor()));
    }
}

Structure demoStructure(){
    double y0 = 1000;
    double x0 = 500;
    Structure Demo;
    Box wall1(Vector2D(x0,1010),10000,20,1e100,BLACK);
    wall1.gravity = false;
    Demo.add(wall1);
    int taille = 5;
    int w = 50;
    int h = 100;
    int espacement = 200;

    addPyramid(Demo,x0,y0,w,h,espacement,taille);

    Demo.demo = true;
    Demo.scale = 0.5;
    return Demo;
}

///////////////// *** TITLE SCREEN *** ////////////////////////


Structure title_screen(bool &stop){

    int choix = 1;

    // ********** Pontstructor **********
    Structure title_screen = Pontstructor(choix);
    title_screen.demo = true;

    title_screen.Display();

    int button_title = -1;
    int x,y;
    Color menu_color_1 = Color(180,200,220);
    Color font_color = BLACK;
    int font_size = window_height/25;
    // Jouer
    fillRect(window_width/3,
             2*window_height/3 - window_height/10,
             window_width/3,
             window_height/6,
             menu_color_1);
    drawString(window_width/3 + window_width/9,
               2*window_height/3 + window_height/9 - window_height/10,
               "Jouer",font_color,font_size);
    // Quitter le jeu
    fillRect(window_width/3,
             2*window_height/3 + window_height/10,
             window_width/3,
             window_height/6,
             menu_color_1);
    drawString(window_width/3 + window_width/20,
               2*window_height/3 + window_height/9 + window_height/10,
               "Quitter le jeu",font_color,font_size);
    // Traitement
    while (button_title < 0){
        getMouse(x,y);
        // Jouer
        if (x > window_width/3 && x < 2*window_width/3
                && y > 2*window_height/3 - window_height/10 && y < 2*window_height/3 - window_height/10 + window_height/6){
            button_title = 1;
        }
        // Quitter
        if (x > window_width/3 && x < 2*window_width/3
                && y > 2*window_height/3 + window_height/10 && y < 2*window_height/3 + window_height/10 + window_height/6){
            button_title = 0;
        }
    }
    fillRect(window_width/3, 2*window_height/3 - window_height/10, window_width/3, window_height/6,backgroundColor);
    fillRect(window_width/3, 2*window_height/3 + window_height/10, window_width/3, window_height/6,backgroundColor);
    if(button_title==0){
        Vector2D pos = title_screen.balls[2].pos;
        double r = title_screen.balls[2].r;
        for(int i=20; i>4; i--){
            fillCircle(pos.x+0.5,pos.y+0.5,r,BLACK);
            milliSleep(20*min(i,15));
            fillCircle(pos.x+0.5,pos.y+0.5,r,RED);
            milliSleep(50);
        }
        fillCircle(pos.x,pos.y,10,backgroundColor);
    }
    if (button_title == 1){
        stop = false;
        play(title_screen);
        title_screen.Erase();

        Structure level_selector = selector();
        level_selector.Display();
        int a = window_width/13;
        int b = window_height/7;
        drawString(4.6*a,0.6*b,"Choix du niveau",font_color,font_size);

        // ********** Select level **********
        Structure game;
        int select_level = -1;
        while (select_level < 0){
            int x,y;
            getMouse(x,y);
            // Level 1
            if (x > a && x < 4*a && y > b && y < 3*b){
                select_level = 0;
                game = level_1();
            }
            // Level 2
            if (x > 5*a && x < 8*a && y > b && y < 3*b){
                select_level = 1;
                game = level_2();
            }
            // Level 3
            if (x > 9*a && x < 12*a && y > b && y < 3*b){
                select_level = 2;
                game = level_3();
            }
            // Level 4
            if (x > 3*a && x < 6*a && y > 4*b && y < 6*b){
                select_level = 3;
                game = level_4();
            }
            // Level 5
            if (x > 7*a && x < 10*a && y > 4*b && y < 6*b){
                select_level = 4;
                game = level_5();
            }
        }
        level_selector.gravite = true;
        level_selector.boxes[select_level].gravity = false;
        level_selector.duration = 2.5;
        play(level_selector);
        level_selector.Erase();
        fillRect(0,0,window_width,window_height,backgroundColor);
        return game;
    }
    if (button_title == 0){
        stop = true;
        title_screen = Pontstructor(button_title);
        return title_screen;
    }
}

Structure Pontstructor(int choix){

    Structure title_screen;
    title_screen.gravite = false;
    title_screen.scrolling = false;
    title_screen.demo = true;
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
        Ball destructor(m + Vector2D(-3*c,3*c), 2.1*c, 1000,golden_egg, Vector2D(700,0),-5);
        destructor.gravity = false;
        destructor.cross = true;
        title_screen.add(destructor);
        title_screen.duration = 6.;
    }
    if(choix == 0)
        title_screen.Explosion(title_screen.balls[2].pos,7e8);
    title_screen.duration = 4.;

    return title_screen;
}

Structure selector(){
    Structure level_selector;
    level_selector.gravite = false;
    level_selector.scrolling = false;
    int a = window_width/13;
    int b = window_height/7;

    Color menu_color_1 = Color(180,200,220);
    Color menu_color_2 = Color(190,180,200);
    Color menu_color_3 = Color(200,160,180);
    Color menu_color_4 = Color(210,140,160);
    Color menu_color_5 = Color(220,120,140);

    level_selector.add(Box(Vector2D(2.5*a,2*b), 3*a, 2*b, 1, menu_color_1));
    level_selector.add(Box(Vector2D(6.5*a,2*b), 3*a, 2*b, 1, menu_color_2));
    level_selector.add(Box(Vector2D(10.5*a,2*b), 3*a, 2*b, 1, menu_color_3));
    level_selector.add(Box(Vector2D(4.5*a,5*b), 3*a, 2*b, 1e100, menu_color_4));
    level_selector.add(Box(Vector2D(8.5*a,5*b), 3*a, 2*b, 1e100, menu_color_5));

    level_selector.demo = true;
    return level_selector;
}
