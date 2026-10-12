#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

// Pins for the ILI9341 Display
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8

// Init Display und Sensor
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
Adafruit_SHT31 sht30 = Adafruit_SHT31();

void drawUserInterface() {

  tft.fillRect(0, 0, 320, 40, ILI9341_BLUE);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 12);
  tft.print("UNO 1 + ILI9341 + SHT30");

  tft.drawRect(0, 45, 320, 70, ILI9341_GREEN);

  tft.setCursor(20, 50);
  tft.setTextColor(ILI9341_YELLOW);
  tft.print("Display SPI Pin Mapping");
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(20, 70);
  tft.print("MOSI:11 MISO:12 SCLK:13");
  tft.setCursor(20, 90);
  tft.print("RST:  8 DC:   9 CS:  10");

  tft.drawRect(0, 120, 320, 120, ILI9341_RED);
  tft.setCursor(20, 125);
  tft.setTextColor(ILI9341_YELLOW);
  tft.print("   SHT30 Sensor Data");

}

void setup() {
  Serial.begin(9600);
  Serial.println("Uno 1 ILI9341 (SPI) SHT30 (I2C)");

  // start Display
  //tft.begin(); // default 24 MHz
  tft.begin(4000000); // 4 MHz
  tft.setRotation(1);  // 1 = Landscape (320x240)
  tft.fillScreen(ILI9341_BLACK);

  // start Sensor
  if (!sht30.begin(0x44)) {
    Serial.println("SHT30 not found, check wiring.");
    tft.fillScreen(ILI9341_RED);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(20, 100);
    tft.print("Sensor-Error!");
    while (1)
      ;
  }

  drawUserInterface();
}

void loop() {

  // retrieve data from the sensor
  float t = sht30.readTemperature();
  float h = sht30.readHumidity();

  tft.setTextSize(3);
  tft.fillRect(20, 150, 295, 85, ILI9341_BLACK);

  tft.setCursor(20, 150);
  tft.setTextColor(ILI9341_WHITE);
  if (!isnan(t)) {
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
    tft.print("Temp.:  ");
    tft.print(t, 1);
    tft.print(" C");
  } else {
    Serial.println("Error while reading the temperature");
    tft.print("Error");
  }

  tft.setCursor(20, 180);
  tft.setTextColor(ILI9341_WHITE);
  if (!isnan(h)) {
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.println(" %");
    tft.print("Humid.: ");
    tft.print(h, 1);
    tft.print(" %");
  } else {
    Serial.println("Error while reading the humidity");
    tft.print("Error");
  }
  Serial.println("--------------------------------");
  delay(2000);
}

/*
Sketch uses 17124 bytes (53%) of program storage space. Maximum is 32256 bytes.
Global variables use 919 bytes (44%) of dynamic memory, leaving 1129 bytes for local variables. Maximum is 2048 bytes.
*/