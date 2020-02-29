/*
 * as5048a.c
 *
 * Created: 2020-02-28 21:34:23
 *  Author: 2AM Pullups
 */ 

uint16_t as5048_read_angle() {
	uint16_t data = (READ << WRITE_READ_BIT) | REG_ANGLE;					/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT) | REG_ANGLE);		/**< Return Parity bit + Register. */
}

uint16_t as5048_read_magnitude() {
	uint16_t data = (READ << WRITE_READ_BIT) | REG_MAGNITUDE;				/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT) | REG_MAGNITUDE);	/**< Return Parity bit + Register. */
}

uint16_t as5048_read_agc() {
	uint16_t data = (READ << WRITE_READ_BIT) | REG_AGC;						/**< Read bit + Register. */
	return spi_read_16((calc_parity(data) << PARITY_BIT) | REG_AGC);		/**< Return Parity bit + Register. */
}


/**
* Calculates Parity Bit.
*
* @param	16 bit input for parity calculation.
* @return	Returns 0x00 for EVEN or 0x01 for ODD.
*/
uint8_t calc_parity(uint16_t data) {
	uint8_t count = 0;
	
	for (uint8_t i = 0; i < 16; i++) {
		if (data & 0x1)
			count++;
		data >>= 1;
	}
	return count & 0x1;
}


