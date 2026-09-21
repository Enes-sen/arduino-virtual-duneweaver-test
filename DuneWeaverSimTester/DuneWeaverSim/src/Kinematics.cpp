#include <Kinematics.h>
#include <Arduino.h>
Kinematics::Kinematics(float radius, int steps){
    maxRadius = radius;
    stepsPerRev = steps;
};
void Kinematics::interpolateLine(float x1, float y1, float x2, float y2, float stepSizeSizemm, MotorController &motors) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float d = sqrt(dx * dx + dy * dy);

    if (d == 0.0f) return;

    int N = (int)(d / stepSizeSizemm);
    if (N == 0) N = 1;

    for (int i = 0; i <= N; i++) {
        float t = (float)i / (float)N;
        float x = x1 + t * dx;
        float y = y1 + t * dy;
        
        float theta, rho;
        long thetaSteps, rhoSteps;
        
        pointToPolar(x, y, theta, rho);
        polarToSteps(theta, rho, thetaSteps, rhoSteps);
        
        motors.moveToSteps(thetaSteps, rhoSteps);
        while (motors.run()) {
            
        }
    }
};
void Kinematics::pointToPolar(float x, float y, float &theta, float &rho){
    rho = sqrt(x*x+y*y);
    theta = atan2(y,x);
};

void Kinematics::polarToSteps(float theta, float rho, long &thetaSteps, long &rhoSteps){
    float revs = theta / (2.0f * PI); 
    thetaSteps = (long)(revs * (float)stepsPerRev);
    rhoSteps = (long)(rho*80.0);
};

Kinematics::~Kinematics(){};