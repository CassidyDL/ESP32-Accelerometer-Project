#include <Arduino.h>
#include <MPU6050_tockn.h>
#include <Wire.h>
#include <Preferences.h>

#define SDA 13
#define SCL 14

MPU6050 mpu6050(Wire);
Preferences calibrationstore;

long timer = 0;
float wheelradius = 0.2;
float accelX;
float accelY;
float accelZ;
float gyroX;
float gyroY;
float gyroZ;

float gyroOffsetX;
float gyroOffsetY;
float gyroOffsetZ;


// put function declarations here:
float WheelSpeed(float, float);


void setup() {
  Serial.begin(1152000);
  Wire.begin(SDA, SCL);
  mpu6050.begin();

  calibrationstore.begin("Calibrations", false);

  bool oldCalibration = calibrationstore.isKey("oldCalibrations");

  if (oldCalibration == false) {
      mpu6050.calcGyroOffsets(true);

      gyroOffsetX = mpu6050.getGyroXoffset();
      gyroOffsetY = mpu6050.getGyroYoffset();
      gyroOffsetZ = mpu6050.getGyroZoffset();
      
      calibrationstore.putFloat("gyroOffX", gyroOffsetX);
      calibrationstore.putFloat("gyroOffY", gyroOffsetY);
      calibrationstore.putFloat("gyroOffZ", gyroOffsetZ);
      calibrationstore.putBool("oldCalibrations", true);

  }
  else {
    gyroOffsetX = calibrationstore.getFloat("gyroOffX", 0.0);
    gyroOffsetY = calibrationstore.getFloat("gyroOffX", 0.0);
    gyroOffsetZ = calibrationstore.getFloat("gyroOffX", 0.0);

    mpu6050.setGyroOffsets(
      gyroOffsetX,
      gyroOffsetY,
      gyroOffsetZ
    );
  }
}

void loop() {
    mpu6050.update();
    Serial.print("Wheel Speed:"); Serial.println(WheelSpeed(wheelradius, mpu6050.getGyroZ()));
}

// put function definitions here:
float WheelSpeed(float radius, float gyroZ) {
  return radius * (gyroZ * (PI / 180.0));
}