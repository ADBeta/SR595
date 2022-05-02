#include "SR595.h"

#define RCLK 9
#define SCLK 8
#define SER 10

SR595 SR(SCLK, RCLK, SER);

uint8_t array[3] = {0xff, 0x03, 0x00};

void setup() {
	//8 bit
	SR.writeByte(0x55);
	delay(1000);
	
	//16 bit
	SR.writeInt(0xaaaa);
	delay(1000);	
	
	//32 bit
	SR.writeLong(0x000002ff);
	delay(1000);
	
	//Array
	SR.writeArray(3, array);
	delay(1000);
	
	array[0] = 1;
	
}

void loop() {
	
	array[0] = array[0] * 2;
	if(array[0] == 0) array[0] = 1;
	
	SR.writeArray(3, array);

	delay(250);
}
