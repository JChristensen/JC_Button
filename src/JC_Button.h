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
        Button::Button(uint8_t pin, uint32_t dbTime=25, uint8_t puEnable=true, uint8_t invert=true)
            : m_pin(pin), m_dbTime(dbTime), m_puEnable(puEnable), m_invert(invert) {}
        void begin();
        bool read();
        bool isPressed();
        bool isReleased();
        bool wasPressed();
        bool wasReleased();
        bool pressedFor(uint32_t ms);
        bool releasedFor(uint32_t ms);
        uint32_t lastChange();
    
    private:
        uint8_t m_pin;          // arduino pin number connected to button
        bool m_puEnable;        // internal pullup resistor enabled
        bool m_invert;          // if true, interpret logic low as pressed, else interpret logic high as pressed
        bool m_state;           // current button state, true=pressed
        bool m_lastState;       // previous button state
        bool m_changed;         // state changed since last read
        uint32_t m_time;        // time of current state (ms from millis)
        uint32_t m_lastChange;  // time of last state change (ms)
        uint32_t m_dbTime;      // debounce time (ms)
};
#endif
