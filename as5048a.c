/*
 * as5048a.c
 *
 * Created: 2020-02-28 21:34:23
 *  Author: 2AM Pullups
 */ 

#include "as5048a.h"

uint16_t as5048_read_angle() {
	uint16_t data = (READ << RW_BIT_POSITION) | REG_ANGLE;								/**< Read bit + Register. */
	return send_and_receive((calc_parity(data) << PARITY_BIT_POSITION) | data);			/**< Send Parity bit + Register and return output */
}

uint16_t as5048_read_magnitude() {
	uint16_t data = (READ << RW_BIT_POSITION) | REG_MAGNITUDE;						/**< Read bit + Register. */
	return send_and_receive((calc_parity(data) << PARITY_BIT_POSITION) | data);		/**< Send Parity bit + Register and return output. */
}

uint16_t as5048_read_agc()
{
	uint16_t data = (READ << RW_BIT_POSITION) | REG_AGC;							/**< Read bit + Register. */
	return send_and_receive((calc_parity(data) << PARITY_BIT_POSITION) | data);		/**< Send Parity bit + Register and return output.  */
}

uint16_t as5048_clear_error()
{
	uint16_t data = (READ << RW_BIT_POSITION) | REG_CLR_ERR;									/**< Read bit + Register. */
	return send_and_receive((calc_parity(data) << PARITY_BIT_POSITION) | data);					/**< Send Parity bit + Register and return output. */	
}

uint16_t com_error_check(uint16_t data)
{
	uint16_t err = 0;																		/**< Error data that would be used for output if there are communication errors. */
	if ( ((data >> ERROR_FLAG) & 0x01) == 0) {												/**< Check if there is communication error between master and as5048. */
		if ( calc_parity(data << 1) == ((uint8_t) (data >> PARITY_BIT_POSITION)) ) {		/**< Check if data received from as5048 has correct parity. */
			return data & 0x3FFF;															/**< Communication is error-free, return 14 bit data. */
		} else {
			err = (1 << 3);																	/**< Parity error flag for further investigation. */
			// TODO: LOG parity error
		}
	}
	err |= as5048_clear_error();												/**< Clears error flag and receives errors from as5048a. */
	// TODO: LOG
	return (1 << ERROR_FLAG)|(err);												/**< Return error data with an error flag (bit 14) for further checking. */
}

uint8_t calc_parity(uint16_t data)
{
	uint8_t count = 0;
	
	for (uint8_t i = 0; i < 16; i++) {
		if (data & 0x1)
			count++;
		data >>= 1;
	}
	return count & 0x1;
}

uint16_t angle_decode(uint16_t data) {
	return (data * (360/ BIT14_VALUE) );
}

uint16_t send_and_receive(uint16_t transmit_data) {
	uint16_t received_data;
	received_data = spi_txrx_16bit(transmit_data);				/* Request data */
	received_data = spi_txrx_16bit(REG_NOP);					/* Receives requested data from the last transmission */
	return received_data;
}
