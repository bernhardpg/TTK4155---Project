#include "../utils/bit_macros.h"
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "MCP2515.h"
#include <stdio.h>
#include <util/delay.h>

/* Bits in TXBnCTRL */
#define TXREQ 3

/* TX buffer address offsets from TXBnCTRL / RXBnCTRL */
#define SIDH_OFFSET 1
#define SIDL_OFFSET 2
#define DLC_OFFSET 5
#define DLC_MASK 15
#define D_OFFSET 6

/* Bits in RXB0CTRL */
#define BUKT 2
#define RXM0 5

/* Bits in CANINTE*/
#define RX0IE 0

/* Bits in CANINTF */
#define RX0IF 0
#define RX1IF 1

/* Bits in TXBnSIDL / RXBnSIDL*/
#define SID0 5


void CAN_init(void)
{
	//TODO will later be expanded to work with multiple modes
	MCP_init();
	MCP_write(MCP_RXB0CTRL, (3 << RXM0));
	MCP_write(MCP_RXB0CTRL, (1 << BUKT));

	// Enable interrupt for received message
	MCP_bit_modify(MCP_CANINTE, (1 << RX0IE), 1);

	MCP_bit_modify(MCP_CANINTF, (1 << RX0IF), 0);
}

void CAN_send(CAN_message * message)
{
	/* Check if buffer is ready */
	while(READ_BIT(MCP_read(MCP_TXB0CTRL), TXREQ));

	/* TODO: Assign priority? */

	MCP_write(MCP_TXB0CTRL + SIDH_OFFSET, 0);
	MCP_write(MCP_TXB0CTRL + SIDL_OFFSET, message->id << SID0);
	MCP_write(MCP_TXB0CTRL + DLC_OFFSET, message->length);
	MCP_write_n(MCP_TXB0CTRL + D_OFFSET, message->data, message->length);
	MCP_request_to_send();
}

void CAN_receive(CAN_message * message)
{
	// Wait for RX0 interrupt flag
	while(!READ_BIT(MCP_read(MCP_CANINTF), RX0IF));

	// Clear flag bit
	MCP_bit_modify(MCP_CANINTF, (1 << RX0IF), 0);


	message->id = (MCP_read(MCP_RXB0CTRL + SIDL_OFFSET)) >> SID0;
	message->length = (MCP_read(MCP_RXB0CTRL + DLC_OFFSET)) & DLC_MASK;
	MCP_read_n(MCP_RXB0CTRL + D_OFFSET, message->data, message->length);
}