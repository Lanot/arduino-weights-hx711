#include "HX711.h"

uint8_t DOUT_PIN = 15;//A1
uint8_t SCK_PIN  = 14;//A0

float scale_calibration = 111.811290;
float weight_units;
float weight_gr;


HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting loadcell...");

  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale();
  scale.tare();
}

void loop() {
  scale.set_scale(scale_calibration);

  Serial.print("Read data: ");
  weight_units = scale.get_units(), 10;

  if (weight_units < 0) {
    weight_units = 0.00;
  }

  weight_gr = weight_units * 0.035274;
  Serial.print("weight_gr =");

  Serial.print(weight_gr);
  Serial.print(" gr");

  Serial.print("scale_calibration=");
  Serial.println(scale_calibration);

  delay(500);
}