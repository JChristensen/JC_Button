// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html

#include "JC_Button.h"

/*----------------------------------------------------------------------*
/ initialize a Button object and the pin it's connected to.             *
/-----------------------------------------------------------------------*/
void Button::begin()
{
    pinMode(m_pin, m_puEnable ? INPUT_PULLUP : INPUT);
    m_state = digitalRead(m_pin);
    if (m_invert) m_state = !m_state;
    m_time = millis();
    m_lastState = m_state;
    m_changed = false;
    m_lastChange = m_time;

    m_pressCount = 0;
    pressRead = false;
}

/*----------------------------------------------------------------------*
/ returns the state of the button, true if pressed, false if released.  *
/ does debouncing, captures and maintains times, previous state, etc.   *
/-----------------------------------------------------------------------*/
bool Button::read()
{
    uint32_t ms = millis();
    bool pinVal = digitalRead(m_pin);
    if (m_invert) pinVal = !pinVal;
    if (ms - m_lastChange < m_dbTime)
    {
        m_changed = false;
    }
    else
    {
        m_lastState = m_state;
        m_state = pinVal;
        m_changed = (m_state != m_lastState);
        if (m_changed) m_lastChange = ms;
    }
    m_time = ms;
    return m_state;
}

/*----------------------------------------------------------------------*
 * multiPressRead() checks the time between changes in the m_state      *
 * If it changes quick enough, it'll detect it as a multi presses       *
 * If a set time passes without another press, it'll return the times   *
 * it got multi-pressed
 *----------------------------------------------------------------------*/
uint8_t Button::multiPressRead() {

    if (read()) {
        //makes sure it counts the press ONLY once
        if (!m_pressRead) {
            m_pressCount++;
            m_pressRead = true;
        }
        return checkMultiPress();
    }

    if (!read()) {
        m_pressRead = false;
        return checkMultiPress();
    }
}

/*----------------------------------------------------------------------*
 * Checks the time that passed without another press. If it exceeds the *
 * limit, it returns the amount of fast presses it counted.             *
 *----------------------------------------------------------------------*/
uint8_t Button::checkMultiPress() {

    if (millis() - m_lastChange > m_multiPressTimeLimit) {
        uint8_t numberOfPresses = m_pressCount;
        m_pressCount = 0;
        return numberOfPresses;
    }
    else {
        return 0;
    }
}

/*----------------------------------------------------------------------*
 * Sets the time in ms for the next button press to be counted as       *
 * a successive multi press.                                            *
 *----------------------------------------------------------------------*/
void Button::setMultiPressTimer(uint32_t multiPressTimeLimit) {
    m_multiPressTimeLimit = multiPressTimeLimit;
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
    return !m_state;
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
