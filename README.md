# LCD_ST7032
Arduino library for ST7032 LCD controller with i2c interface.

Tested with Arduino Uno, Arduino Zero, Attiny85@1mhz, Attiny85@8mhz and ESP8266 with this LCD Module: http://www.buydisplay.com/default/16x2-lcd-3-3v-character-cog-display-module-black-on-white (with 3.3V and 5V) 

Edit April 08, 2022: Also tested with the Seeeduino XIAO with the Midas MCCOG21605B6W-SPTLYI display: https://www.midasdisplays.com/product-explorer/lcds/mono-cog-character-lcds/mccog21605b/mccog21605b6w-sptlyi.

Connections for the Midas Display (Supply at 5V, I/O at 3V3):
1. Vout  --> 1uF ceramic to pin 4, VDD (5V)
2. CAP1N --> 1uF ceramic cap to pin 3
3. CAP1P --> 1uF ceramic cap to pin 2
4. VDD   --> 5V supply
5. VSS   --> GND supply
6. SDA   --> to microcontroller SDA and also pulled up to +3V3 through 4.7k Ohm resistor
7. SCL   --> to microcontroller SCL and also pulled up to +3V3 through 4.7k Ohm resistor
8. RESET --> (active low) 1k Ohm resistor to +3V3