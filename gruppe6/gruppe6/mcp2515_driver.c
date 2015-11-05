
#include "mcp2515_driver.h"
#include "MCP2515.h"

char MCP2515_read(char address){
	SPI_enable();
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	char data = SPI_receive();
	SPI_disable();
	return data;
}

void MCP2515_write(char data, char address){
	SPI_enable();
	SPI_transmit(MCP_WRITE);
	SPI_transmit(address);
	SPI_transmit(data);
	SPI_disable();
}

void MCP2515_rts(char rts_port){
	SPI_enable();
	switch (rts_port){
		case 0:
			SPI_transmit(MCP_RTS_TX0);
			break;
		case 1:
			SPI_transmit(MCP_RTS_TX1);
			break;
		case 2:
			SPI_transmit(MCP_RTS_TX2);
			break;
	}
	SPI_disable();
}

char MCP2515_read_status(){
	SPI_enable();
	SPI_transmit(MCP_READ_STATUS);
	char data = SPI_receive();
	SPI_disable();
	return data;
}

void MCP2515_bit_modify(char address, char mask, char data){
	SPI_enable();
	SPI_transmit(MCP_BITMOD);
	SPI_transmit(address);
	SPI_transmit(mask);
	SPI_transmit(data);
	SPI_disable();
}

void MCP2515_reset(){
	SPI_enable();
	SPI_transmit(MCP_RESET);
	SPI_disable();
}







