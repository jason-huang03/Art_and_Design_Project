// TestFunctions.cpp
#include "TestFunctions.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // ST7735 library for TFT
#include <Adafruit_MPU6050.h>

extern Adafruit_ST7735 tft; // Use the 'tft' object created in your main sketch
extern Adafruit_MPU6050 mpu; // Use the 'mpu' object created in your main sketch

void testDisplay() {
    // Example function to test display functionality
    tft.fillScreen(ST7735_RED);  // Fill the screen with red color
    delay(1000);
    tft.fillScreen(ST7735_GREEN);  // Fill the screen with green color
    delay(1000);
    tft.fillScreen(ST7735_BLUE);  // Fill the screen with blue color
    delay(1000);
}

void testMPU() {
    // Example function to read from sensors and print the values
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
    }
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    
    // Print accelerometer data
    Serial.println("=== Accelerometer ===");
    Serial.print("X: "); Serial.print(a.acceleration.x); Serial.println(" m/s^2");
    Serial.print("Y: "); Serial.print(a.acceleration.y); Serial.println(" m/s^2");
    Serial.print("Z: "); Serial.print(a.acceleration.z); Serial.println(" m/s^2");

    // Print gyroscope data
    Serial.println("=== Gyroscope ===");
    Serial.print("X: "); Serial.print(g.gyro.x); Serial.println(" rad/s");
    Serial.print("Y: "); Serial.print(g.gyro.y); Serial.println(" rad/s");
    Serial.print("Z: "); Serial.print(g.gyro.z); Serial.println(" rad/s");

    // Print temperature data
    Serial.println("=== Temperature ===");
    Serial.print("Temp: "); Serial.print(temp.temperature); Serial.println(" °C");

}
