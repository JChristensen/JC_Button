# Arduino Button Library
https://github.com/JChristensen/JC_Button  
README file  

## License
Arduino Button Library Copyright (C) 2018-2019 Jack Christensen GNU GPL v3.0

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License v3.0 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/gpl.html>

## Introduction
The Button library is for debouncing and reading momentary contact switches like tactile button switches.  "Long presses" of arbitrary length can be detected. Works well in state machine constructs.  Use the read() function to read each button in the main loop, which should execute as fast as possible.

The simplest way to use a button with an AVR microcontroller is to wire the button between a GPIO pin and ground, and turn on the AVR internal pullup resistor. The Button class constructor takes four arguments, but three have default values that work for a button wired in this manner.

A derived class, ToggleButton, implements button objects that need only "push-on, push-off" functionality.

## Examples
The following example sketches are included with the **Button** library:

- **SimpleOnOff**: Just turns the Arduino's pin 13 LED on and off.
- **LongPress**: Demonstrates detecting long and short button presses.
- **UpDown**: Counts up or down, one number at a time or rapidly by holding the button down.
- **Toggle**: Demonstrates ToggleButton functionality.


## Constructors

### Button(pin, dbTime, puEnable, invert)
##### Description
The constructor defines a button object.
##### Syntax
`Button(pin, dbTime, puEnable, invert);`
##### Required parameter
**pin:** Arduino pin number that the button is connected to *(byte)*  
##### Optional parameters
**dbTime:** Debounce time in milliseconds. Defaults to 25ms if not given. *(unsigned long)*  
**puEnable:** *true* to enable the microcontroller's internal pull-up resistor, else *false*. Defaults to *true* if not given. *(bool)*  
**invert:** *false* interprets a high logic level to mean the button is pressed, *true* interprets a low level as pressed. *true* should be used when a pull-up resistor is employed, *false* for a pull-down resistor. Defaults to *true* if not given. *(bool)*
##### Returns
None.
##### Example
```c++
// button connected from pin 2 to ground, 25ms debounce, pullup enabled, logic inverted
Button myButton(2);

// same as above but this button needs a longer debounce time (50ms)
Button myButton(3, 50);

// a button wired from the MCU pin to Vcc with an external pull-down resistor
Button myButton(4, 25, false, false);

```

### ToggleButton(pin, initialState, dbTime, puEnable, invert)
##### Description
The constructor defines a toggle button object, which has "push-on, push-off" functionality. The initial state can be on or off. See the section, [ToggleButton Library Functions](https://github.com/JChristensen/JC_Button#togglebutton-library-functions) for functions that apply specifically to the ToggleButton object. The ToggleButton class is derived from the Button class, so all Button functions are available, but because it is inherently a more limited concept, the special ToggleButton functions will be most useful, along with `begin()` and `read()`.
##### Syntax
`ToggleButton(pin, initialState, dbTime, puEnable, invert);`
##### Required parameter
**pin:** Arduino pin number that the button is connected to *(byte)*  
##### Optional parameters
**initialState:** Initial state for the button. Defaults to off (false) if not given. *(bool)*  
**dbTime:** Debounce time in milliseconds. Defaults to 25ms if not given. *(unsigned long)*  
**puEnable:** *true* to enable the microcontroller's internal pull-up resistor, else *false*. Defaults to *true* if not given. *(bool)*  
**invert:** *false* interprets a high logic level to mean the button is pressed, *true* interprets a low level as pressed. *true* should be used when a pull-up resistor is employed, *false* for a pull-down resistor. Defaults to *true* if not given. *(bool)*
##### Returns
None.
##### Example
```c++
// button connected from pin 2 to ground, initial state off,
// 25ms debounce, pullup enabled, logic inverted
ToggleButton myToggle(2);

// same as above but this button is initially "on" and also
// needs a longer debounce time (50ms).
ToggleButton myToggle(3, true, 50);

// a button wired from the MCU pin to Vcc with an external pull-down resistor,
// initial state is off.
Button myButton(4, false, 25, false, false);

```

## Button Library Functions

### begin()
##### Description
Initializes the Button object and the pin it is connected to.
##### Syntax
`myButton.begin();`
##### Parameters
None.
##### Returns
None.
##### Example
```c++
myButton.begin();
```
### read()
##### Description
Reads the button and returns a *boolean* value (*true* or *false*) to indicate whether the button is pressed. The read() function needs to execute very frequently in order for the sketch to be responsive. A good place for read() is at the top of loop(). Often, the return value from read() will not be needed if the other functions below are used.
##### Syntax
`myButton.read();`
##### Parameters
None.
##### Returns
*true* if the button is pressed, else *false* *(bool)*
##### Example
```c++
myButton.read();
```

### isPressed()
### isReleased()
##### Description
These functions check the button state from the last call to `read()` and return false or true accordingly. These functions **do not** cause the button to be read.
##### Syntax
`myButton.isPressed();`  
`myButton.isReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button has been pressed (released) or not *(bool)*
##### Example
```c++
if ( myButton.isPressed() )
{
	//do something
}
else
{
	//do something else
}
```

### wasPressed()
### wasReleased()
##### Description
These functions check the button state to see if it changed between the last two calls to `read()` and return false or true accordingly. These functions **do not** cause the button to be read. Note that these functions may be more useful than `isPressed()` and `isReleased()` since they actually detect a **change** in the state of the button, which is usually what we want in order to cause some action.
##### Syntax
`myButton.wasPressed();`  
`myButton.wasReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button was pressed (released) or not *(boolean)*
##### Example
```c++
if ( myButton.wasPressed() )
{
	//do something
}
```

### pressedFor(ms)
### releasedFor(ms)
##### Description
These functions check to see if the button is pressed (or released), and has been in that state for the specified time in milliseconds. Returns false or true accordingly. These functions are useful to detect "long presses". Note that these functions **do not** cause the button to be read.
##### Syntax
`myButton.pressedFor(ms);`  
`myButton.releasedFor(ms);`
##### Parameters
**ms:** The number of milliseconds *(unsigned long)*
##### Returns
*true* or *false*, depending on whether the button was pressed (released) for the specified time *(bool)*
##### Example
```c++
if ( myButton.pressedFor(1000) )
{
    // button has been pressed for one second
}
```

### lastChange()
##### Description
Under certain circumstances, it may be useful to know when a button last changed state. `lastChange()` returns the time the button last changed state, in milliseconds (the value is derived from the Arduino millis() function).
##### Syntax
`myButton.lastChange();`
##### Parameters
None.
##### Returns
The time in milliseconds when the button last changed state *(unsigned long)*
##### Example
```c++
unsigned long msLastChange = myButton.lastChange();
```

## ToggleButton Library Functions

### changed()
##### Description
Returns a boolean value (true or false) to indicate whether the toggle button changed state the last time `read()` was called.
##### Syntax
`myToggle.changed();`
##### Parameters
None.
##### Returns
*true* if the toggle state changed, else *false* *(bool)*
##### Example
```c++
if (myToggle.changed())
{
    // do something
}
else
{
    // do something different
}
```

### toggleState()
##### Description
Returns a boolean value (true or false) to indicate the toggle button state as of the last time `read()` was called.
##### Syntax
`myToggle.toggleState();`
##### Parameters
None.
##### Returns
*true* if the toggle is "on", else *false* *(bool)*
##### Example
```c++
if (myToggle.toggleState())
{
    // do something
}
else
{
    // do something different
}
```