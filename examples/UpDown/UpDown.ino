/*----------------------------------------------------------------------*
 * Example sketch for Arduino Button Library by Jack Christensen        *
 *                                                                      *
 * An example that uses both short and long button presses to adjust    *
 * a number up and down, between two limits. Short presses increment    *
 * or decrement by one, long presses repeat at a specified rate.        *
 * Every time the number changes, it is written to the serial monitor.  *
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/

#include <Button.h>        //https://github.com/JChristensen/Button

#define DN_PIN 2           //Connect two tactile button switches (or something similar)
#define UP_PIN 3           //from Arduino pin 2 to ground and from pin 3 to ground.
#define PULLUP true        //To keep things simple, we use the Arduino's internal pullup resistor.
#define INVERT true        //Since the pullup resistor will keep the pin high unless the
                           //switch is closed, this is negative logic, i.e. a high state
                           //means the button is NOT pressed. (Assuming a normally open switch.)
#define DEBOUNCE_MS 20     //A debounce time of 20 milliseconds usually works well for tactile button switches.

#define REPEAT_FIRST 500   //ms required before repeating on long press
#define REPEAT_INCR 100    //repeat interval for long press
#define MIN_COUNT 0
#define MAX_COUNT 59

Button btnUP(UP_PIN, PULLUP, INVERT, DEBOUNCE_MS);    //Declare the buttons
Button btnDN(DN_PIN, PULLUP, INVERT, DEBOUNCE_MS);

enum {WAIT, INCR, DECR};              //The possible states for the state machine
uint8_t STATE;                        //The current state machine state
int count;                            //The number that is adjusted
int lastCount = -1;                   //Previous value of count (initialized to ensure it's different when the sketch starts)
unsigned long rpt = REPEAT_FIRST;     //A variable time that is used to drive the repeats for long presses

void setup(void)
{
    Serial.begin(115200);
}

void loop(void)
{
    btnUP.read();                             //read the buttons
    btnDN.read();
    
    if (count != lastCount) {                 //print the count if it has changed
        lastCount = count;
        Serial.println(count, DEC);
    }
    
    switch (STATE) {
        
        case WAIT:                                //wait for a button event
            if (btnUP.wasPressed())
                STATE = INCR;
            else if (btnDN.wasPressed())
                STATE = DECR;
            else if (btnUP.wasReleased())         //reset the long press interval
                rpt = REPEAT_FIRST;
            else if (btnDN.wasReleased())
                rpt = REPEAT_FIRST;
            else if (btnUP.pressedFor(rpt)) {     //check for long press
                rpt += REPEAT_INCR;               //increment the long press interval
                STATE = INCR;
            }
            else if (btnDN.pressedFor(rpt)) {
                rpt += REPEAT_INCR;
                STATE = DECR;
            }
            break;

        case INCR:                                //increment the counter
            count = min(count++, MAX_COUNT);      //but not more than the specified maximum
            STATE = WAIT;
            break;

        case DECR:                                //decrement the counter
            count = max(count--, MIN_COUNT);      //but not less than the specified minimum
            STATE = WAIT;
            break;
    }
}

