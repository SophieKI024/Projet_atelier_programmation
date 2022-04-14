#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;


#include "tools.h"


void shock(double x,  double y,  double &vx,  double &vy,  double m,
           double x2, double y2, double &vx2, double &vy2, double m2) {
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


void shockSimple(double x,  double y,  double &vx, double &vy, double m,
                 double x2, double y2, double vx2, double vy2) {
    shock(x,y,vx,vy,m,x2,y2,vx2,vy2,1000*m);
}


bool collision(double x1, double y1, double vx1, double vy1, double r1,
               double x2, double y2, double vx2, double vy2, double r2) {
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

