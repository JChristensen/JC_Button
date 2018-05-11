// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Library for reading momentary contact switches like tactile button
// switches. Intended for use in state machine constructs.
// Use the read() function to read each button in the main loop,
// which should execute as fast as possible.

#include "JC_Button.h"

/*----------------------------------------------------------------------*
 * Button(pin, puEnable, invert, dbTime) instantiates a button object.  *
 * pin      Is the Arduino pin the button is connected to.              *
 * puEnable Enables the AVR internal pullup resistor if != 0 (can also  *
 *          use true or false).                                         *
 * invert   If invert == 0, interprets a high state as pressed, low as  *
 *          released. If invert != 0, interprets a high state as        *
 *          released, low as pressed  (can also use true or false).     *
 * dbTime   Is the debounce time in milliseconds.                       *
 *                                                                      *
 * (Note that invert cannot be implied from puEnable since an external  *
 *  pullup could be used.)                                              *
 *----------------------------------------------------------------------*/

void Button::begin()
{
    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
    m_state = digitalRead(m_pin);
    if (m_invert) m_state = !m_state;
    m_time = millis();
    m_lastState = m_state;
    m_changed = false;
    m_lastChange = m_time;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true==pressed, false==released,      *
/ does debouncing, captures and maintains times, previous states, etc.  *
/-----------------------------------------------------------------------*/
bool Button::read()
{
    uint32_t ms = millis();
    uint8_t pinVal = digitalRead(m_pin);
    if (m_invert) pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_time = ms;
        m_changed = false;
        return m_state;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_time = ms;
        m_changed = (m_state != m_lastState);
        if (m_changed) m_lastChange = ms;
        return m_state;
    }
}

/*----------------------------------------------------------------------*
 * isPressed() and isReleased() check the button state when it was last *
 * read, and return false (0) or true (!=0) accordingly.                *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::isPressed()
{
    return m_state;
}

bool Button::isReleased()
{
    return m_state;
}

/*----------------------------------------------------------------------*
 * wasPressed() and wasReleased() check the button state to see if it   *
 * changed between the last two reads and return false (0) or           *
 * true (!=0) accordingly.                                              *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::wasPressed()
{
    return m_state && m_changed;
}

bool Button::wasReleased()
{
    return !m_state && m_changed;
}

/*----------------------------------------------------------------------*
 * pressedFor(ms) and releasedFor(ms) check to see if the button is     *
 * pressed (or released), and has been in that state for the specified  *
 * time in milliseconds. Returns false (0) or true (!=0) accordingly.   *
 * These functions do not cause the button to be read.                  *
 *----------------------------------------------------------------------*/
bool Button::pressedFor(uint32_t ms)
{
    return m_state && m_time - m_lastChange >= ms;
}

bool Button::releasedFor(uint32_t ms)
{
    return !m_state && m_time - m_lastChange >= ms;
}

/*----------------------------------------------------------------------*
 * lastChange() returns the time the button last changed state,         *
 * in milliseconds.                                                     *
 *----------------------------------------------------------------------*/
uint32_t Button::lastChange()
{
    return m_lastChange;
}
