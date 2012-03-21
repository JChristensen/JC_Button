/*----------------------------------------------------------------------*
 * button.cpp -- Library for reading momentary contact switches like	*
 * tactile button switches.	Intended for use in state machine 			*
 * constructs.  Use the read() function to read all buttons in the 		*
 * main loop, which should execute as fast as possible, or at least		*
 * very frequently.														*
 *																		*
 * Jack Christensen 11May2011											*
 *                                                                      *
 * This work is licensed under the Creative Commons Attribution-        *
 * ShareAlike 3.0 Unported License. To view a copy of this license,     *
 * visit http://creativecommons.org/licenses/by-sa/3.0/ or send a       *
 * letter to Creative Commons, 171 Second Street, Suite 300,            *
 * San Francisco, California, 94105, USA.                               *
 *----------------------------------------------------------------------*/
#include "WProgram.h"
#include "button.h"

//the constructor button(pin, puEnabled, invert, dbTime) instantiates a button object.
//pin is the Arduino pin the button is connected to.
//puEnabled enables the AVR internal pullup resistor if != 0 (can use true or false).
//invert = 0 interprets a high state as pressed, low as released.
//invert != 0 interprets a high state as released, low as pressed  (can use true or false).
//dbTime is the debounce time in milliseconds.
//note that invert cannot be implied from puEnabled since an external pullup could be used.
button::button(uint8_t pin, uint8_t puEnabled, uint8_t invert, uint32_t dbTime)
{
	_pin = pin;
	_puEnabled = puEnabled;
	_invert = invert;
	_dbTime = dbTime;
	pinMode(_pin, INPUT);
    if (_puEnabled != 0)
    	digitalWrite(_pin, HIGH);		//enable pullup resistor
	_state = digitalRead(_pin);
	if (_invert != 0) _state = !_state;
	_time = millis();
	_lastState = _state;
	_changed = 0;
	_lastTime = _time;
	_lastChange = _time;
}

//read() returns the state of the button 1 (pressed), or 0 (released),
//does debouncing, and also captures and maintains times, previous states, etc.
uint8_t button::read(void)
{
	static uint32_t ms;
	static uint8_t pinVal;

	ms = millis();
	pinVal = digitalRead(_pin);
	if (_invert != 0) pinVal = !pinVal;
	if (ms < _lastChange + _dbTime) {
		_lastTime = _time;
		_time = ms;
		_changed = 0;
		return _state;
	}
	else {
		_lastTime = _time;
		_lastState = _state;
		_state = pinVal;
		_time = ms;
		if (_state != _lastState)	{
			_lastChange = ms;
			_changed = 1;
		}
		else {
			_changed = 0;
		}
		return _state;
	}
}

//isPressed() and isReleased() check the button state when it was last read,
//and return false (0) or true (!=0) accordingly.
//These functions do not cause the button to be read.
uint8_t button::isPressed(void)
{
	return _state == 0 ? 0 : 1;
}

uint8_t button::isReleased(void)
{
	return _state == 0 ? 1 : 0;
}

//wasPressed() and wasReleased() check the button state to see if it changed
//between the last two reads and return false (0) or true (!=0) accordingly.
//These functions do not cause the button to be read.
uint8_t button::wasPressed(void)
{
	return _state && _changed;
}

uint8_t button::wasReleased(void)
{
	return !_state && _changed;
}

//pressedFor(ms) and releasedFor(ms) check to see if the button is pressed (or released),
//and has been in that state for the specified time. Returns false (0) or true (1) accordingly.
//These functions do not cause the button to be read.
uint8_t button::pressedFor(uint32_t ms)
{
	return (_state == 1 && _time - _lastChange >= ms) ? 1 : 0;
}

uint8_t button::releasedFor(uint32_t ms)
{
	return (_state == 0 && _time - _lastChange >= ms) ? 1 : 0;
}

//lastChange() returns the time of the last state change in milliseconds.
uint32_t button::lastChange(void)
{
	return _lastChange;
}
