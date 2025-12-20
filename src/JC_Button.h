// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#ifndef JC_BUTTON_H_INCLUDED
#define JC_BUTTON_H_INCLUDED

#include <Arduino.h>

class Button
{
    public:
        // Button(pin, dbTime, puEnable, invert) instantiates a button object.
        //
        // Required parameter:
        // pin      The Arduino pin the button is connected to
        //
        // Optional parameters:
        // dbTime   Debounce time in milliseconds (default 25ms, max 65535ms)
        // puEnable true to enable the AVR internal pullup resistor (default true)
        // invert   true to interpret a low logic level as pressed (default true)
        Button(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert), m_state(false), m_changed(false)
        {
            if (dbTime > UINT16_MAX)
                m_dbTime = UINT16_MAX; // value limited to 16 bits
        }

        // Initialize a Button object
        void begin();

        // Returns the state of the button, true if pressed, false if released.
        // Does debouncing, captures and maintains times, previous state, etc.
        // Call this function frequently to ensure the sketch is responsive to user input.
        bool read();

        // Returns true if the button state was pressed at the last call to read().
        // Does not cause the button to be read.
        bool isPressed() const {return m_state;}

        // Returns true if the button state was released at the last call to read().
        // Does not cause the button to be read.
        bool isReleased() const {return !m_state;}

        // These functions check the button state to see if it changed
        // between the last two reads and return true or false accordingly.
        // These functions do not cause the button to be read.
        bool wasPressed() const {return m_state && m_changed;}
        bool wasReleased() const {return !m_state && m_changed;}

        // Returns true if the button state at the last call to read() was pressed,
        // and has been in that state for at least the given number of milliseconds.
        // This function does not cause the button to be read.
        bool pressedFor(uint32_t ms) const {return m_state && (millis() - m_lastChange) >= ms;}

        // Returns true if the button state at the last call to read() was released,
        // and has been in that state for at least the given number of milliseconds.
        // This function does not cause the button to be read.
        bool releasedFor(uint32_t ms) const {return !m_state && (millis() - m_lastChange) >= ms;}

        // Returns the time in milliseconds (from millis) that the button last
        // changed state.
        uint32_t lastChange() const {return m_lastChange;}

    private:
        uint8_t m_pin;                  // arduino pin number connected to button
        uint16_t m_dbTime;              // debounce time (ms)
        bool m_puEnable : 1;            // internal pullup resistor enabled
        bool m_invert : 1;              // if true, interpret logic low as pressed, else interpret logic high as pressed
        bool m_state : 1;               // current button state, true=pressed
        bool m_changed : 1;             // state changed since last read
        uint32_t m_lastChange {0};      // time of last state change (from millis)
        uint32_t m_dbStart {0};         // debounce interval start time. debouncing when: dbStart!=lastChange
};

// a derived class for a "push-on, push-off" (toggle) type button.
// initial state can be given, default is off (false).
class ToggleButton : public Button
{
    public:

        // constructor is similar to Button, but includes the initial state for the toggle.
        ToggleButton(uint8_t pin, bool initialState=false, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : Button(pin, dbTime, puEnable, invert), m_toggleState(initialState) {}

        // read the button and return its state.
        // should be called frequently.
        bool read()
        {
            Button::read();
            if (wasPressed()) {
                m_toggleState = !m_toggleState;
            }
            return m_toggleState;
        }

        // has the state changed?
        bool changed() const {return wasPressed();} // the state changes only when wasPressed()

        // return the current state
        bool toggleState() const {return m_toggleState;}

    private:
        bool m_toggleState;
};
#endif
