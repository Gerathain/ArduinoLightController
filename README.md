# ArduinoLightController
An arduino based controller for a set of LEDs.

Currently has several modes that the arduino can be in:
  Loop colour - slowly loops through the rainbow
  Random variation - moves through the rainbow with a changing velocity
  static colour - displays one colour

The arduino has the ability to communicate over serial with a simple protocol to prevent errors and allow expansion.
  Messages consist of a length and a payload.
  The payload is up to 8 bytes (to try and prevent locking up the arduino with data streams)
  WARNING: if the message length is wrong, the arduino may lock up/freakout. In the future this will be improved so the aruino won't lock up

In the future this will be expanded with the ability to use data streams to control the colour of the lights.

Thanks to ratkins for the code used to convert between HSV and RGB.
