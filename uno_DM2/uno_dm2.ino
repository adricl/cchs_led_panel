/*
  Scrolling alphabet demo, displays characters one at a time into a scrolling box.
 */

#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>
#include <CircularBuffer.h>

// Buffer for messages from serial
CircularBuffer<char, 1500> messages;

// Set Width to the number of displays wide you have
const int WIDTH = 2;

// You can change to a smaller font (two lines) by commenting this line,
// and uncommenting the line after it:
const uint8_t *FONT = Arial14;
//const uint8_t *FONT = SystemFont5x7;

SoftDMD dmd(WIDTH,1);  // DMD controls the entire display
DMD_TextBox box(dmd);  // "box" provides a text box to automatically write to/scroll the display

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  dmd.setBrightness(150);
  dmd.selectFont(FONT);
  dmd.begin();
}

// the loop routine runs over and over again forever:
void loop() {

  byte av_count = Serial1.available();//checking if charcater has come from InputBox of Serial Monitor 
  for(int i = 0; i < av_count; i++){
    byte bt = Serial1.read();
    messages.push(bt);
    Serial.write(bt);
  }

  if (!messages.isEmpty()) {
    char letter = messages.shift();
    Serial1.print(letter);
    box.print(letter);
  }
  else {
    box.clear();
  }
  delay(200);
}