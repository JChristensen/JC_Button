// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch to demonstrate toggle buttons.

#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button

// pin assignments
const byte
    LED1_PIN(5),                // connect an LED to ground, through an appropriate current limiting resistor
    LED2_PIN(6),                // connect an LED to ground, through an appropriate current limiting resistor
    BUTTON1_PIN(7),             // connect a button switch from this pin to ground
    BUTTON2_PIN(8);             // connect a button switch from this pin to ground

ToggleButton                    // define the buttons
    btn1(BUTTON1_PIN),          // this button's initial state is off
    btn2(BUTTON2_PIN, true);    // this button's initial state is on

void setup()
{
    // initialize the button objects
    btn1.begin();
    btn2.begin();

    // set the LED pins as outputs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);

    // show the initial states
    digitalWrite(LED1_PIN, btn1.toggleState());
    digitalWrite(LED2_PIN, btn2.toggleState());
}

void loop()
{
    // read the buttons
    btn1.read();
    btn2.read();

    // if button state changed, update the LEDs
    if (btn1.changed()) digitalWrite(LED1_PIN, btn1.toggleState());
    if (btn2.changed()) digitalWrite(LED2_PIN, btn2.toggleState());
}
