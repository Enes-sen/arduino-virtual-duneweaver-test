#include <GCodeParser.h>

GCodeParser::GCodeParser() {
    currentX = 0.0f;
    currentY = 0.0f;
    buffer = "";
}

GCodeParser::~GCodeParser() {}

void GCodeParser::listenSerial(Kinematics &kinematics, MotorController &motors) {
    if (Serial.available()) {
        char c = Serial.read();

        if (c != '\n' && c != '\r') {
            buffer += c;
        } else {
            // Satır sonu geldiğinde tampon doluysa ayrıştır
            if (buffer.length() > 0) {
                ParseLine(buffer, kinematics, motors);
                buffer = "";
            }
        }
    }
}

void GCodeParser::ParseLine(String line, Kinematics &kinematics, MotorController &motors) {
    line.trim(); // Baştaki ve sondaki boşlukları temizle

    if (line.startsWith("G1") || line.startsWith("G0")) {
        float targetX = currentX;
        float targetY = currentY;

        int xIndex = line.indexOf('X');
        int yIndex = line.indexOf('Y');

        if (xIndex != -1) {
            targetX = line.substring(xIndex + 1).toFloat();
        }

        if (yIndex != -1) {
            targetY = line.substring(yIndex + 1).toFloat();
        }

        // En az bir koordinat geldiyse çizimi başlat
        if (xIndex != -1 || yIndex != -1) {
            kinematics.interpolateLine(currentX, currentY, targetX, targetY, 1.0f, motors);
            currentX = targetX;
            currentY = targetY;
            Serial.print("OK -> X: "); Serial.print(currentX);
            Serial.print(" Y: "); Serial.println(currentY);
        }
    }
}