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

#define DUMMY_BYTE	0x00


/**
* Initialize the Serial Peripheral Interface.
*
* @param data  This is the byte that will be sent.
* @return int16 Returns the Master In Slave Out data.
*/
void spi_init();

/**
* Sending and receiving a byte by SPI.
*
* @param data  This is the byte that will be sent.
* @return int16 Returns the Master In Slave Out data.
*/
uint8_t spi_txrx(uint8_t);

/**
* Adding two integers in a non-conventional, but equally correct, way.
*
* @param num_a  This is the first parameter to the function add_num
* @param num_b  This is the second parameter to the function add_num
* @return int16 This returns sum of num_a and num_b.
*/
uint8_t spi_read_8(uint8_t);

/**
* Adding two integers in a non-conventional, but equally correct, way.
*
* @param num_a  This is the first parameter to the function add_num
* @param num_b  This is the second parameter to the function add_num
* @return int16 This returns sum of num_a and num_b.
*/
uint8_t spi_write_8(uint8_t);

/**
* Adding two integers in a non-conventional, but equally correct, way.
*
* @param num_a  This is the first parameter to the function add_num
* @param num_b  This is the second parameter to the function add_num
* @return int16 This returns sum of num_a and num_b.
*/
uint16_t spi_read_16(uint16_t);

/**
* Adding two integers in a non-conventional, but equally correct, way.
*
* @param num_a  This is the first parameter to the function add_num
* @param num_b  This is the second parameter to the function add_num
* @return int16 This returns sum of num_a and num_b.
*/
uint16_t spi_write_16(uint16_t, uint16_t);


#endif /* SPI_H_ */