#ifndef GCODE_PARSER_H
#define GCODE_PARSER_H
#include <Kinematics.h>
#include <MotorController.h>
class GCodeParser{
    private:
        float currentX;
        float currentY;
        String buffer;
    public:
        GCodeParser();
        ~GCodeParser();
        
        void ParseLine(String line, Kinematics &kinematics, MotorController &motors);
        void listenSerial(Kinematics &kinematics, MotorController &motors);

};


#endif