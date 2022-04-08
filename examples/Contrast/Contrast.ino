//-------------------------------------------------------------------------------------------
// Olav Kallhovd sept2017, Modified Srijal Poojari, April 2022
//
// Tested Module    : ERC1602-4, EASTRISING TECHNOLOGY CO,.LTD. [Srijal: Midas MCCOG21605B6W-SPTLYI. Not all functions were tested]
// Drive IC         : ST7032
// INTERFACE        : I2C
// VDD              : 2.7V-5.5V
// Tested with MCU	: Arduino Uno, Attiny85@1mhz(5.0V), Attiny85@8mhz(5.0V) and ESP8266(3.3V) [Srijal: Seeeduino XIAO]
//-------------------------------------------------------------------------------------------

#include <DISPLAY_ST7032.h>

DISPLAY_ST7032 midas_lcd;

const byte contrastButtonPin = 3;
boolean lastButtonState = 1;

void setup() {
  pinMode(contrastButtonPin, INPUT);
  digitalWrite(contrastButtonPin, HIGH);
  midas_lcd.begin();
  midas_lcd.set_contrast(8); //contrast value range is 0-63, try 25@5V or 50@3.3V as a starting value
}

void loop() {
  boolean a = digitalRead(contrastButtonPin);
  if (a != lastButtonState) {
    if (!a) {
      midas_lcd.adjust_contrast(1); //increase contrast (-1 to decrease)
    }
    lastButtonState = a;
  }

  midas_lcd.set_cursor(0, 0);  //LINE 1 ADDRESS 0
  midas_lcd.print("Contrast value:");
  midas_lcd.set_cursor(1, 0);  //LINE 2 ADDRESS 0
  byte c = midas_lcd.get_contrast();
  midas_lcd.print(c, DEC);
  midas_lcd.write(' ');

}
