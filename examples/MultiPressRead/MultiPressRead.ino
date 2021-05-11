// Arduino Button Library
// https://github.com/JChristensen/JC_Button
// Copyright (C) 2018 by Jack Christensen and licensed under
// GNU GPL v3.0, https://www.gnu.org/licenses/gpl.html
//
// Example of the multiPressRead() functionality added by Kuan Liu
// returns the number of presses in fast succession

#include <JC_Button.h>          // https://github.com/Kuantronic/JC_Button

// button pin assignment
#define BUTTON_PIN 7              // connect a button switch from this pin to ground

Button myBtn(BUTTON_PIN);       // define the button

void setup(){
  Serial.begin(115200);           //initalize serial at 115200 baud rate
  myBtn.begin();                  //initialize the button object

  //uncomment the line below to set the time allowed between presses.
  //myBtn.setMultiPressTimer(150);  // default time is 200ms if this function is not called.
  
  //the shorter the time, the more responsive it becomes to returning the number of counts
  //BUT if it gets too short, it becomes more likely the fast presses will NOT count towards the succession
}

void loop(){
  uint8_t numOfPresses = myBtn.multiPressRead();

  switch (numOfPresses){
    case 1:
      Serial.println("single press!");
      break;
    case 2:
      Serial.println("double press!");
      break;
    case 3:
      Serial.println("triple press!");
      break;
    case 4:
      Serial.println("quadruple press!");
    default:
      // do nothing
      // for no press and presses over 4 in fast succession
      break;
  }

}
