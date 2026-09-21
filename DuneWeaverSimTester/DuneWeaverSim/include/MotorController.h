#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H

#include <AccelStepper.h>
class MotorController{
private:
    AccelStepper stepperTheta;
    AccelStepper stepperRho;
public:
    MotorController(uint8_t thetaStepPin, uint8_t thetaDirPin, uint8_t rhoStepPin, uint8_t rhoDirPin);
    ~MotorController();
    void begin(float maxSpeed, float acceleration);
    void moveToSteps(long thetaSteps, long rhoSteps);
    bool run();
};

#endif