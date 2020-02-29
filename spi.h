/*
 * spi.h
 *
 * Created: 2020-02-28 21:33:38
 *  Author: Christoffer
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>

#define READ_CMD	1		/**< Read command, slave specific*/
#define WRITE_CMD	0		/**< Write command, slave specific*/

#define SPI_PORT			/**< AVR SPI port*/
#define SPI_CS_PIN			/**< AVR chip select pin*/
#define SPI_MOSI_PIN        /**< AVR MOSI pin*/
#define SPI_SCK_PIN			/**< AVR MOSI pin*/

#define SPI_ENABLE
#define SPI_MASTER
#define SPI_D

#define DUMMY_BYTE	0x00


/**
* Initialize the Serial Peripheral Interface.
*
* @param data  This is the byte that will be sent.
* @return int16 Returns the Master In Slave Out data.
*/
void spi_init(void);




/**
* Set CS pin to high.
*/
void spi_set_cs(void);




/**
* Set CS pin to low.
*/
void spi_clear_cs(void);




/**
* Sending and receiving a byte by SPI.
*
* @param data		This is the byte that will be sent.
* @return 			Returns the Master In Slave Out data.
*/
uint8_t spi_txrx(uint8_t data);




/**
* This function performs a 8-bit read of the specified register address.
*
* @param address	This is the address of the register to be read.
* @return 			The value of the specified register.
*/
uint8_t spi_read_8(uint8_t address);




/**
* This function writes data to specified register.
*
* @param address	This is the address of the register to be written.
* @param data		This is the data that will be written.
*/
void spi_write_8(uint8_t address, uint8_t data);




/**
*  This function performs a 16-bit read of the specified register address.
*
* @param address	This is the 16-bit address of the register to be written.
* @return int16		Returns the value of the specified register.
*/
uint16_t spi_read_16(uint16_t address);




/**
*  This function writes a 16-bit value to a specified register address.
*
* @param address	This is the 16-bit address of the register to be written.
* @param data		This is the second parameter to the function add_num
* @return			The value of the specified register.
*/
void spi_write_16(uint16_t address, uint16_t data);


#endif /* SPI_H_ */