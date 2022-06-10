#ifndef MODELING_H
#define MODELING_H
#include <fstream>
#include <math.h>




int Tank_Radius,Tank_CTR,Tank, Body_lenght, EnginePlateRadius, EngineRadius,
EngineLenght,EnginesCount,Engine_CTR,Payload_R,Payload_L,SP_W,SP_L;

int SP_Square,Payload_Volume;

double foo;

void ExcelExport()
{

    SP_W=round(sqrt(SP_Square)/2);
    SP_L=SP_W*4;
    Payload_L=Payload_R*1.5;
    EnginePlateRadius=round(Body_lenght*sqrt(2)/2);
    EngineRadius=25;
    EngineLenght=30;
    Engine_CTR=180;






    std::ofstream OutFile("data.csv");
    OutFile << Body_lenght<< std::endl;
    OutFile << Body_lenght<< std::endl;
    OutFile << Body_lenght<< std::endl;
    OutFile << Tank_Radius << std::endl;
    OutFile << Tank_CTR << std::endl;
    OutFile << EnginePlateRadius << std::endl;
    OutFile << EngineRadius << std::endl;
    OutFile << EngineLenght << std::endl;
    OutFile << Engine_CTR << std::endl;
    OutFile << EnginesCount << std::endl;
    OutFile << Payload_R << std::endl;
    OutFile << Payload_L << std::endl;
    OutFile << SP_W << std::endl;
    OutFile << SP_L << std::endl;
    OutFile.close();
}










#endif // MODELING_H
