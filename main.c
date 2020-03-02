/*
 * as5048_mag_rotary_encoder.c
 *
 * Created: 2020-02-28 21:30:07
 * Author : Christoffer
 */ 

#include "fcpu.h"

#include <avr/io.h>
#include "spi.h"
#include "as5048a.h"

spi_init_t spi_settings = { .data_order		= SPI_DORD_MSB,
							.spi_master		= TRUE,
							.clock_polarity = 0,
							.clock_phase	= 0,
							.clock_rate		= SPI_FCPU_DIV_4,
							.double_speed	= FALSE};


int main(void)
{
	spi_set_cs();
	spi_init(&spi_settings);


    while (1) {
		//SPI_PORT &= ~(1 << SPI_CS_PIN);
		//spi_txrx(0b11001100);
		//SPI_PORT |= (1 << SPI_CS_PIN);
  		spi_write_16(0b0000111101010101, 0x0f0f);
		//spi_read_8(0b01010101);
		_delay_ms(10);

    }
}


