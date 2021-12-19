//https://wiki.iarduino.ru/page/hx_711_with_tenzo/
#include "HX711.h"

uint8_t DOUT_PIN = 15;//A1
uint8_t SCK_PIN  = 14;//A0

//float     weight_of_standard = 201; 
const float CALIBRATION_FACTOR = 3.80;//3.81
const float CALIBRATION_THRESHOLD = 5.00;//grams
const float CALIBRATION_RATE    = 0.035274;//unces to grams

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Init a loadcell ... ");
  scale.begin(DOUT_PIN, SCK_PIN);       
  scale.set_scale();                    
  scale.tare();                         
  scale.set_scale(CALIBRATION_FACTOR);  
}

float getWeight() {
  float ounces = scale.get_units(10);
  float grams = ounces * CALIBRATION_RATE; 

  if (grams < CALIBRATION_THRESHOLD) {
    return 0;
  }

  return grams;
}

void loop() {
  Serial.println("Weight grams: " + String(getWeight())); 

  delay(50);       
}