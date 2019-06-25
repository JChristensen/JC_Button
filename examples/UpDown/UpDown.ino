// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example sketch that uses both short and long button presses to adjust
// a number up and down, between two limits. Short presses increment
// or decrement by one, long presses repeat at a specified rate.
// Every time the number changes, it is written to the serial monitor.

#include <JC_Button.h>              // https://github.com/JChristensen/JC_Button

// pin assignments
const byte
    DN_PIN(7),                      // connect a button switch from this pin to ground
    UP_PIN(8);                      // ditto

Button btnUP(UP_PIN), btnDN(DN_PIN);    // define the buttons

const unsigned long
    REPEAT_FIRST(500),              // ms required before repeating on long press
    REPEAT_INCR(100);               // repeat interval for long press
const int
    MIN_COUNT(0),
    MAX_COUNT(59);

void setup()
{
    btnUP.begin();
    btnDN.begin();
    Serial.begin(115200);
}

void loop()
{
    static int
        count,                          // the number that is adjusted
        lastCount(-1);                  // previous value of count (initialized to ensure it's different when the sketch starts)
    static unsigned long
        rpt(REPEAT_FIRST);              // a variable time that is used to drive the repeats for long presses
    enum states_t {WAIT, INCR, DECR};   // states for the state machine
    static states_t STATE;              // current state machine state

    btnUP.read();                   // read the buttons
    btnDN.read();

    if (count != lastCount)         // print the count if it has changed
    {
        lastCount = count;
        Serial.println(count, DEC);
    }

    switch (STATE)
    {
        case WAIT:                              // wait for a button event
            if (btnUP.wasPressed())
                STATE = INCR;
            else if (btnDN.wasPressed())
                STATE = DECR;
            else if (btnUP.wasReleased())       // reset the long press interval
                rpt = REPEAT_FIRST;
            else if (btnDN.wasReleased())
                rpt = REPEAT_FIRST;
            else if (btnUP.pressedFor(rpt))     // check for long press
            {
                rpt += REPEAT_INCR;             // increment the long press interval
                STATE = INCR;
            }
            else if (btnDN.pressedFor(rpt))
            {
                rpt += REPEAT_INCR;
                STATE = DECR;
            }
            break;

        case INCR:
            ++count;                            // increment the counter
            count = min(count, MAX_COUNT);      // but not more than the specified maximum
            STATE = WAIT;
            break;

        case DECR:
            --count;                            // decrement the counter
            count = max(count, MIN_COUNT);      // but not less than the specified minimum
            STATE = WAIT;
            break;
    }
}
