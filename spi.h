/*
 * spi.h
 *
 * Created: 2020-02-28 21:33:38
 *  Author: 2AM PULLUPS
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "fcpu.h"
#include "atmega1284.h"

#include <avr/io.h>
#include <util/delay.h>

#define TRUE	1
#define FALSE	0

#define HIGH	1
#define LOW		0

#define SPI_DDR				DDRB
#define SPI_PORT			PORTB		/**< AVR SPI port*/
#define SPI_CS_PIN			PORTB4		/**< AVR chip select pin*/
#define SPI_MOSI_PIN		PORTB5		/**< AVR MOSI pin*/
#define SPI_SCK_PIN			PORTB7		/**< AVR MOSI pin*/

#define SPI_MASTER				TRUE	/**< If true the AVR becomes the master*/
#define SPI_MSB_FIRST			1		/**< MSB is sent first otherwise LSB*/
#define SPI_LSB_FIRST			1		/**< LSB is sent first otherwise LSB*/
#define SPI_CLOCK_POLARITY		0		/**< When 0 SCK is high in idle, when 1 low*/
#define SPI_CLOCK_PHASE			0		/**< Determines which flank the data is sampled on*/
#define SPI_DOUBLE_RATE			FALSE	/**< When set to true the spi data rate is doubled*/

#define SPI_FCPU_DIV_4			0		/**< F_CPU is divided by 4*/
#define SPI_FCPU_DIV_16			1		/**< F_CPU is divided by 16*/
#define SPI_FCPU_DIV_64			2		/**< F_CPU is divided by 64*/
#define SPI_FCPU_DIV_128		3		/**< F_CPU is divided by 128*/

#define SPI_CS_DELAY			1		/**< The delay, in us, between consequent read or writes */ 

#define DUMMY_BYTE	0x00

#define SPI (*(spi_reg_t *) SPCR0_OFFSET)


// OLD CRAP
typedef struct spi_init {			// before: spi_init
	uint8_t data_order;					/**< Set to TRUE (1) for MSB first*/
	uint8_t spi_master;					/**< Set to TRUE (1) to be master*/
	uint8_t clock_polarity;				/**< AVR SPI port*/
	uint8_t clock_phase;				/**< AVR SPI port*/
	uint8_t clock_rate;					/**< AVR SPI port*/
	uint8_t double_speed;				/**< AVR SPI port*/
} spi_init_t;

// NEW
/**
 * The bitfield representing SPI control, status and data registers.
 */
typedef struct spi_reg {
	// SPCR0 : SPI Control Register
	uint8_t clock_rate				:	2;		/**< Clock rate selection. */
	uint8_t clock_phase				:	1;		/**< Sampling trailing edge when set (1), and leading edge when cleared (0). */
	uint8_t clock_polarity			:	1;		/**< When set (1) the SCK is logic HIGH when idle. */
	uint8_t spi_master				:	1;		/**< Set (1) to be master, clear (0) to be slave. */
	uint8_t data_order				:	1;		/**< If set (1) the MSB is sent first otherwise LSB. */
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

// Init example
// spi_init_t spi_settings = {.data_order = SPI_DORD_MSB, .spi_master = TRUE, .clock_polarity = 0, .clock_phase = 0, .clock_rate = SPI_FCPU_DIV_4, .double_speed = FALSE};


/**
* Initialize the Serial Peripheral Interface.
*
* @param spi_settings	A struct containing the SPI configuration data.
*/
// OLD CRAP: void spi_init(spi_init_t *spi_settings);
void spi_init(void);


/**
* Sending and receiving a byte by SPI.
*
* @param data		This is the byte that will be sent.
* @return 			Returns the received data.
*/
uint8_t spi_txrx(uint8_t data);

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