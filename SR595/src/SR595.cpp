#include "Arduino.h"
#include "SR595.h"

SR595::SR595(uint8_t sclk, uint8_t rclk, uint8_t ser) {
	//Copy passed values into class vars 
	hw_SCLK = sclk;
	hw_RCLK = rclk;
	hw_SER = ser;
	
	//Convert arduino pin number to asm
	hw_SCLKasm = digitalPinToBitMask(hw_SCLK);
	hw_RCLKasm = digitalPinToBitMask(hw_RCLK);
	hw_SERasm = digitalPinToBitMask(hw_SER);
	
	//Allocate ports for each pin
	hw_SCLKport = portOutputRegister(digitalPinToPort(hw_SCLK));
	hw_RCLKport = portOutputRegister(digitalPinToPort(hw_RCLK));
	hw_SERport = portOutputRegister(digitalPinToPort(hw_SER));
	
	pinMode(hw_RCLK, OUTPUT);
	pinMode(hw_SCLK, OUTPUT);
	pinMode(hw_SER, OUTPUT);
	
	digitalWrite(hw_RCLK, LOW);
	digitalWrite(hw_SCLK, LOW);
	digitalWrite(hw_SER, LOW);
}

void SR595::writeByte(uint8_t data) {
	//Write single byte to the Shift Register using asm port maniuplation 
	
	//bit in byte to shift
	for(int8_t bitMask = 7; bitMask >= 0; bitMask--) {
		//current bit to be sent
		bool curBit = (data >> bitMask) & 0x01;
		
		//Output that bit to the SER Pin
		if(curBit) {
			*hw_SERport |= hw_SERasm;
		}
		
		if(!curBit) {
			*hw_SERport &= ~hw_SERasm;
		}
		
		//Serial clock toggle
		*hw_SCLKport |= hw_SCLKasm;
		*hw_SCLKport &= ~hw_SCLKasm;
	}
	
	//Latch clock toggle
	*hw_RCLKport |= hw_RCLKasm;
	*hw_RCLKport &= ~hw_RCLKasm;
}

void SR595::writeInt(uint16_t data) {
	//Write 2 byte 16 bit value to shift register
	
	//bit in byte to shift
	for(int8_t bitMask = 15; bitMask >= 0; bitMask--) {
		//current bit to be sent
		bool curBit = (data >> bitMask) & 0x01;
		
		//Output that bit to the SER Pin
		if(curBit) {
			*hw_SERport |= hw_SERasm;
		}
		
		if(!curBit) {
			*hw_SERport &= ~hw_SERasm;
		}
		
		//Serial clock toggle
		*hw_SCLKport |= hw_SCLKasm;
		*hw_SCLKport &= ~hw_SCLKasm;
	}
	
	//Latch clock toggle
	*hw_RCLKport |= hw_RCLKasm;
	*hw_RCLKport &= ~hw_RCLKasm;
}

void SR595::writeLong(uint32_t data) {
	//Write 4 byte 32 bit value to shift register
	
	//bit in byte to shift
	for(int8_t bitMask = 31; bitMask >= 0; bitMask--) {
		//current bit to be sent
		bool curBit = (data >> bitMask) & 0x01;
		
		//Output that bit to the SER Pin
		if(curBit) {
			*hw_SERport |= hw_SERasm;
		}
		
		if(!curBit) {
			*hw_SERport &= ~hw_SERasm;
		}
		
		//Serial clock toggle
		*hw_SCLKport |= hw_SCLKasm;
		*hw_SCLKport &= ~hw_SCLKasm;
	}
	
	//Latch clock toggle
	*hw_RCLKport |= hw_RCLKasm;
	*hw_RCLKport &= ~hw_RCLKasm;
}

void SR595::writeArray(int16_t size, uint8_t *array) {
	//Write array of bytes to the shift register using asm manipulation
	
	//Decriment size to make it faster to execute and 'MSBFirst'
	int16_t arrIndex = size - 1;
	
	//Byte in array
	for(arrIndex; arrIndex >= 0; arrIndex--) {
		//bit in byte to shift
		for(int8_t bitMask = 7; bitMask >= 0; bitMask--) {
			//current bit to be sent
			bool curBit = (array[arrIndex] >> bitMask) & 0x01;
			
			//Output that bit to the SER Pin
			if(curBit) {
				*hw_SERport |= hw_SERasm;
			}
			
			if(!curBit) {
				*hw_SERport &= ~hw_SERasm;
			}
			
			//Serial clock toggle
			*hw_SCLKport |= hw_SCLKasm;
			*hw_SCLKport &= ~hw_SCLKasm;
		}
	}
	
	//Latch clock toggle
	*hw_RCLKport |= hw_RCLKasm;
	*hw_RCLKport &= ~hw_RCLKasm;
}
