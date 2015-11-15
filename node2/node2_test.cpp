/*
 * node2_test.cpp
 *
 * Created: 14.10.2015 16:10:32
 *  Author: sindrhan
 */ 
#include "node2_test.h"


void CAN_test()
{
	
	can_message_t testmelding  = (can_message_t){
	.id = 0xff,
	.length = 4,
	.data = {1, 2, 3, 6,},
	};
	
	can_init(MODE_LOOPBACK);
	can_transmit(testmelding);
	can_message_t mottatt_melding = can_receive();
	
	Serial.print("\nid: ");
	Serial.print(mottatt_melding.id);
	Serial.print("\nlen: ");
	Serial.print(mottatt_melding.length);
	Serial.print("\nMelding: [ ");
	Serial.print(mottatt_melding.data[0]);
	Serial.print(" ");
	Serial.print(mottatt_melding.data[1]);
	Serial.print(" ");
	Serial.print(mottatt_melding.data[2]);
	Serial.print(" ");
	Serial.print(mottatt_melding.data[3]);
	Serial.print(" ]\n");
}


void MCP_test()
{
	SPI_init();
	for (char i = 'a'; i<='f'; i++){
		Serial.print("Memory 0x36: ");
		Serial.print(MCP2515_read(0x36));
		Serial.print("\n");
		Serial.print("Writing '");
		Serial.print(i);
		Serial.print("' to 0x36\n");
		MCP2515_write(i,0x36);
		Serial.print("Memory 0x36: ");
		Serial.print(MCP2515_read(0x36));
		Serial.print("\n\n");
	}
}


	//can_message_t mottatt = can_receive();
	//printf("ID: %d\nLength: %d\nX: %d\nY: %d\n\n", mottatt.id,
	//mottatt.length, mottatt.data[0], mottatt.data[1]);
	//_delay_ms(500);
	//