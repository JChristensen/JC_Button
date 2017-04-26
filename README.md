# Arduino Button Library v1.0
https://github.com/JChristensen/Button    
ReadMe file  
Jack Christensen Mar 2012

![CC BY-SA](http://mirrors.creativecommons.org/presskit/buttons/80x15/png/by-sa.png)

## Introduction
The Button library is for debouncing and reading momentary contact switches like tactile button switches.  "Long presses" of arbitrary length can be detected. Works well in state machine constructs.  Use the read() function to read each button in the main loop, which should execute as fast as possible.

## Installation
To use the **Button** library:  
- Go to https://github.com/JChristensen/Button, click the **Download ZIP** button and save the ZIP file to a convenient location on your PC.
- Uncompress the downloaded file.  This will result in a folder containing all the files for the library, that has a name that includes the branch name, usually **Button-master**.
- Rename the folder to just **Button**.
- Copy the renamed folder to the Arduino sketchbook\libraries folder.

## Examples
The following example sketches are included with the **Button** library:

- **SimpleOnOff**: Just turns the Arduino's pin 13 LED on and off.
- **LongPress**: Demonstrates detecting long and short button presses.
- **UpDown**: Counts up or down, one number at a time or rapidly by holding the button down.

## Button library methods

### Button(pin, puEnable, invert, dbTime)
##### Description
The constructor defines a button object.
##### Syntax
`Button(pin, puEnable, invert, dbTime);`
##### Parameters
**pin:** Arduino pin number that the button is connected to *(byte)*
**puEnable:** *true* to enable the microcontroller's internal pull-up resistor, else *false* *(boolean)*
invert: *false* interprets a high logic level to mean the button is pressed, *true* interprets a low level as pressed. *true* should be used when a pull-up resistor is employed, *false* for a pull-down resistor. *(boolean)*
**dbTime:** Debounce time in milliseconds *(unsigned long)*
##### Returns
None.
##### Example
```c++
Button myButton = Button(2, true, true, 25);	//25 ms debounce
```

### read(void)
##### Description
Reads the button and returns a *boolean* value (*true* or *false*) to indicate whether the button is pressed. The read() function needs to execute very frequently in order for the sketch to be responsive. A good place for read() is at the top of loop(). Often, the return value from read() will not be needed if the other functions below are used.
##### Syntax
`myButton.read();`
##### Parameters
None.
##### Returns
*true* if the button is pressed, *else* false *(boolean)*
##### Example
```c++
myButton.read();
```

### isPressed(void)
### isReleased(void)
##### Description
These methods check the button state at the point in time when it was last read, and return false or true accordingly. These functions **do not** cause the button to be read.
##### Syntax
`myButton.isPressed();`
`myButton.isReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button has been pressed (released) or not *(boolean)*
##### Example
```c++
if ( myButton.isPressed() ) {
	//do some stuff
}
else {
	//do some different stuff
}
```

### wasPressed(void)
### wasReleased(void)
##### Description
These methods check the button state to see if it changed between the last two reads and return false or true accordingly. These functions **do not** cause the button to be read. Note that these functions may be more useful than `isPressed()` and `isReleased()` since they actually detect a **change** in the state of the button, which is usually what we want in order to cause some action.
##### Syntax
`myButton.wasPressed();`
`myButton.wasReleased();`
##### Parameters
None.
##### Returns
*true* or *false*, depending on whether the button was pressed (released) or not *(boolean)*
##### Example
```c++
if ( myButton.wasPressed() ) { ...
```

### pressedFor(ms)
### releasedFor(ms)
##### Description
These methods check to see if the button is pressed (or released), and has been in that state for the specified time in milliseconds. Returns false or true accordingly. These functions are useful to detect "long presses". Note that these functions **do not** cause the button to be read.
##### Syntax
`myButton.pressedFor(ms);`
`myButton.releasedFor(ms);`
##### Parameters
**ms:** The number of milliseconds *(unsigned long)*
##### Returns
*true* or *false*, depending on whether the button was pressed (released) for the specified time *(boolean)*
##### Example
```c++
if ( myButton.pressedFor(1000) ) {  //has the button been pressed for one second?
```

### lastChange(void)
##### Description
Under certain circumstances, it may be useful to know when a button last changed state. lastChange() returns the time the button last changed state, in milliseconds (the value is derived from the Arduino millis() function).
##### Syntax
`myButton.lastChange();`
##### Parameters
None.
##### Returns
The time in milliseconds when the button last changed state *(unsigned long)*
##### Example
```c++
unsigned long lastChange = myButton.lastChange();
```
