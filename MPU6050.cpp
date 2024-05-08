#include "MPU6050.h"

extern Adafruit_MPU6050 mpu;

float getAccelNorm()
{
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  return sqrt(a.acceleration.x * a.acceleration.x + a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z);
}
