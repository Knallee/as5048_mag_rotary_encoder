/*
 * spi.h
 *
 * Created: 2020-02-28 21:33:38
 *  Author: 2AM PULLUPS
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "atmega1284.h"
#include <avr/io.h>

#define TRUE	1
#define FALSE	0
#define HIGH	1
#define LOW		0

#define SPI_DDR			DDRB
#define SPI_PORT		PORTB		/**< AVR SPI port*/
#define SPI_CS			PORTB4		/**< AVR chip select pin*/
#define SPI_MOSI		PORTB5		/**< AVR MOSI pin*/
#define SPI_MISO		PORTB6		/**< AVR MISO pin*/
#define SPI_SCK			PORTB7		/**< AVR SCK pin*/

#define SPI_MSB_FIRST			0		/**< MSB is sent first otherwise LSB*/
#define SPI_LSB_FIRST			1		/**< LSB is sent first otherwise LSB*/

#define SPI_FCPU_DIV_4			0		/**< F_CPU is divided by 4*/
#define SPI_FCPU_DIV_16			1		/**< F_CPU is divided by 16*/
#define SPI_FCPU_DIV_64			2		/**< F_CPU is divided by 64*/
#define SPI_FCPU_DIV_128		3		/**< F_CPU is divided by 128*/


/**
 * The bitfield representing SPI control, status and data registers.
 */
typedef struct {
	// SPCR0 : SPI Control Register
	uint8_t clock_rate				:	2;		/**< Clock rate selection. */
	uint8_t clock_phase				:	1;		/**< Sampling trailing edge when set (1), and leading edge when cleared (0). */
	uint8_t clock_polarity			:	1;		/**< When set (1) the SCK is logic HIGH when idle. */
	uint8_t spi_master				:	1;		/**< Set (1) for AVR to be a master, clear (0) to be a slave. */
	uint8_t data_order				:	1;		/**< If set (1) the LSB is sent first otherwise MSB. */
	uint8_t enable					:	1;		/**< Set (1) to enable SPI. */
	uint8_t interrupt_enable		:	1;		/**< Enables the SPI interrupt. */
	// SPSR0 : SPI Status Register
	uint8_t double_speed			:	1;		/**< When set (1) the SCK frequency is doubled. */	
	uint8_t reserved				:	5;		/**< Not used. */
	uint8_t write_collision_flag	:	1;		/**< (Read only) */
	uint8_t interrupt_flag			:	1;		/**< (Read only) Is set when the serial transfer is complete. */
	// SPDR0 : SPI Data Register
	uint8_t data					:	8;
} spi_reg_t;


/**
* Initialize the Serial Peripheral Interface.
*/
void spi_init(void);


/**
* Sends and receives a byte with SPI. 
*
* Note: It is only invoked by other spi_txrx methods.
*
* @param data		This is the byte that will be sent.
* @return 			Returns the received byte.
*/
uint8_t spi_txrx(uint8_t);


/**
* Sending and receiving a byte by SPI.
*
* @param data		This is the byte that will be sent.
* @return 			Returns the received data.
*/
uint8_t spi_txrx_byte(uint8_t data);


/**
* Sending and receiving 16 bits as one package.
*
* @param data		This is the 16 bits that will be sent.
* @return 			Returns the received 16 bits.
*/
uint16_t spi_txrx_16bit(uint16_t data);


/**
* Set CS pin to high.
*/
void spi_set_cs(void);


/**
* Set CS pin to low.
*/
void spi_clear_cs(void);

#endif /* SPI_H_ */