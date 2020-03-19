/*
 * as5048a.h
 *
 * Created: 2020-02-28 21:33:53
 *  Author: 2AM Pullups
 */ 


#ifndef AS5048A_H_
#define AS5048A_H_

#include <stdlib.h>
#include <avr/io.h>

#include "spi.h"
#include "uart.h"

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
#define COMP_HIGH_BIT	11			/**< Indicates weak magnetic field. */
#define COMP_LOW_BIT	10			/**< Indicates high magnetic field. */
#define CORDIC_OF_BIT	9			/**< CORDIC Overflow. Indicates (HIGH) an out of range error in the CORDIC part */
#define OCF_BIT			8			/**< Offset Compensation Finished.  */


/* Communication send bits */
#define PARITY_BIT_POSITION		15		/**< Parity bit for SPI communication package. */
#define	RW_BIT_POSITION			14		/**< SPI read/write bit (ONLY for parity calculation). */


/* Communication received bits */
#define ERROR_FLAG		14			/**< Error flag that indicates a transmission error in a previous host transmission. */


/* Values of RW_BIT */
#define READ			1
#define WRITE			0


/* Constants */
#define	 BIT14_VALUE		16384			/**< 2^14 */

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
uint16_t as5048_clear_error();

/**
* Calculates Parity Bit.
*
* @param	16 bit input for parity calculation.
* @return	Returns 0x00 for EVEN or 0x01 for ODD.
*/
uint8_t calc_parity(uint16_t data);

/**
* Checks for communication errors between master and as5048.
*
* @param	Received data (16 bit).
* @return	Returns error data (bits 3-0) if there are errors during communication & an error flag (bit 14)
*					else returns requested data.
*			Error message:
*				[Bit]	[Description]
*				14		Error flag (communication error occurred)
*				3		Parity error	(as5048 -> Master)
*				2		Parity error	(Master -> as5048)
*				1		Command invalid (Master -> as5048)
*				0		Framing error	(Master -> as5048)
*/
uint16_t com_error_check(uint16_t data);


/** 
* Decodes angle value.
*
* @param	Received data (14 bit).
* @return	Returns angle value in a range [0, 360].
*/
uint16_t angle_decode(uint16_t data);

#endif /* AS5048A_H_ */