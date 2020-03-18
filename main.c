/*
 * as5048_mag_rotary_encoder.c
 *
 * Created: 2020-02-28 21:30:07
 * Author : Christoffer
 */ 

#include "fcpu.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "spi.h"
#include "as5048a.h"




volatile usart0_t *usart0 = (volatile usart0_t *) 0x000000C0;
volatile usart1_t *usart1 = (volatile usart1_t *) 0x000000C8;


//spi_init_t spi_settings = { .data_order		= SPI_DORD_MSB,
							//.spi_master		= TRUE,
							//.clock_polarity = 0,
							//.clock_phase	= 0,
							//.clock_rate		= SPI_FCPU_DIV_4,
							//.double_speed	= FALSE};
							
volatile uint8_t rx_data;


void uart_init(void);
uint16_t val;

int main(void)
{
	
	//spi_set_cs();
	//spi_init(&spi_settings);
	

	uart_init();
	sei();


    while (1) {
		//SPI_PORT &= ~(1 << SPI_CS_PIN);
		//spi_txrx(0b11001100);
		//SPI_PORT |= (1 << SPI_CS_PIN);
  		//spi_txrx_16bit(0b0000111101010101);
		//spi_read_8(0b01010101);
		usart1_send_two_byte_as_ascii_string(val);
		val += 5;
		if (val == 65535) val = 0;
		_delay_ms(1);

    }
}


void uart_init() {
	


	usart1->tx_enable = TRUE;
	usart1->rx_enable = TRUE;
	usart1->rx_complete_int_enable = TRUE;
	usart1_set_baudrate();

}

ISR(USART1_RX_vect) {
	
	rx_data = UDR1;
	UDR1 = rx_data;
	
	
	
}

