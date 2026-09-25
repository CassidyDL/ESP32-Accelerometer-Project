#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>

#define SDA 13
#define SCL 14

MPU6050 mpu6050(Wire);
int16_t ax,ay,az;
int16_t gx,gy,gz;

long timer = 0;
float wheelradius = 0.2;
float accelX;
float accelY;
float accelZ;
float gyroX;
float gyroY;
float gyroZ;


// put function declarations here:
float WheelSpeed(float, float);


void setup() {
  Serial.begin(1152000);
  Wire.begin(SDA, SCL);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
    mpu6050.update();
    Serial.print("Wheel Speed:"); Serial.println(WheelSpeed(wheelradius, mpu6050.getGyroZ()));
}

// put function definitions here:
float WheelSpeed(float radius, float gyroZ) {
  return radius * (gyroZ * (PI / 180.0));
}