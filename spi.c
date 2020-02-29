/*
 * spi.c
 *
 * Created: 2020-02-28 21:33:23
 *  Author: Christoffer
 */ 

#include "spi.h"

void spi_init(uint8_t slave_master, uint8_t data_order, uint8_t spi_clk) 
{
	SPI_PORT	|= (1 << SPI_MOSI_PIN) | (1 << SPI_SCK_PIN) | (1 << SPI_CS_PIN);
	SPCR		|= (1 << SPE) | (1 << MSTR);
}

void spi_init_enable()
{
	
}

uint8_t spi_txrx(uint8_t data)
{
	/* SPI transmit and receive */
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

void spi_set_cs()
{
	SPI_PORT |= (1 << SPI_CS_PIN);
}

void spi_clear_cs()
{
	SPI_PORT &= ~(1 << SPI_CS_PIN);
}


uint8_t spi_read_8(uint8_t address)
{	
	spi_clear_cs();
	spi_txrx(address | (READ_CMD << 8));
	spi_set_cs();

	// might need some delay between setting and clearing the cs pin
	spi_clear_cs();
	uint8_t data = spi_txrx(DUMMY_BYTE);
	spi_set_cs();
	
	return data;
}

void spi_write_8(uint8_t address, uint8_t data)
{
	spi_clear_cs();
	spi_txrx(address | (WRITE_CMD << 8));
	spi_set_cs();
	
	// might need some delay between setting and clearing the cs pin
	spi_clear_cs();
	spi_txrx(data);
	spi_set_cs();
	
}

uint16_t spi_read_16(uint16_t address)
{
	uint8_t ms_byte, ls_byte;

	spi_clear_cs();
	spi_txrx((address >> 8) | (READ_CMD << 8));
	spi_txrx((uint8_t) address);
	spi_set_cs();
	
	// might need some delay between setting and clearing the cs pin
	spi_clear_cs();
	ms_byte = spi_txrx(DUMMY_BYTE);
	ls_byte = spi_txrx(DUMMY_BYTE);
	spi_set_cs();
	
	return (ms_byte << 8) | ls_byte;
}

void spi_write_16(uint16_t address, uint16_t data)
{
	uint8_t ms_byte, ls_byte;
	spi_clear_cs();
	spi_txrx((address >> 8) | (WRITE_CMD << 8));
	spi_txrx((uint8_t) address);
	spi_set_cs();
	
	// might need some delay between setting and clearing the cs pin
	spi_clear_cs();
	spi_txrx(data >> 8);
	spi_txrx((uint8_t) data);
	spi_set_cs();
}
