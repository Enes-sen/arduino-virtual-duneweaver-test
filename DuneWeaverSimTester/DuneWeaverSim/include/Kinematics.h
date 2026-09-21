#ifndef KINEMATICS_H
#define KINEMATICS_H
#include<MotorController.h>
class Kinematics {
private:
    float maxRadius;
    int stepsPerRev;      

public:
    Kinematics(float radius, int steps);
    ~Kinematics();
    void interpolateLine(float x1,float y1,float x2,float y2,float stepSizeSizemm,MotorController &motors);
    void pointToPolar(float x, float y, float &theta, float &rho);
    void polarToSteps(float theta, float rho, long &thetaSteps, long &rhoSteps);
};

#endif