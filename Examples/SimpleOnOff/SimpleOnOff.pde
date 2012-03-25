/*----------------------------------------------------------------------*
 * Example sketch for Arduino Button Library by Jack Christensen        *
 *                                                                      *
 * The simplest example. Using a tactile button switch to turn          *
 * the Arduino's pin 13 LED on and off. Wire a switch from Arduino      *
 * pin 2 to ground.                                                     *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include <Button.h>        //https://github.com/JChristensen/Button

#define BUTTON_PIN 2       //Connect a tactile button switch (or something similar)
                           //from Arduino pin 2 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.
#define LED_PIN 13         //The standard Arduino "Pin 13" LED

Button myBtn(BUTTON_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the button
boolean ledState;          //A variable that keeps the current LED status

void setup(void)
{
    pinMode(LED_PIN, OUTPUT);    //Set the LED pin as an output
}

void loop(void)
{
    myBtn.read();                    //Read the button

    if (myBtn.wasReleased()) {       //If the button was released, change the LED state
        ledState = !ledState;
        digitalWrite(LED_PIN, ledState);
    }
}


