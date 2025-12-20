// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "JC_Button.h"

// initialize a Button object
void Button::begin()
{
    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
    m_state = static_cast<bool>(digitalRead(m_pin)) ^ m_invert;
    m_changed = false;
    m_lastChange = millis();
    m_dbStart = m_lastChange; // no debouncing
}

// returns the state of the button, true if pressed, false if released.
// does debouncing, captures and maintains times, previous state, etc.
bool Button::read()
{
    uint32_t now = millis();
    bool pinVal = static_cast<bool>(digitalRead(m_pin)) ^ m_invert;

    m_changed = false; // clear any previous state change

    if (m_dbStart != m_lastChange) {
        // debouncing mode
        if (pinVal != m_state) {
            // pinVal differs - still debouncing
            if (now - m_dbStart >= m_dbTime) {
                // pinVal is stable for enough time => change state
                m_state = pinVal;
                m_changed = true;
                m_lastChange = now;
                m_dbStart = m_lastChange; // no debouncing
            }
        }
        else {
            // pinVal returned back to a previous state
            m_dbStart = m_lastChange; // end debouncing
        }
    }
    else {
        // we are in a stable state mode
        if (pinVal != m_state) {
            // change on input => start debouncing
            m_dbStart = now;
        }
        else {
            // nothing happens
        }
    }
    return m_state;
}
