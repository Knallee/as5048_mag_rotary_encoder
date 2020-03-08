/*
 * spi.c
 *
 * Created: 2020-02-28 21:33:23
 *  Author: Christoffer
 */ 

#include "spi.h"

void spi_init(spi_init_t *spi_settings) 
{
	SPCR	|= (1 << SPE);
	SPI_DDR	|= (1 << SPI_MOSI_PIN) | (1 << SPI_SCK_PIN) | (1 << SPI_CS_PIN);
	
	if(spi_settings->spi_master == TRUE) {
		SPCR |= (1 << MSTR);
	} else if (spi_settings->spi_master == FALSE) {
		SPCR &= ~(1 << MSTR);
	}
	
	if ((spi_settings->clock_polarity == 0) || (spi_settings->clock_polarity == 1)) {
		if(spi_settings->clock_polarity == 1) {
			SPCR |= (1 << CPOL);
		} else {
			SPCR &= ~(1 << CPOL);
		}
	}
	
	if ((spi_settings->clock_phase == 0) || (spi_settings->clock_phase == 1)) {
		if(spi_settings->clock_phase == 1) {
			SPCR |= (1 << CPHA);
			} else {
			SPCR &= ~(1 << CPHA);
		}
	}
	
	if ((0 <= spi_settings->clock_rate) && (spi_settings->clock_rate <= 3)) {
		SPCR |= spi_settings->clock_rate;
	}
	
	if(spi_settings->double_speed == TRUE) {
		SPSR |= (1 << SPI2X);
		} else if (spi_settings->double_speed == FALSE) {
		SPSR &= ~(1 << SPI2X);
	}

}



uint8_t spi_txrx_byte(uint8_t data)
{
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));
	return SPDR;
}

uint16_t spi_txrx_16bit(uint16_t data)
{
	uint8_t hi_byte, low_byte;
	hi_byte = spi_txrx_byte(data >> 8);
	low_byte = spi_txrx_byte((uint8_t) data);
	
	return ((hi_byte << 8) | (low_byte));
}

void spi_set_cs()
{
	SPI_PORT |= (1 << SPI_CS_PIN);
}

void spi_clear_cs()
{
	SPI_PORT &= ~(1 << SPI_CS_PIN);
}


