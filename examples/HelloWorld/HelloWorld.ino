//-------------------------------------------------------------------------------------------
// Olav Kallhovd sept2017, Modified Srijal Poojari, April 2022
//
// Tested Module    : ERC1602-4, EASTRISING TECHNOLOGY CO,.LTD. [Srijal: Midas MCCOG21605B6W-SPTLYI. Not all functions were tested]
// Drive IC         : ST7032
// INTERFACE        : I2C
// VDD              : 2.7V-5.5V
// Tested with MCU	: Arduino Uno, Attiny85@1mhz(5.0V), Attiny85@8mhz(5.0V) and ESP8266(3.3V) [Srijal: Seeeduino XIAO]
//-------------------------------------------------------------------------------------------

#include <LCD_ST7032.h>

LCD_ST7032 midas_lcd;

void setup() {
  midas_lcd.begin();
  midas_lcd.set_contrast(8); //contrast value range is 0-63, value = 8 worked well for the Midas display with the Seeeduino XIAO.
}

void loop() {
  static int counter = 0;
  
  // Write a piece of text on the first line...
  midas_lcd.set_cursor(0, 0);  //LINE 1, ADDRESS 0
  midas_lcd.print("Hello World!");

  // Write the counter on the second line...
  midas_lcd.set_cursor(1, 0);
  midas_lcd.print(counter/10, DEC);
  midas_lcd.write('.');
  midas_lcd.print(counter%10, DEC);
  midas_lcd.write(' ');
  delay(500);
  counter++;
}