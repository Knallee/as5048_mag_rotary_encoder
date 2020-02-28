/*
 * spi.c
 *
 * Created: 2020-02-28 21:33:23
 *  Author: Christoffer
 */ 

#include "spi.h"

void spi_init() 
{
	
	
	
}

uint8_t spi_txrx(uint8_t data)
{
	/* SPI transmit and receive */
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}


uint8_t spi_read_8(uint8_t address)
{
	spi_txrx(address | (READ_CMD << 8));
	return spi_txrx(DUMMY_BYTE);
}

uint8_t spi_write_8(uint8_t address)
{
	spi_txrx(address | (WRITE_CMD << 8));
	return spi_txrx(DUMMY_BYTE);
}

uint16_t spi_read_16(uint16_t address)
{
	uint8_t ms_byte, ls_byte;
	spi_txrx((address >> 8) | (READ_CMD << 8));
	spi_txrx((uint8_t) address);
	ms_byte = spi_txrx(DUMMY_BYTE);
	ls_byte = spi_txrx(DUMMY_BYTE);
	return (ms_byte << 8) | ls_byte;
}

uint16_t spi_write_16(uint16_t address, uint16_t data)
{
	uint8_t ms_byte, ls_byte;
	spi_txrx((address >> 8) | (WRITE_CMD << 8));
	spi_txrx((uint8_t) address);
	ms_byte = spi_txrx(data >> 8);
	ls_byte = spi_txrx((uint8_t) data);
	return (ms_byte << 8) | ls_byte;
}
