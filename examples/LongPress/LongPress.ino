// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch demonstrating short and long button presses.
//
// A simple state machine where a short press of the button turns the
// Arduino pin 13 LED on or off, and a long press causes the LED to
// blink rapidly. Once in rapid blink mode, another long press goes
// back to on/off mode.

#include <JC_Button.h>          // https://github.com/JChristensen/JC_Button

// pin assignments
const byte
    BUTTON_PIN(7),              // connect a button switch from this pin to ground
    LED_PIN(13);                // the standard Arduino "pin 13" LED

Button myBtn(BUTTON_PIN);       // define the button
const unsigned long
    LONG_PRESS(1000),           // we define a "long press" to be 1000 milliseconds.
    BLINK_INTERVAL(100);        // in the BLINK state, switch the LED every 100 milliseconds.

void setup()
{
    myBtn.begin();              // initialize the button object
    pinMode(LED_PIN, OUTPUT);   // set the LED pin as an output
}

// the list of possible states for the state machine. This state machine has a fixed
// sequence of states, i.e. ONOFF --> TO_BLINK --> BLINK --> TO_ONOFF --> ONOFF
// note that while the user perceives two "modes", i.e. ON/OFF mode and rapid blink mode,
// two extra states are needed in the state machine to transition between these modes.
enum states_t {ONOFF, TO_BLINK, BLINK, TO_ONOFF};

bool ledState;                  // current LED status
unsigned long ms;               // current time from millis()
unsigned long msLast;           // last time the LED was switched

void loop()
{
    static states_t STATE;      // current state machine state
    ms = millis();              // record the current time
    myBtn.read();               // read the button

    switch (STATE)
    {
        // this state watches for short and long presses, switches the LED for
        // short presses, and moves to the TO_BLINK state for long presses.
        case ONOFF:
            if (myBtn.wasReleased())
                switchLED();
            else if (myBtn.pressedFor(LONG_PRESS))
                STATE = TO_BLINK;
            break;

        // this is a transition state where we start the fast blink as feedback to the user,
        // but we also need to wait for the user to release the button, i.e. end the
        // long press, before moving to the BLINK state.
        case TO_BLINK:
            if (myBtn.wasReleased())
                STATE = BLINK;
            else
                fastBlink();
            break;

        // the fast-blink state. Watch for another long press which will cause us to
        // turn the LED off (as feedback to the user) and move to the TO_ONOFF state.
        case BLINK:
            if (myBtn.pressedFor(LONG_PRESS))
            {
                STATE = TO_ONOFF;
                digitalWrite(LED_PIN, LOW);
                ledState = false;
            }
            else
                fastBlink();
            break;

        // this is a transition state where we just wait for the user to release the button
        // before moving back to the ONOFF state.
        case TO_ONOFF:
            if (myBtn.wasReleased())
                STATE = ONOFF;
            break;
    }
}

// reverse the current LED state. if it's on, turn it off. if it's off, turn it on.
void switchLED()
{
    msLast = ms;                // record the last switch time
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
}

// switch the LED on and off every BLINK_INTERVAL milliseconds.
void fastBlink()
{
    if (ms - msLast >= BLINK_INTERVAL)
        switchLED();
}

