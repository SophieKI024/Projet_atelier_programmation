
#include "tools.h"

void drawGround(){
    fillRect(0,height-h_ground,width,h_ground,Color(88,41,0));
    fillRect(0,height-h_ground,width,h_ground/3,Color(107,202,35));
}

int sgn(double a){  // renvoie +1 si a>0, -1 si a<0 et 0 si a=0
    return (a>0)-(a<0);
}

void InitRandom(){
    srand((unsigned int) time(0));
}

// Fonctions Tp4

void shock(double x,  double y,  double &vx,  double &vy,  double m, double x2, double y2, double &vx2, double &vy2, double m2) {
    double vvx = (m * vx + m2 * vx2)/(m + m2);
    double vvy = (m * vy + m2 * vy2)/(m + m2);
    double deltax = x2 - x;
    double deltay = y2 - y;
    double norme = deltax * deltax + deltay * deltay;
    double scal = -2. * ((vx-vvx)*deltax + (vy-vvy)*deltay)/norme;
    vx += scal * deltax;
    vy += scal * deltay;
    scal = -2. * ((vx2-vvx)*deltax + (vy2-vvy)*deltay)/norme;
    vx2 += scal * deltax;
    vy2 += scal * deltay;
}


void shock(Ball &D, Ball &S){
    shock(D.pos.x, D.pos.y, D.vitesse.x, D.vitesse.y, D.masse, S.pos.x, S.pos.y, S.vitesse.x, S.vitesse.y, S.masse);
}

void shockSimple(double x,  double y,  double &vx, double &vy, double m, double x2, double y2, double vx2, double vy2) {
    shock(x,y,vx,vy,m,x2,y2,vx2,vy2,1000*m);
}

void shockSimple(Ball &D, Ball S){
    shockSimple(D.pos.x, D.pos.y, D.vitesse.x, D.vitesse.y, D.masse, S.pos.x, S.pos.y, S.vitesse.x, S.vitesse.y);
}

bool collision(double x1, double y1, double vx1, double vy1, double r1, double x2, double y2, double vx2, double vy2, double r2, float dt) {
    double dx=x1-x2,dy=y1-y2,dvx=vx1-vx2,dvy=vy1-vy2,r=r1+r2;
    if(dvx*dvx + dvy*dvy != 0) {
        double t_min = -(dx*dvx + dy*dvy)/(dvx*dvx + dvy*dvy);
        double t_true;
        if (t_min < 0)
            t_true = 0;
        else if (t_min > dt)
            t_true = dt;
        else
            t_true = t_min;
        dx += dvx * t_true;
        dy += dvy * t_true;
    }
    return ((dx*dx + dy*dy) <= r*r);
}

bool collision(Ball &D, Ball &S, float dt){
    return collision(D.pos.x, D.pos.y, D.vitesse.x, D.vitesse.y, D.rayon, S.pos.x, S.pos.y, S.vitesse.x, S.vitesse.y, S.rayon, dt);
}

void Gravitation(Ball sun, Ball &D, int G, double dt){
    Vector r = D.pos - sun.pos;
    double comp_acc_sur_r = - G * sun.masse / pow(r.norme(), 3);
    D.vitesse += (r * comp_acc_sur_r) * dt;
}

void Gravitation_bis(Ball &sun, Ball &D, int G, double dt){
    Vector r = D.pos - sun.pos;
    double comp_acc_sur_r = - G * sun.masse / pow(r.norme(), 3);
    D.vitesse += (r * comp_acc_sur_r) * dt;
    sun.vitesse -= (r * comp_acc_sur_r) * dt;
}

void Display_tour(int tour, string nom_joueur_1, string nom_joueur_2, int width, int height){
    string c = to_string(tour);
    drawString(width/2 - 10, height/2 - 200, "Tour " + c , RED);
    if (tour%2 == 0){
        drawString(width/2 - 10, height/2 - 180, nom_joueur_1 + " joue.", RED);
    }
    else{
        drawString(width/2 - 10, height/2 - 180, nom_joueur_2 + " joue.", RED);
    }
}

void Soleils(int nbSoleils, Ball soleils[], Ball super_sun, Ball Joueur_1, Ball Joueur_2, int width, int height){
    for (int i=0; i<nbSoleils; i++){
            bool found = false;
            double rayon = 0;
            while (not found){
                rayon = 5 + rand()%10;
                soleils[i] = Ball(Vector(rand()%width, rand()%height), Vector(), rayon, YELLOW, rayon / 20);
                int compteur = 0;

                Vector Vector_distance = soleils[i].pos - super_sun.pos;
                double ecart = Vector_distance.norme() - soleils[i].rayon - super_sun.rayon;
                if (ecart > 0){
                    compteur ++;
                }

                Vector_distance = soleils[i].pos - Joueur_1.pos;
                ecart = Vector_distance.norme() - soleils[i].rayon - Joueur_1.rayon;
                if (ecart > 100){
                    compteur ++;
                }

                Vector_distance = soleils[i].pos - Joueur_2.pos;
                ecart = Vector_distance.norme() - soleils[i].rayon - Joueur_2.rayon;
                if (ecart > 100){
                    compteur ++;
                }

                for (int j=0; j<i; j++){
                    Vector_distance = soleils[i].pos - soleils[j].pos;
                    ecart = Vector_distance.norme() - soleils[i].rayon - soleils[j].rayon;
                    if (ecart > 0){
                        compteur ++;
                    }
                }
                if (compteur == i+3){
                    found = true;
                }
            }
            soleils[i].display();
    }
}
