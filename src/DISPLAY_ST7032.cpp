//-------------------------------------------------------------------------------------------
// DISPLAY_ST7032.h - Arduino i2c master library for LCD ST7032
// Olav Kallhovd sept2017, Modified Srijal Poojari, April 2022
//
// Tested Module    : ERC1602-4, EASTRISING TECHNOLOGY CO,.LTD. [Srijal: Midas MCCOG21605B6W-SPTLYI. Not all functions were tested]
// Drive IC         : ST7032
// INTERFACE        : I2C
// VDD              : 2.7V-5.5V
// Tested with MCU	: Arduino Uno, Attiny85@1mhz(5.0V), Attiny85@8mhz(5.0V) and ESP8266(3.3V) [Srijal: Seeeduino XIAO]
//-------------------------------------------------------------------------------------------

#include <Arduino.h>
#include <DISPLAY_ST7032.h>
#if defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) \
    || defined(__AVR_ATtiny84__) || defined(__AVR_ATtiny25__) \
    || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__) \
    || defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__) \
    || defined(__AVR_ATtiny87__) || defined(__AVR_ATtiny167__) \
    || defined( __AVR_ATtiny261__ ) || defined( __AVR_ATtiny461__ ) \
    || defined( __AVR_ATtiny861__ ) || defined(__AVR_ATtiny1634__)
#include <USIWire.h>
#else
#include <Wire.h>
#endif

DISPLAY_ST7032::DISPLAY_ST7032() 
{ 
} 

void DISPLAY_ST7032::begin() 
{
	Wire.begin();
	delay(100);
    write_instruction(FUNCTION_SET | FUNCTION_SET_DL | FUNCTION_SET_N | FUNCTION_SET_IS);
    write_instruction(INTERNAL_OSC_FREQ | INTERNAL_OSC_FREQ_BS | INTERNAL_OSC_FREQ_F2);
    write_instruction(POWER_ICON_BOST_CONTR | POWER_ICON_BOST_CONTR_Ion);
    set_contrast(contrast);
    write_instruction(FOLLOWER_CONTROL | FOLLOWER_CONTROL_Fon | FOLLOWER_CONTROL_Rab2);
    delay(300);
    write_instruction(display_on_off_setting);
	write_instruction(ENTRY_MODE_SET | ENTRY_MODE_SET_ID); 
    this->clear(); 
	this->home();
}	

void DISPLAY_ST7032::write_instruction(uint8_t cmd)
{
	Wire.beginTransmission(write_address);
	Wire.write(CNTRBIT_CO);  
	Wire.write(cmd);
	Wire.endTransmission();
	delayMicroseconds(WRITE_DELAY_MS);
}

void DISPLAY_ST7032::write_data(uint8_t data)
{
	Wire.beginTransmission(write_address);
	Wire.write(CNTRBIT_RS); 
	Wire.write(data);
	Wire.endTransmission();
	delayMicroseconds(WRITE_DELAY_MS);
}

size_t DISPLAY_ST7032::write(uint8_t chr) 
{
	this->write_data(chr);
	return 1;
}

void DISPLAY_ST7032::clear() { //clear display
	this->write_instruction(CLEAR_DISPLAY);
	delayMicroseconds(HOME_CLEAR_DELAY_MS);
}

void DISPLAY_ST7032::home() { //return to first line address 0
	this->write_instruction(RETURN_HOME);
	delayMicroseconds(HOME_CLEAR_DELAY_MS);
}

void DISPLAY_ST7032::set_cursor(uint8_t line, uint8_t pos) 
{
	uint8_t p;
	if(pos > 15) pos = 0;
	if(line == 0) p = LINE_1_ADR + pos;
	else p = LINE_2_ADR + pos;
	write_instruction(SET_DDRAM_ADDRESS | p);
}

void DISPLAY_ST7032::display() //turn on display
{ 
	display_on_off_setting |= DISPLAY_ON_OFF_D;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::no_display() //turn off display
{ 
	display_on_off_setting &= ~DISPLAY_ON_OFF_D;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::cursor() //display underline cursor
{ 
	display_on_off_setting |= DISPLAY_ON_OFF_C;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::no_cursor() //stop display underline cursor
{ 
	display_on_off_setting &= ~DISPLAY_ON_OFF_C;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::blink() //cursor block blink
{ 
	display_on_off_setting |= DISPLAY_ON_OFF_B;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::no_blink() //stop cursor block blink
{ 
	display_on_off_setting &= ~DISPLAY_ON_OFF_B;
	write_instruction(display_on_off_setting);
}

void DISPLAY_ST7032::set_contrast(int val) 
{
	if (val > CONTRAST_MAX) val = CONTRAST_MIN;
	else if (val < CONTRAST_MIN) val = CONTRAST_MAX;
	write_instruction(CONTRAST_SET | (val & B00001111));
	write_instruction((val >> 4) | POWER_ICON_BOST_CONTR | POWER_ICON_BOST_CONTR_Bon);
	contrast = val;
}

void DISPLAY_ST7032::adjust_contrast(int val) 
{
	set_contrast(val + contrast);
}

uint8_t DISPLAY_ST7032::get_contrast() 
{
	return contrast;
}
