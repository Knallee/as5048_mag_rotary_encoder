/*
 * as5048a.c
 *
 * Created: 2020-02-28 21:34:23
 *  Author: 2AM Pullups
 */ 

#include "as5048a.h"

uint16_t as5048_read_angle() {
	uint16_t data = (READ << RW_BIT_POSITION) | REG_ANGLE;							/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT_POSITION) | REG_ANGLE);		/**< Send Parity bit + Register and return output */
}

uint16_t as5048_read_magnitude() {
	uint16_t data = (READ << RW_BIT_POSITION) | REG_MAGNITUDE;						/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT_POSITION) | REG_MAGNITUDE);	/**< Send Parity bit + Register and return output. */
}

uint16_t as5048_read_agc() {
	uint16_t data = (READ << RW_BIT_POSITION) | REG_AGC;							/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT_POSITION) | REG_AGC);		/**< Send Parity bit + Register and return output.  */
}

uint8_t as5048_clear_error() {
		uint16_t data = (READ << RW_BIT_POSITION) | REG_CLR_ERR;									/**< Read bit + Register. */
		return (uint8_t) spi_read_16((calc_parity(data) << PARITY_BIT_POSITION) | REG_CLR_ERR);		/**< Send Parity bit + Register and return output. */	
}

// Untested!
uint16_t com_error_check(uint16_t data) {
	uint8_t err = 0;
	if ( ((data >> ERROR_FLAG) & 0x01) == 0) {												/**< Check if Error Flag is 0. */
		if ( calc_parity(data << 1) == ((uint8_t) (data >> PARITY_BIT_POSITION)) ) {		/**< Check if Parity bit is equal to data's parity value. */
			return data & 0x3FFF;															/**< Return data with first 2 bits cleared. */
		} else {
			err = (1 << 3);																	/**< Parity error for further checking. */
			// TODO: LOG parity error
		}
	}
	err |= as5048_clear_error();												/**< Clears error flag and receives errors from as5048a. */
	// TODO: LOG
	return (1 << ERROR_FLAG)|(err);												/**< Return error data with an error flag for further checking. */
}

uint8_t calc_parity(uint16_t data) {
	uint8_t count = 0;
	
	for (uint8_t i = 0; i < 16; i++) {
		if (data & 0x1)
			count++;
		data >>= 1;
	}
	return count & 0x1;
}