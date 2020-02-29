/*
 * spi.c
 *
 * Created: 2020-02-28 21:33:23
 *  Author: Christoffer
 */ 

#include "spi.h"

void spi_init(spi_init_t *spi_settings) 
{
	SPCR		|= (1 << SPE);
	SPI_PORT	|= (1 << SPI_MOSI_PIN) | (1 << SPI_SCK_PIN) | (1 << SPI_CS_PIN);
	
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
