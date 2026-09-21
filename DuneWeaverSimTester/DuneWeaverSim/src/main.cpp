#include <Arduino.h>
#include <Kinematics.h>
#include <MotorController.h>
#include <GCodeParser.h>

MotorController motors(2, 3, 4, 5);
Kinematics kinematics(100.0, 200);
GCodeParser parser;

void setup() {
    Serial.begin(115200);
    motors.begin(1000.0, 500.0);
    Serial.println("Dune-Weaver Hazir! G-Code komutu bekleniyor (Örn: G1 X30 Y40)...");
}

void loop() {
    parser.listenSerial(kinematics, motors);
    motors.run();
}