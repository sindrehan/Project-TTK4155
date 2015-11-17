
#include "mcp2515_driver.h"
#include "MCP2515.h"

uint8_t MCP2515_read(uint8_t address)
{
	SPI_enable();
	SPI_transmit(MCP_READ);
	SPI_transmit(address);
	uint8_t data = SPI_receive();
	SPI_disable();
	return data;
}

void MCP2515_write(uint8_t data, uint8_t address)
{
	SPI_enable();
	SPI_transmit(MCP_WRITE);
	SPI_transmit(address);
	SPI_transmit(data);
	SPI_disable();
}

void MCP2515_rts(uint8_t rts_port)
{
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

uint8_t MCP2515_read_status(void)
{
	SPI_enable();
	SPI_transmit(MCP_READ_STATUS);
	uint8_t data = SPI_receive();
	SPI_disable();
	return data;
}

void MCP2515_bit_modify(uint8_t address, uint8_t mask, uint8_t data)
{
	SPI_enable();
	SPI_transmit(MCP_BITMOD);
	SPI_transmit(address);
	SPI_transmit(mask);
	SPI_transmit(data);
	SPI_disable();
}

void MCP2515_reset(void)
{
	SPI_enable();
	SPI_transmit(MCP_RESET);
	SPI_disable();
}







