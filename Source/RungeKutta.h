#include "Initialize.h"
#include <math.h>
#include <QVector>
#ifndef RUNGEKUTTA_H
#define RUNGEKUTTA_H
#define Gravitation_Param 398600000000000


double sign(double ARG)
{
    if(ARG > 0) return 1;
    if(ARG == 0) return 0;
    if(ARG < 0) return -1;
}

double F_PSI()
{
    double U_ANG = ANGLE_U;
    double R_0 = Start_Orbit_Radius;
    double R_F = Finnaly_Orbit_Radius;
    double INC_0 = Start_Orbit_Inclination;
    double INC_F = Finally_Orbit_Inclination;
    double VEL_0 = Initial_Speed;
    double V_X = VELOCITY;
    double PSI_MAX = atan(sin(M_PI*(INC_F-INC_0)/2)/sqrt(R_F/R_0)*1/(1-cos(M_PI*(INC_F-INC_0)/2)/sqrt(R_F/R_0)-V_X/VEL_0*sqrt(1-2*cos(M_PI*(INC_F-INC_0)/2)/sqrt(R_F/R_0)+R_0/R_F)));

  if (INC_F < INC_0)
    {
        if (PSI_MAX < 0) return PSI_MAX*sign(cos(U_ANG));
        if (PSI_MAX > 0) return (PSI_MAX-M_PI)*sign(cos(U_ANG));
    }
    if (INC_F > INC_0)
    {
        if (PSI_MAX > 0) return PSI_MAX*sign(cos(U_ANG));
        if (PSI_MAX < 0) return (PSI_MAX+M_PI)*sign(cos(U_ANG));
    }


}

double X_ACC()
{

    return INITIAL_ACCELERATION*cos(F_PSI())*exp(VELOCITY/Gas_Flow_Speed);
}

double Z_ACC()
{
    return -INITIAL_ACCELERATION*sin(abs(F_PSI()))*exp(VELOCITY/Gas_Flow_Speed)*sign(cos(ANGLE_U));//*cos(F_PSI())
}

double dr(double t,  double r, double inc, double u_ang, double vel)
{
    return 2*X_ACC()*sqrt(pow(r,3)/Gravitation_Param);
}

double di(double t,  double r, double inc, double u_ang, double vel)
{
    return Z_ACC()*sqrt(r/Gravitation_Param)*cos(u_ang);
}

double du(double t,  double r, double inc, double u_ang, double vel)
{
    return sqrt(Gravitation_Param/pow(r,3));
}

double dV(double t,  double r, double inc, double u_ang, double vel)
{
    return sqrt(pow(X_ACC(),2)+pow(Z_ACC(),2));
}

double k[4][4];
__int8 h = 100;
double MAX_R =0;

void Runge_Kutta(QVector<double> * LOCAL_TIME, QVector<double> * LOCAL_RADIUS, QVector<double> * LOCAL_INCLINATION)
{

    for(int i = 0; i < RK_STEPS; i++)
    {
        k[0][0]= h * dr(TIME,RADIUS,INCLINATION, ANGLE_U, VELOCITY);
        k[1][0]= h * di(TIME,RADIUS,INCLINATION, ANGLE_U, VELOCITY);
        k[2][0]= h * du(TIME,RADIUS,INCLINATION, ANGLE_U, VELOCITY);
        k[3][0]= h * dV(TIME,RADIUS,INCLINATION, ANGLE_U, VELOCITY);

        k[0][1]= h * dr(TIME+h/2.0,RADIUS+k[0][0]/2.0,INCLINATION+k[1][0]/2.0, ANGLE_U+k[2][0]/2.0, VELOCITY+k[3][0]/2.0);
        k[1][1]= h * di(TIME+h/2.0,RADIUS+k[0][0]/2.0,INCLINATION+k[1][0]/2.0, ANGLE_U+k[2][0]/2.0, VELOCITY+k[3][0]/2.0);
        k[2][1]= h * du(TIME+h/2.0,RADIUS+k[0][0]/2.0,INCLINATION+k[1][0]/2.0, ANGLE_U+k[2][0]/2.0, VELOCITY+k[3][0]/2.0);
        k[3][1]= h * dV(TIME+h/2.0,RADIUS+k[0][0]/2.0,INCLINATION+k[1][0]/2.0, ANGLE_U+k[2][0]/2.0, VELOCITY+k[3][0]/2.0);

        k[0][2]= h * dr(TIME+h/2.0,RADIUS+k[0][1]/2.0,INCLINATION+k[1][1]/2.0, ANGLE_U+k[2][1]/2.0, VELOCITY+k[3][1]/2.0);
        k[1][2]= h * di(TIME+h/2.0,RADIUS+k[0][1]/2.0,INCLINATION+k[1][1]/2.0, ANGLE_U+k[2][1]/2.0, VELOCITY+k[3][1]/2.0);
        k[2][2]= h * du(TIME+h/2.0,RADIUS+k[0][1]/2.0,INCLINATION+k[1][1]/2.0, ANGLE_U+k[2][1]/2.0, VELOCITY+k[3][1]/2.0);
        k[3][2]= h * dV(TIME+h/2.0,RADIUS+k[0][1]/2.0,INCLINATION+k[1][1]/2.0, ANGLE_U+k[2][1]/2.0, VELOCITY+k[3][1]/2.0);

        k[0][3]= h * dr(TIME+h, RADIUS+k[0][2],INCLINATION+k[1][2], ANGLE_U+k[2][2], VELOCITY+k[3][2]);
        k[1][3]= h * di(TIME+h, RADIUS+k[0][2],INCLINATION+k[1][2], ANGLE_U+k[2][2], VELOCITY+k[3][2]);
        k[2][3]= h * du(TIME+h, RADIUS+k[0][2],INCLINATION+k[1][2], ANGLE_U+k[2][2], VELOCITY+k[3][2]);
        k[3][3]= h * dV(TIME+h, RADIUS+k[0][2],INCLINATION+k[1][2], ANGLE_U+k[2][2], VELOCITY+k[3][2]);


        LOCAL_INCLINATION->push_back(180*INCLINATION/M_PI);
        LOCAL_RADIUS->push_back(RADIUS/1000.0);
        LOCAL_TIME->push_back(TIME/86000);

        TIME      += h;
        RADIUS    +=   (k[0][0]+2.0*k[0][1]+2.0*k[0][2]+k[0][3])/6.0;
        if (RADIUS > MAX_R) MAX_R =RADIUS;
        INCLINATION += (k[1][0]+2.0*k[1][1]+2.0*k[1][2]+k[1][3])/6.0;
        ANGLE_U   +=   (k[2][0]+2.0*k[2][1]+2.0*k[2][2]+k[2][3])/6.0;

        VELOCITY  +=   (k[3][0]+2.0*k[3][1]+2.0*k[3][2]+k[3][3])/6.0;
    }

}











#endif // RUNGEKUTTA_H
