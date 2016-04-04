#include "RGBConverter.h"

#define RED 6
#define BLUE 5
#define GREEN 7

double hsv[3];

void setup() {
  // put your setup code here, to run once:

  double hsv[3] = {0.5, 1, 1};

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  byte rgb[3];

  RGBConverter::hsvToRgb(hsv[0], hsv[1], hsv[2], rgb);

  hsv[0] += 0.001; /*colour will cycle, repeating every 2 seconds*/
  if(hsv[0] > 1)
  {
    hsv[0] = 0;
  }

  analogWrite(RED, rgb[0]);
  analogWrite(GREEN, rgb[1]);
  analogWrite(BLUE, rgb[2]);
  
  delay(20);
}
