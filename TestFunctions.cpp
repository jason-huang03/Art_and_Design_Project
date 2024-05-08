// TestFunctions.cpp
#include "TestFunctions.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // ST7735 library for TFT
#include <Adafruit_MPU6050.h>
#include "W25Q64.h"
#include "W25Q64_cp.h"

extern Adafruit_ST7735 tft;  // Use the 'tft' object created in your main sketch
extern Adafruit_MPU6050 mpu; // Use the 'mpu' object created in your main sketch
extern W25Q64SPI W25Q64;     // Use the 'W25Q64' object created in your main sketch
extern W25Q64SPI_cp W25Q64_cp;

void testDisplay()
{
  // Example function to test display functionality
  tft.fillScreen(ST7735_RED); // Fill the screen with red color
  delay(1000);
  tft.fillScreen(ST7735_GREEN); // Fill the screen with green color
  delay(1000);
  tft.fillScreen(ST7735_BLUE); // Fill the screen with blue color
  delay(1000);
}

void testMPU()
{
  // Example function to read from sensors and print the values
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
  }
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // Print accelerometer data
  Serial.println("=== Accelerometer ===");
  Serial.print("X: ");
  Serial.print(a.acceleration.x);
  Serial.println(" m/s^2");
  Serial.print("Y: ");
  Serial.print(a.acceleration.y);
  Serial.println(" m/s^2");
  Serial.print("Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  // Print gyroscope data
  Serial.println("=== Gyroscope ===");
  Serial.print("X: ");
  Serial.print(g.gyro.x);
  Serial.println(" rad/s");
  Serial.print("Y: ");
  Serial.print(g.gyro.y);
  Serial.println(" rad/s");
  Serial.print("Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  // Print temperature data
  Serial.println("=== Temperature ===");
  Serial.print("Temp: ");
  Serial.print(temp.temperature);
  Serial.println(" °C");
}

void testW25Q64()
{
  // // // Example function to test W25Q64 functionality
  // // uint8_t MID;
  // // uint16_t DID;
  // // W25Q64.W25Q64_ReadID(&MID, &DID);

  // // // Data to write
  // // uint8_t dataToWrite[10] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
  // // uint32_t address = 0x000000; // Start address for the write/read test
  // // uint8_t dataRead[10]; // Array to store the data read

  // // // Write data to W25Q64
  // // W25Q64.W25Q64_PageProgram(address, dataToWrite, sizeof(dataToWrite));
  // // Serial.println("Data written to flash memory.");

  // // // Read data back from W25Q64
  // // W25Q64.W25Q64_ReadData(address, dataRead, sizeof(dataRead));
  // // Serial.print("Data read from flash memory: ");
  // // for (int i = 0; i < sizeof(dataRead); i++) {
  // //     Serial.print(dataRead[i], HEX);
  // //     Serial.print(" ");
  // // }
  // // Serial.println();

  // // // Compare written and read data
  // // bool dataMatch = true;
  // // for (int i = 0; i < sizeof(dataToWrite); i++) {
  // //     if (dataToWrite[i] != dataRead[i]) {
  // //         dataMatch = false;
  // //         break;
  // //     }
  // // }

  // // if (dataMatch) {
  // //     Serial.println("Read data matches written data!");
  // // } else {
  // //     Serial.println("Error: Read data does not match written data.");
  // // }

  // uint8_t i;
  // // uint8_t MID = 0x00;
  // // uint16_t DID = 0x00;
  // uint8_t ArrayWrite[] = "Hello World!";
  // uint8_t ArrayRead[12];

  // W25Q64.MySPI_Start(); // Equivalent to MySPI_W_SS(1); and MySPI_W_SCK(0); in the setup
  // // W25Q64.W25Q64_ReadID(&MID, &DID);
  // // Serial.print("ID = 0x");
  // // Serial.print(MID, HEX);
  // // Serial.println(DID, HEX);

  // W25Q64.W25Q64_SectorErase(0x000000);
  // W25Q64.W25Q64_WaitBusy();
  // W25Q64.W25Q64_PageProgram(0x000000, ArrayWrite, 12);
  // W25Q64.W25Q64_ReadData(0x000000, ArrayRead, 12);
  // W25Q64.W25Q64_WaitBusy();

  // for (i = 0; i < 12; i++)
  // {
  //   Serial.print((char)ArrayRead[i]);
  // }
  // Serial.println();

  // // W25Q64.W25Q64_SectorErase(0x000000);
  // // W25Q64.W25Q64_ReadData(0x000000, ArrayRead, 12);
  // // for(i = 0; i < 12; i++) {
  // //   Serial.print(ArrayRead[i], HEX);
  // // }
  // // Serial.println();

  uint8_t rec[10];
  uint8_t data[10] = "transmitok";
  Serial.print("start");
  W25Q64_cp.W25Q64_ReadData(rec, 0x000000, 10);
  for (int i = 0; i < 10; i++)
  {
    Serial.print(rec[i]);
    Serial.println();
  }
  Serial.println();
  Serial.print("continue1");
  W25Q64_cp.W25Q64_SectorErase(0x000000);
  W25Q64_cp.W25Q64_WritePage(data, 0x000000);
  W25Q64_cp.W25Q64_ReadData(rec, 0x000000, 10);
  for (int i = 0; i < 10; i++)
  {
    Serial.print(rec[i]);
  }
  Serial.println();
  W25Q64_cp.W25Q64_SectorErase(0x000000);
}
