/*
 * General purpose 74HC595 shift register driver library using ASM port 
 * maniuplation instead of digitalWrite for more speed.
 *
 * Still in testing and improvement phase
 *
 * ADBeta 28 Apr 2022
 * V0.2
*/

#include "Arduino.h"

#ifndef SR595_h
#define SR595_h

class SR595 {
	public:
	
	//Declare hardware pins. sclk rclk ser
	SR595(uint8_t, uint8_t, uint8_t);
	
	//Write a single byte to the shift register
	void writeByte(uint8_t);
	
	//Write a 2 byte int to the shift register
	void writeInt(uint16_t);
	
	//Write a 4 byte long to the shift register
	void writeLong(uint32_t);
	
	//Write an array to the shift register. size, pointer to array
	void writeArray(int16_t, uint8_t*);
	
	private:
	uint8_t hw_SCLK, hw_RCLK, hw_SER; //Arduino pin
	uint8_t hw_SCLKasm, hw_RCLKasm, hw_SERasm; //Assembly pin
	volatile uint8_t *hw_SCLKport, *hw_RCLKport, *hw_SERport; //Assembly port
	

}; //class SR595


#endif
