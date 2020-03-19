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


#define SPI_TEST		1
#define ENCODER_TEST	2
#define UART_TEST		3

#define MODE			


volatile usart0_t *usart0 = (volatile usart0_t *) 0x000000C0;
volatile usart1_t *usart1 = (volatile usart1_t *) 0x000000C8;


spi_init_t spi_settings = { .data_order		= SPI_DORD_MSB,
							.spi_master		= TRUE,
							.clock_polarity = 1,
							.clock_phase	= 0,
							.clock_rate		= SPI_FCPU_DIV_16,
							.double_speed	= FALSE};
							
volatile uint8_t rx_data;


void uart_init(void);
uint16_t val;

uint16_t agc_data, error;
uint16_t angle_data;
uint16_t agc_data1, error1;
uint16_t angle_data1;
uint16_t deg;
uint8_t agc;

int main(void)
{
	_delay_ms(100);
	spi_set_cs();
	spi_init(&spi_settings);
	

	uart_init();
	//sei();


    
	//as5048_clear_error();	
	
	
	while (1) {
		agc_data1 = as5048_read_angle();
		angle_data = as5048_read_agc();

		agc_data = as5048_read_angle();
		angle_data1 = as5048_read_agc();




		if (( agc_data & ((1<< CORDIC_OF_BIT)|(1<< COMP_HIGH_BIT)|(1<< COMP_LOW_BIT)) ) == 0) {			/**< Check diagnostics bits for magnetic compensation and CORDIC overflow which tells if data is valid. */
			deg = angle_decode(angle_data);
			agc = (uint8_t) agc_data;
			// TODO: UART output deg value
		}
	}
}
		
//#if MODE == SPI_TEST
//
	//while (1) {
//
		//SPI_PORT &= ~(1 << SPI_CS_PIN);
		//spi_txrx_byte(0b11001100);
		//SPI_PORT |= (1 << SPI_CS_PIN);
		//_delay_us(5);
		//SPI_PORT &= ~(1 << SPI_CS_PIN);
  		//spi_txrx_16bit(0b0000111101010101);
		//SPI_PORT |= (1 << SPI_CS_PIN);
		//_delay_ms(5);
		  //
	//}
		  //
//#elif MODE == ENCODER_TEST
//
	//while (1) {
		//agc_data = as5048_read_angle();
		////angle_data = as5048_read_agc();
//
//
		//if (( agc_data & ((1<< CORDIC_OF_BIT)|(1<< COMP_HIGH_BIT)|(1<< COMP_LOW_BIT)) ) == 0) {			/**< Check diagnostics bits for magnetic compensation and CORDIC overflow which tells if data is valid. */
			//deg = angle_decode(angle_data);
			//agc = (uint8_t) agc_data;
			//// TODO: UART output deg value
		//}
	//}
		//
//#elif MODE == UART_TEST
//
	//while (1) {
		//if (val > 65535) val = 0;
		//usart1_send_uint16_as_ascii_string(val);
		//val += 500;
		//_delay_ms(1);
	//}
	//
//#endif




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

