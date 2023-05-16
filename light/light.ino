#include<Keyboard.h>
#include <Mouse.h>
#include <SPI.h>
#include <SD.h>

File myFile;
// Pin's for Running Scripts
const int MacPin = 8;

const int WindowsPin = 9;
const int PhotoresistorPin = A0;

bool executed = false;

void setup() {

  // Maybe change Serial to 3000 later
  Serial.begin(9600);

}

// Void loop runs repeatedly.
void loop() {

  // Only if the MacPin is on AND it hasn't run once.
  if (digitalRead(MacPin) == HIGH && executed == false) {
    light();
    executed = true;
   
  }

  // Only if the WindowsPin is on AND it hasn't run once.
  else if (digitalRead(WindowsPin) == HIGH && executed == false) {

    executed = true;
  }


  else if (digitalRead(MacPin) == LOW && digitalRead(WindowsPin) == LOW) {

    executed = false;

  }

}

// Functions

// Click when light
void light() {

  for (int i=0; true; i++) {
    Serial.println(analogRead(PhotoresistorPin)); // Prints the "brightness" in serial. 
    delay(100);

    Mouse.move(5 * cos(PI * i), 5 * cos(PI * i), 0); // Oscillates the mouse.

    if (analogRead(PhotoresistorPin) < 40) {
      Serial.println("Lights off");
      delay(100);
    }
    else if (analogRead(PhotoresistorPin) >= 40) {
      Serial.println("Lights On");
      Serial.println(analogRead(PhotoresistorPin));
      delay(500);
      Mouse.press(MOUSE_LEFT);
      delay(100);
      Mouse.release();
      break;

    }
  }
}
