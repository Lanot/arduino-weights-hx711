//https://wiki.iarduino.ru/page/hx_711_with_tenzo/
#include "HX711.h"

uint8_t DOUT_PIN = 15;//A1
uint8_t SCK_PIN  = 14;//A0

float     weight_of_standard = 201;
float     conversion_rate    = 0.035274;
const int z                  = 10;      
float     calibration_value[z];         
float     calibration_factor = 0;   

HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("Init a loadcell callibration with " + String(weight_of_standard, 2) + " gramms");

  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale();
  scale.tare();          
  
  Serial.println("You have 10 seconds to set your known load");  
  delay(10000);                                                                           
  Serial.print("calibration factor: ");                                                   
  for (int i = 0; i < z; i++) {                                                           
    calibration_value[i] = scale.get_units(1) / (weight_of_standard / conversion_rate);   //to grams
    calibration_factor += calibration_value[i];                                           
  }
  calibration_factor = calibration_factor / z;                                            
  Serial.println(calibration_factor); 
}

void loop() {
}