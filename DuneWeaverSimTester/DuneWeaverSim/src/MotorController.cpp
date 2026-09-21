#include<MotorController.h>

MotorController::MotorController(uint8_t thetaStepPin, uint8_t thetaDirPin, uint8_t rhoStepPin, uint8_t rhoDirPin): stepperTheta(AccelStepper::DRIVER, thetaStepPin, thetaDirPin),
    stepperRho(AccelStepper::DRIVER, rhoStepPin, rhoDirPin){};
MotorController::~MotorController(){};
void MotorController::begin(float maxSpeed, float acceleration){
    stepperRho.setMaxSpeed(maxSpeed);
    stepperTheta.setMaxSpeed(maxSpeed);
    stepperRho.setAcceleration(acceleration);
    stepperTheta.setAcceleration(acceleration);
};
void MotorController::moveToSteps(long thetaSteps, long rhoSteps){
    stepperTheta.moveTo(thetaSteps);
    stepperRho.moveTo(rhoSteps);
};
bool MotorController::run(){
    bool thetaRunning = stepperTheta.run();
    bool rhoRunning = stepperRho.run();
    return thetaRunning || rhoRunning;
};