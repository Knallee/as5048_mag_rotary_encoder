/*
 * as5048a.h
 *
 * Created: 2020-02-28 21:33:53
 *  Author: 2AM Pullups
 */ 


#ifndef AS5048A_H_
#define AS5048A_H_

#include <avr/io.h>

#include "spi.h"

/* Control and Error Registers */
#define REG_NOP			0x0000		/**< Dummy register. */
#define REG_CLR_ERR		0x0001		/**< Clear error flag register. */
#define REG_PRG_CTRL	0x0003		/**< Programming control register (CHECK PROGRAMMING PROCEDURE BEFORE USING!). */
/* Programmable Customer Settings */
#define REG_OTP_HIGH	0x0016		/**< One Time Programmable Zero Position High byte register. */
#define REG_OTP_LOW		0x0017		/**< One Time Programmable Zero Position Low byte register. */
/* Readout Registers */
#define REG_AGC			0x3FFD		/**< Diagnostics (4 bit) + AGC (8 bit) register. */
#define REG_MAGNITUDE	0x3FFE		/**< Magnitude (14 bit) register. */
#define REG_ANGLE		0x3FFF		/**< Angle (14 bit) register. */
/* Diagnostics bits */
#define COMP_HIGH		11			/**< Indicates weak magnetic field. */
#define COMP_LOW		10			/**< Indicates high magnetic field. */
#define CORDIC_OF		9			/**< CORDIC Overflow. Indicates (HIGH) an out of range error in the CORDIC part */
#define OCF				8			/**< Offset Compensation Finished.  */
/* Communication bits */
#define PARITY_BIT		15			/**< Parity bit for SPI communication package. */
#define	WRITE_READ_BIT	14			/**< SPI read/write bit (ONLY for parity calculation). */
/* Read & Write for Parity calculation */
#define READ			1			/**< Read needed for Parity calculation. */
#define WRITE			0			/**< Write needed for Parity calculation. */

// One time programming function, used only once
// void as5048_otp();	

/**
* Receiving Angle.
*
* @return	Returns angle (lower 14 bits).
*/
uint16_t as5048_read_angle();

/**
* Receiving Magnitude.
*
* @return	Returns magnitude (lower 14 bits).
*/
uint16_t as5048_read_magnitude();

/**
* Receiving Diagnostics + Automatic Gain Control (AGC) from AS5048.
*
* @return	Returns Diagnostics (bis 11-8) AGC (lower 8 bits).
*/
uint16_t as5048_read_agc();

/**
* Clears error flag and receives errors.
*
* @return	Returns error bits.
*/
uint8_t as5048_clear_error();

#endif /* AS5048A_H_ */