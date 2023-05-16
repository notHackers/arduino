// Libraries for keyboard
#include<Keyboard.h>

// Pin's for Running Scripts
const int MacPin = 8;
const int WindowsPin = 9;
const int PhotoresistorPin = A0;

bool executed = false;

void setup() {

  Serial.begin(9600);

  // Declaring Input/Out Pins
  pinMode(10, INPUT);
  pinMode(MacPin, INPUT);
  pinMode(WindowsPin, INPUT);
  pinMode(4, OUTPUT);
  delay(200);

}

void keyPress(char key1, int timeDelay = 500) {
  Keyboard.press(key1);
  Keyboard.releaseAll();
  delay(timeDelay);
}

// Void loop runs repeatedly.
void loop() {

  // Only if the MacPin is on AND it hasn't run once.
  if (digitalRead(MacPin) == HIGH && executed == false) {
    delay(200);
    keyPress(KEY_LEFT_GUI); // Windows button
    Keyboard.print("defender settings"); // Types "defender settings" in Windows prompt
    enter();
    delay(3000); 
    enter(); // Opens virus protection
    keyPress(KEY_TAB, 100); // Uses tab to navigatve to "manage settings"
    keyPress(KEY_TAB, 100);
    keyPress(KEY_TAB, 100);
    enter();
    keyPress(' '); // Toggles "real time security" off 
    delay(1000); 
    keyPress(KEY_TAB, 100); // Chooses "Yes" wheb Windows defender asks user to allow changes
    keyPress(KEY_TAB, 100);
    enter();
    twoKeys(KEY_LEFT_ALT, KEY_F4, 300); // Closes Window

    executed = true;
  }


  // Only if the WindowsPin is on AND it hasn't run once.
  else if (digitalRead(WindowsPin) == HIGH && executed == false) {
    // No additional script.

    executed = true;
  }


  else if (digitalRead(MacPin) == LOW && digitalRead(WindowsPin) == LOW) {
    //Serial.println("Off!");

    executed = false;

  }

}

// Useful Functions
 
// Pressing Two Keys
void twoKeys(char key1, char key2, int postdelay) {
  delay(1000);
  Keyboard.press(key1);
  delay(100);
  Keyboard.press(key2);
  delay(100);
  Keyboard.releaseAll();
  delay(postdelay);
}

// Enter
void enter() {
  delay(1000);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.release(KEY_RETURN);
  delay(1000);

}
