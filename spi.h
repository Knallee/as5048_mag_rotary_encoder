/*
 * spi.h
 *
 * Created: 2020-02-28 21:33:38
 *  Author: Christoffer
 */ 


#ifndef SPI_H_
#define SPI_H_

#include "fcpu.h"

#include <avr/io.h>
#include <util/delay.h>

#define TRUE	1
#define FALSE	0

#define READ_CMD	1		/**< Read command, slave specific*/
#define WRITE_CMD	0		/**< Write command, slave specific*/

#define SPI_DDR				DDRB
#define SPI_PORT			PORTB		/**< AVR SPI port*/
#define SPI_CS_PIN			PORTB4		/**< AVR chip select pin*/
#define SPI_MOSI_PIN		PORTB5		/**< AVR MOSI pin*/
#define SPI_SCK_PIN			PORTB7		/**< AVR MOSI pin*/

#define SPI_MASTER				TRUE	/**< If true the AVR becomes the master*/
#define SPI_DORD_MSB			TRUE	/**< If true the MSB is sent first otherwise LSB*/	
#define SPI_CLOCK_POLARITY		0		/**< When 0 SCK is high in idle, when 1 low*/
#define SPI_CLOCK_PHASE			0		/**< Determines which flank the data is sampled on*/
#define SPI_DOUBLE_RATE			FALSE	/**< When set to true the spi data rate is doubled*/

#define SPI_FCPU_DIV_4			0		/**< F_CPU is divided by 4*/
#define SPI_FCPU_DIV_16			1		/**< F_CPU is divided by 16*/
#define SPI_FCPU_DIV_64			2		/**< F_CPU is divided by 64*/
#define SPI_FCPU_DIV_128		3		/**< F_CPU is divided by 128*/

#define SPI_CS_DELAY			1		/**< The delay, in us, between consequent read or writes */ 
											  


#define DUMMY_BYTE	0x00


typedef struct spi_init {
	uint8_t data_order;					/**< Set to TRUE (1) for MSB first*/
	uint8_t spi_master;					/**< Set to TRUE (1) to be master*/
	uint8_t clock_polarity;				/**< AVR SPI port*/
	uint8_t clock_phase;				/**< AVR SPI port*/
	uint8_t clock_rate;					/**< AVR SPI port*/
	uint8_t double_speed;				/**< AVR SPI port*/
} spi_init_t;

// Init example
// spi_init_t spi_settings = {.data_order = SPI_DORD_MSB, .spi_master = TRUE, .clock_polarity = 0, .clock_phase = 0, .clock_rate = SPI_FCPU_DIV_4, .double_speed = FALSE};


/**
* Initialize the Serial Peripheral Interface.
*
* @param spi_settings	A struct containing the spi configuration data.
*/
void spi_init(spi_init_t *spi_settings);




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