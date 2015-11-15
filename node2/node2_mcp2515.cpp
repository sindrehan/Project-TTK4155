// 
// 
// 

#include "node2_mcp2515.h"

uint8_t MCP2515_read(uint8_t address)
{
	SPI_enable();
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	uint8_t data = SPI_receive();
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
	char status = SPI_receive();
	SPI_disable();
	return status;
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
	//Allow mcp2515 time to complete command
	_delay_us(1);
}

