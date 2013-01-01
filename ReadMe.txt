ReadMe file for Arduino Button Library v1.0
https://github.com/JChristensen/Button
Jack Christensen Mar 2012

This work is licensed under the Creative Commons Attribution-ShareAlike 3.0
Unported License. To view a copy of this license, visit
http://creativecommons.org/licenses/by-sa/3.0/ or send a letter to Creative
Commons, 171 Second Street, Suite 300, San Francisco, California, 94105, USA.

--------------------------------------------------------------------------------
Arduino library for debouncing and reading momentary contact switches like
tactile button switches.  "Long presses" of arbitrary length can be detected.
Works well in state machine constructs.  Use the read() function to read each
button in the main loop, which should execute as fast as possible.

--------------------------------------------------------------------------------
To use the library:
(1) Go to https://github.com/JChristensen/Button and click the ZIP button to
download the repository as a ZIP file to a convenient location on your PC.
(2) Uncompress the downloaded file. This will result in a folder containing all
the files for the library, that has a name that includes the branch name,
for example "Button-master".
(3) Rename the folder to just "Button".
(4) Copy the renamed folder to the Arduino sketchbook\libraries folder.

--------------------------------------------------------------------------------
The following example sketches are included with the Button library:

SimpleOnOff: Just turns the Arduino's pin 13 LED on and off.

LongPress: Demonstrates detecting long and short button presses.

UpDown: Counts up or down, one number at a time or rapidly by holding the button
down.

--------------------------------------------------------------------------------
Declare button objects as follows.

Button(pin, puEnable, invert, dbTime) instantiates a button object.

Where:
pin -- Is the Arduino pin the button is connected to,

puEnable -- Enables the AVR internal pullup resistor if != 0 (can also use true
or false),

invert -- If invert == 0, a high state is interpreted as pressed, low as
released. If invert != 0, a high state is interpreted as released, low as
pressed (can also use true or false), and

dbTime   Is the debounce time in milliseconds.

Example. Wire a normally-open tactile button switch between Arduino pin 2 and
ground.  We will use the internal pullup resistor, so the pin will be high when
the button is not pressed, and low when the button is pressed.  Therefore we
should use invert == true to invert the logic:

Button myButton = Button(2, true, true, 25);

--------------------------------------------------------------------------------
The read() method reads the button and returns a boolean value (true or false)
to indicate whether the button is pressed.  The read() function needs to execute
very frequently in order for the sketch to be responsive.  A good place for
read() is at the top of loop().  I don't normally use the return value from
read(), because I use the other functions.

Example:    myButton.read();

--------------------------------------------------------------------------------
The isPressed() and isReleased() functions check the button state when it was
last read, and return false or true accordingly.  These functions DO NOT cause
the button to be read.

Example:    if ( myButton.isPressed ) {
                //do some stuff
            }
            else {
                //do some different stuff
            }

--------------------------------------------------------------------------------
The wasPressed() and wasReleased() functions check the button state to see if it
changed between the last two reads and return false or true accordingly.  These
functions DO NOT cause the button to be read.  Note that these functions may be
more useful than isPressed() and isReleased() since they actually detect a
CHANGE in the state of the button, which is usually what we want in order to
cause some action.

Example:    if ( myButton.wasPressed() ) { ...

--------------------------------------------------------------------------------
The pressedFor(ms) and releasedFor(ms) functions check to see if the button is
pressed (or released), and has been in that state for the specified time in
milliseconds.  Returns false or true accordingly.  These functions are useful to
detect "long presses".  Note that these functions DO NOT cause the button to be
read.

Example:    if ( myButton.pressedFor(1000) ) {  //has button been pressed
                                                //for one second?

--------------------------------------------------------------------------------
Under certain circumstances, it may be useful to know when a button last changed
state.  lastChange() returns the time the button last changed state, in
mlliseconds (the value is from the Arduino millis() function).

Example:    unsigned long lastChange = myButton.lastChange();

--------------------------------------------------------------------------------
