/*
 * spi.c
 *
 * Created: 2020-02-28 21:33:23
 *  Author: 2AM PULLUPS
 */ 

#include "spi.h"

volatile spi_reg_t *spi = (volatile spi_reg_t *) SPCR0_OFFSET;


void spi_init()
{	
	spi_set_cs();
	SPI_DDR	|= (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_CS);
	SPI_DDR	&= ~(1 << SPI_MISO);
	spi->enable			= TRUE;
	spi->spi_master		= TRUE;
	spi->data_order		= SPI_MSB_FIRST;
	spi->clock_polarity	= LOW;
	spi->clock_phase	= 0;
	spi->clock_rate		= SPI_FCPU_DIV_16;
	spi->double_speed	= FALSE;
}

uint8_t spi_txrx(uint8_t data)
{
	spi->data = data;
	while (spi->interrupt_flag == 0);
	return spi->data;
}

uint8_t spi_txrx_byte(uint8_t data)
{
	spi_clear_cs();
	data = spi_txrx(data);
	spi_set_cs();
	return data;
}

uint16_t spi_txrx_16bit(uint16_t data)
{
	uint8_t hi_byte, low_byte;
	spi_clear_cs();
	hi_byte = spi_txrx(data >> 8);
	low_byte = spi_txrx((uint8_t) data);
	spi_set_cs();
	return ((hi_byte << 8) | (low_byte));
}


void spi_set_cs()
{
	SPI_PORT |= (1 << SPI_CS);
}

void spi_clear_cs()
{
	SPI_PORT &= ~(1 << SPI_CS);
}


