#include "RGBConverter.h"

#define FLOAT_RAND(n) static_cast <float> (rand()) / static_cast <float> (RAND_MAX/n)

#define RED_PIN 10
#define BLUE_PIN 9
#define GREEN_PIN 11

#define MODE_OFF 0
#define MODE_SIGNAL_COLOUR 1
#define MODE_LOOP_COLOUR 2
#define MODE_CONST_COLOUR 3

#define MAX_COMMAND_SIZE 8

double hsv[3] = {0.5, 1, 1};
byte rgb[3];
double vector = 0;
int mode = 1;
int* commandBuffer = (int*)malloc(MAX_COMMAND_SIZE);

void setup() {
  // put your setup code here, to run once:

  randomSeed(analogRead(0));

  Serial.begin(9600);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void off()
{
  hsv[0] = 0;
  hsv[1] = 0;
  hsv[2] = 0;
}

void signalColourStep()
{
  float r = FLOAT_RAND(0.002);
  if (FLOAT_RAND(1) >= 0.5)
  {
    r *= -1;
  }
  
  if (fabs(vector + r) < 0.005) { vector += r; }
  hsv[0] += vector;
  if (hsv[0] > 1) { hsv[0] -= 1; }
  if (hsv[0] < 0) { hsv[0] += 1; }

  return;
}

void loopColourStep()
{
  hsv[0] += 0.001;
  return;
}

void setConstColour()
{
  
}

int parseCommand(int* command)
{
  bool commandCorrect = true;
  long h;
  
  switch(command[0])
  {
    case MODE_OFF:
      mode = MODE_OFF;
      break;
    case MODE_SIGNAL_COLOUR:
      mode = MODE_SIGNAL_COLOUR;
      hsv[1] = 1;
      hsv[2] = 1;
      break;
    case MODE_LOOP_COLOUR:
      mode = MODE_LOOP_COLOUR;
      hsv[1] = 1;
      hsv[2] = 1;
      break;
    case MODE_CONST_COLOUR:
      mode = MODE_CONST_COLOUR;
      switch(command[1])
      {
        case 0:
          RGBConverter::rgbToHsv(command[2], command[3], command[4], hsv);
          break;
        case 1:
          h = command[2];
          h <<= 24;
          h += command[3];
          h <<= 16;
          h += command[4];
          h <<= 8;
          h += command[5];
          hsv[0] = h/4294967295.0f; //2^32 - 1 to convert h into [0:1] range
          hsv[1] = (float)command[6]/255;
          hsv[2] = (float)command[7]/255;
          break;
        default:
          commandCorrect = false;
          break;
      }
      break;
    default:
      commandCorrect = false;
  }

  if(commandCorrect)
  {
    Serial.write("Command correct!");
  }
  else
  {
    Serial.write("Command or subcommand not correct, you lose");
  }
}

void loop() {
  if(Serial.available() > 0)
  {
    int commandSize = Serial.peek();
    if(commandSize > MAX_COMMAND_SIZE)
    {
      char* msg;
      sprintf(msg, "Command too long, max command length: %d", MAX_COMMAND_SIZE);
      Serial.write(msg);
      for(int i = 0; i <= commandSize; i++)
      {
        Serial.read();
      }
    }
    else
    {
      if(Serial.available() >= commandSize + 1)
      {
        Serial.read();
        for(int i = 0; i < commandSize; i++)
        {
         commandBuffer[i] = (int)Serial.read();
        }
        parseCommand(commandBuffer);
      }
    }
  }

  switch(mode)
  {
    case MODE_OFF:
      off();
      break;
    case MODE_SIGNAL_COLOUR:
      signalColourStep();
      break;
    case MODE_LOOP_COLOUR:
      loopColourStep();
      break;
    case MODE_CONST_COLOUR:
      setConstColour();
      break;
    default:
      mode = MODE_OFF;
  }  

  RGBConverter::hsvToRgb(hsv[0], hsv[1], hsv[2], rgb);
  analogWrite(RED_PIN, rgb[0]);
  analogWrite(GREEN_PIN, rgb[1]);
  analogWrite(BLUE_PIN, rgb[2]);
  
  delay(20);
}
