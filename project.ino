#include <Adafruit_GFX.h>    // Core graphics library for all Adafruit displays
#include <Adafruit_ST7735.h> // Library specific to the ST7735 TFT display

#include <Adafruit_MPU6050.h> // Library for MPU6050 accelerometer and gyroscope
#include <Adafruit_Sensor.h>  // Generic sensor library needed for the MPU6050
#include <Wire.h>             // Wire library for I2C communication

#include "W25Q64.h"
#include "TestFunctions.h"
#include "W25Q64_cp.h"

// Pin definitions for the Adafruit 1.44" TFT with ST7735
#define TFT_CS 10 // Chip select line for TFT display
#define TFT_RST 8 // Reset line for TFT (optional use, can connect to Arduino RESET pin)
#define TFT_DC 9  // Data/command line for TFT

// TFT screen
// SCK: 13, SDI: 11, CS: 10, RS: 9, RST: 8

// Create an ST7735 object. Since we are using hardware SPI, MOSI and SCK are set automatically
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// MPU6050: SCL: A5, SDA: A4

// Create an MPU6050 object
Adafruit_MPU6050 mpu;

// Flag to keep track of MPU6050 initialization status
bool mpu_able = true;

// W25Q64: software SPI
W25Q64SPI W25Q64 = W25Q64SPI();
W25Q64SPI_cp W25Q64_cp = W25Q64SPI_cp();

void setup()
{
  // Serial communication for debugging
  Serial.begin(9600);

  // Initialize the display
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK); // Clear the screen to black

  // Initialize MPU6050
  if (!mpu.begin())
  {
    // If MPU6050 initialization fails, update flag
    mpu_able = false;
    Serial.println("Failed to find MPU6050 chip");
  }

  // W25Q64.SPI_Init();
  W25Q64_cp.W25Q64_Init();
}

void loop()
{
  // testDisplay();
  // testMPU();
  // testW25Q64();
  testMPU();
  delay(1000);
}
