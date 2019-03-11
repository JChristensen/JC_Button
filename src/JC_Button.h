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
        // dbTime   Debounce time in milliseconds (default 25ms)
        // puEnable true to enable the AVR internal pullup resistor (default true)
        // invert   true to interpret a low logic level as pressed (default true)
        Button(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert) {}

        // Initialize a Button object and the pin it's connected to
        void begin();

        // Returns the current debounced button state, true for pressed,
        // false for released. Call this function frequently to ensure
        // the sketch is responsive to user input.
        bool read();

        // Returns true if the button state was pressed at the last call to read().
        // Does not cause the button to be read.
        bool isPressed();

        // Returns true if the button state was released at the last call to read().
        // Does not cause the button to be read.
        bool isReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and this was a change since the previous read.
        bool wasPressed();

        // Returns true if the button state at the last call to read() was released,
        // and this was a change since the previous read.
        bool wasReleased();

        // Returns true if the button state at the last call to read() was pressed,
        // and has been in that state for at least the given number of milliseconds.
        bool pressedFor(uint32_t ms);

        // Returns true if the button state at the last call to read() was released,
        // and has been in that state for at least the given number of milliseconds.
        bool releasedFor(uint32_t ms);

        // Returns the time in milliseconds (from millis) that the button last
        // changed state.
        uint32_t lastChange();

    private:
        uint8_t m_pin;          // arduino pin number connected to button
        uint32_t m_dbTime;      // debounce time (ms)
        bool m_puEnable;        // internal pullup resistor enabled
        bool m_invert;          // if true, interpret logic low as pressed, else interpret logic high as pressed
        bool m_state;           // current button state, true=pressed
        bool m_lastState;       // previous button state
        bool m_changed;         // state changed since last read
        uint32_t m_time;        // time of current state (ms from millis)
        uint32_t m_lastChange;  // time of last state change (ms)
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
            if (wasPressed())
            {
                m_toggleState = !m_toggleState;
                m_changed = true;
            }
            else
            {
                m_changed = false;
            }
            return m_toggleState;
        }

        // has the state changed?
        bool changed() {return m_changed;}

        // return the current state
        bool toggleState() {return m_toggleState;}

    private:
        bool m_toggleState;
        bool m_changed;
};
#endif
