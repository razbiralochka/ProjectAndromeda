#ifndef MODELING_H
#define MODELING_H
#include <fstream>





int Tank_Radius,Tank_CTR,Tank, Body_lenght, EnginePlateRadius, EngineRadius,
EngineLenght,EnginesCount,Engine_CTR,Payload_R,Payload_L,SP_W,SP_L;

void ExcelExport()
{












    std::ofstream OutFile("data.csv");
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
    OutFile.close();
}










#endif // MODELING_H
