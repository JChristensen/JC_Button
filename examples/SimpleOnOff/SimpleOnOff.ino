// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to turn an LED on and off with a tactile button switch.
// Wire the switch from the Arduino pin to ground.

#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button

// pin assignments
const byte
    BUTTON_PIN(7),              // connect a button switch from this pin to ground
    LED_PIN(13);                // the standard Arduino "pin 13" LED

Button myBtn(BUTTON_PIN);       // define the button

void setup()
{
    myBtn.begin();              // initialize the button object
    pinMode(LED_PIN, OUTPUT);   // set the LED pin as an output
}

void loop()
{
    static bool ledState;       // a variable that keeps the current LED status
    myBtn.read();               // read the button

    if (myBtn.wasReleased())    // if the button was released, change the LED state
    {
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}

