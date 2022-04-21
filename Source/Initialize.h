#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "mainwindow.h"
#include <string>

#define Gravitation_Param 398600000000000

double Start_SC_Mass, Gas_Flow_Speed, Fly_Time, Start_Orbit_Height,
    Start_Orbit_Inclination,Finally_Orbit_Height,Finally_Orbit_Inclination, Engine_Specific_Mass,
    Electro_Specific_Mass, SSS_Realitive_Mass, Realitive_Construct_Mass, EFFICIENCY, Engines_Thrust,
    Start_Orbit_Radius, Finnaly_Orbit_Radius, Initial_Speed, Delta_velocity, Engines_Power,Gas_Mass,
    Construct_Mass, Engines_Mass, Electro_Mass, SSS_Mass, Payload_Mass;

double TIME = 0;





__int8 EngineNumber = 1;

QString name;
QString SelectedEngine = "1";





void SdelatPizdato()
{
    Start_Orbit_Radius = (6371 + Start_Orbit_Height)*1000;
    Finnaly_Orbit_Radius = (6371 + Finally_Orbit_Height)*1000;
    Initial_Speed = sqrt(Gravitation_Param/Start_Orbit_Radius);
    Delta_velocity = Initial_Speed*sqrt(1-2*sqrt(Start_Orbit_Radius/Finnaly_Orbit_Radius)*cos((M_PI/2)*(Finally_Orbit_Inclination-Start_Orbit_Inclination))+(Start_Orbit_Radius/Finnaly_Orbit_Radius));
    Gas_Mass = Start_SC_Mass*(1-exp((-Delta_velocity)/Gas_Flow_Speed));
    Engines_Thrust = (Gas_Flow_Speed*Gas_Mass)/(Fly_Time);
    Engines_Power = (Engines_Thrust*Gas_Flow_Speed)/(2*EFFICIENCY);
    Construct_Mass = Realitive_Construct_Mass * Start_SC_Mass;
    Engines_Mass = Engine_Specific_Mass * Engines_Thrust;
    Electro_Mass = Electro_Specific_Mass * Engines_Power;
    SSS_Mass = SSS_Realitive_Mass * Gas_Mass;
    Payload_Mass = Start_SC_Mass - Gas_Mass - Construct_Mass - SSS_Mass - Engines_Mass - Electro_Mass;
}


void SdelatZaebumba()
{
    Start_Orbit_Radius = (6371 + Start_Orbit_Height)*1000;
    Finnaly_Orbit_Radius = (6371 + Finally_Orbit_Height)*1000;
    Initial_Speed = sqrt(Gravitation_Param/Start_Orbit_Radius);
    Delta_velocity = Initial_Speed*sqrt(1-2*sqrt(Start_Orbit_Radius/Finnaly_Orbit_Radius)*cos((M_PI/2)*(Finally_Orbit_Inclination-Start_Orbit_Inclination))+(Start_Orbit_Radius/Finnaly_Orbit_Radius));
    Gas_Mass = Start_SC_Mass*(1-exp((-Delta_velocity)/Gas_Flow_Speed));


    Construct_Mass = Realitive_Construct_Mass * Start_SC_Mass;
    Engines_Mass = Engine_Specific_Mass * Engines_Thrust;
    Electro_Mass = Electro_Specific_Mass * Engines_Power;
    SSS_Mass = SSS_Realitive_Mass * Gas_Mass;
    Payload_Mass = Start_SC_Mass - Gas_Mass - Construct_Mass - SSS_Mass - Engines_Mass - Electro_Mass;

}



int RK_STEPS =Fly_Time/100;
double INITIAL_ACCELERATION = Engines_Thrust/Start_SC_Mass;


double ANGLE_U = 0;
double RADIUS = Start_Orbit_Radius;
double VELOCITY=0;
double INCLINATION=Start_Orbit_Inclination;





#endif // INITIALIZE_H
