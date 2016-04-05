#include "RGBConverter.h"

#define FLOAT_RAND(n) static_cast <float> (rand()) / static_cast <float> (RAND_MAX/n)

#define RED 10
#define BLUE 9
#define GREEN 11

double hsv[3] = {0.5, 1, 1};
byte rgb[3];
double vector = 0;

void setup() {
  // put your setup code here, to run once:

  randomSeed(analogRead(0));

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  RGBConverter::hsvToRgb(hsv[0], hsv[1], hsv[2], rgb);

  float r = FLOAT_RAND(0.002);
  if (FLOAT_RAND(1) >= 0.5)
  {
    r *= -1;
  }
  
  if (fabs(vector + r) < 0.005) { vector += r; }
  hsv[0] += vector;
  if (hsv[0] > 1) { hsv[0] -= 1; }
  if (hsv[0] < 0) { hsv[0] += 1; }
  
  if(hsv[0] > 1)
  {
    hsv[0] -= 1;
  }
  
  analogWrite(RED, rgb[0]);
  analogWrite(GREEN, rgb[1]);
  analogWrite(BLUE, rgb[2]);
  
  delay(20);
}
