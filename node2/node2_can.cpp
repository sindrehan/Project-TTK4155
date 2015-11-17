// 
// 
// 

#include "node2_can.h"

uint8_t rxbuffer = 0;

void can_init(uint8_t mode)
{
	SPI_init();
	MCP2515_reset();
	MCP2515_bit_modify(MCP_CANCTRL, 0xE0, mode);
	MCP2515_bit_modify(MCP_RXB0CTRL, 0x60, MCP_FILTER_OFF);
	MCP2515_bit_modify(MCP_RXB0CTRL, 0x04, MCP_ROLLOVER_OFF);
	MCP2515_bit_modify(MCP_CANINTE, 0xFF, MCP_NO_INT);
}

void can_transmit(can_message_t msg){
	
	while (MCP2515_read(MCP_TXB0CTRL) & (MCP_TXREQ)){}
	
	MCP2515_write((msg.id >> 3), MCP_TXB0SIDH);
	MCP2515_write((msg.id << 5), MCP_TXB0SIDL);
	MCP2515_write(msg.length, MCP_TXB0DLC);
	for (uint8_t i = 0; i < msg.length; i++){
		MCP2515_write(msg.data[i], MCP_TXB0D0+i);
	}
	MCP2515_rts(0);
	
}

can_message_t can_receive(void)
{
	can_message_t msg  = {0};
	
	if (MCP2515_read(MCP_CANINTF) & (MCP_RX0IF)){
		uint8_t low = MCP2515_read(MCP_RXB0SIDL);
		low /= 0b100000;
		uint8_t high = MCP2515_read(MCP_RXB0SIDH);
		high *= 0b1000;
		msg.id = high + low;
		msg.length = (MCP2515_read(MCP_RXB0DLC)) & (0x0f);
		for (uint8_t i = 0; i < msg.length; i++){
			msg.data[i] = MCP2515_read(MCP_RXB0D0 + i);
		}
		rxbuffer = 0;
		MCP2515_bit_modify(MCP_CANINTF, MCP_RX0IF, REMOVE_INT);
	}
	return msg;
}


void can_printmsg(can_message_t m){
	if (m.id != 0){
		printf("(can_msg_t){id:%x, len:%d, data:{",
			m.id, m.length
			);
			if(m.length){
				printf("%d", m.data[0]);
			}
			for(uint8_t i = 1; i < m.length; i++){
				printf(", %d", m.data[i]);
			}
		printf("}\n");	
	}

}