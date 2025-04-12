#include "Arduino.h"
#include "DCMDriverL298.h"
#include "Joystick.h"

// L298N Motor Driver 1 (Left side)
#define ENA1 5
#define IN1_1 2
#define IN1_2 3
#define ENB1 6
#define IN1_3 4
#define IN1_4 7

// L298N Motor Driver 2 (Right side)
#define ENA2 9
#define IN2_1 8
#define IN2_2 11
#define ENB2 10
#define IN2_3 12
#define IN2_4 13

// Joystick pins
#define JOY_X A3
#define JOY_Y A4
#define JOY_SW A1

DCMDriverL298 motorLeft(ENA1, IN1_1, IN1_2, ENB1, IN1_3, IN1_4);
DCMDriverL298 motorRight(ENA2, IN2_1, IN2_2, ENB2, IN2_3, IN2_4);
Joystick joystick(JOY_X, JOY_Y, JOY_SW);

const int threshold = 200;  // How much movement to detect (adjust if needed)
const int motorSpeed = 200; // 0 to 255

void setup() {
  Serial.begin(9600);
}

void loop() {
  int x = joystick.getX(); // 0 to 1023
  int y = joystick.getY();

  // Debug - you can remove later
  Serial.print("X: "); Serial.print(x);
  Serial.print("  Y: "); Serial.println(y);

  if (y > 512 + threshold) {
    // Forward
    motorLeft.setMotorA(motorSpeed, 1);
    motorLeft.setMotorB(motorSpeed, 1);
    motorRight.setMotorA(motorSpeed, 1);
    motorRight.setMotorB(motorSpeed, 1);
  }
  else if (y < 512 - threshold) {
    // Backward
    motorLeft.setMotorA(motorSpeed, 0);
    motorLeft.setMotorB(motorSpeed, 0);
    motorRight.setMotorA(motorSpeed, 0);
    motorRight.setMotorB(motorSpeed, 0);
  }
  else if (x < 512 - threshold) {
    // Left turn
    motorLeft.setMotorA(motorSpeed, 0);
    motorLeft.setMotorB(motorSpeed, 0);
    motorRight.setMotorA(motorSpeed, 1);
    motorRight.setMotorB(motorSpeed, 1);
  }
  else if (x > 512 + threshold) {
    // Right turn
    motorLeft.setMotorA(motorSpeed, 1);
    motorLeft.setMotorB(motorSpeed, 1);
    motorRight.setMotorA(motorSpeed, 0);
    motorRight.setMotorB(motorSpeed, 0);
  }
  else {
    // Stop
    motorLeft.stopMotors();
    motorRight.stopMotors();
  }

  delay(100);
}
