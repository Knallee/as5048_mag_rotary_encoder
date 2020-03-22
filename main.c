/*
 * as5048_mag_rotary_encoder.c
 *
 * Created: 2020-02-28 21:30:07
 * Author : 2AM PULLUPS
 */ 

#include "fcpu.h"

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "spi.h"
#include "as5048a.h"
#include "atmega1284.h"


#define SPI_TEST		1
#define UART_TEXT_TEST	2
#define ENCODER_TEST	3
#define UART_TEST		4
#define UART_YAT_TEST   5

#define MODE			UART_TEXT_TEST

volatile uint8_t rx_data;
void data_integrity(uint16_t data);

uint16_t val;
uint16_t agc_data, angle_data, error_data;
uint16_t deg;
uint8_t agc;

int main(void)
{	
	spi_init();
	usart1_init();	
	
	//sei();
    
	//as5048_clear_error();	
		
#if MODE == SPI_TEST

	while (1) {
		spi_txrx_byte(0b11001100);
  		spi_txrx_16bit(0b0000111101010101);		  
	}
	  
#elif MODE == UART_TEXT_TEST
	uint16_t tick = 0;
	char buf[256];
	deg = 99;
	agc = 44;
	
	while (1) {
		snprintf(buf, sizeof buf, "%d%s%d%s%d%s", tick, ". Deg: ", deg , ", AGC:" , agc, "        ");
		usart1_tx_string(buf);
		_delay_ms(1000);
		tick++;
	}
	
	
#elif MODE == ENCODER_TEST	
	while (1) {
		agc_data = as5048_read_agc();
		data_integrity(agc_data);				/* Check for error flag */
		angle_data = as5048_read_angle();
		data_integrity(angle_data);				/* Check for error flag */
		
		deg = angle_decode(angle_data);
		agc = (uint8_t) agc_data;
		usart1_tx_data(deg/2);	// 1 circle = 180 deg, deal with it!
		usart1_tx_data(agc);
		
		
		//if (( agc_data & ((1<< CORDIC_OF_BIT)|(1<< COMP_HIGH_BIT)|(1<< COMP_LOW_BIT)) ) == 0) {			/**< Check diagnostics bits for magnetic compensation and CORDIC overflow which tells if data is valid. */
		//	deg = angle_decode(angle_data);
		//	agc = (uint8_t) agc_data;
		// TODO: UART output deg value
	}
#elif MODE == UART_TEST

	while (1) {
		if (val > 65535) val = 0;
		usart1_send_uint16_as_ascii_string(val);
		val += 500;
		_delay_ms(1);
	}
	
#elif MODE == UART_YAT_TEST

	while (1) {
		usart1_tx_string("Din mamma!");
		_delay_ms(1000);
	}
	
#endif

}





ISR(USART1_RX_vect) {
	rx_data = UDR1;
	UDR1 = rx_data;
}

// Debugger
void data_integrity(uint16_t data) {
	uint16_t checker = com_error_check(data);
	if ((checker & (1 << ERROR_FLAG)) == (1 << ERROR_FLAG)) {
		usart1_tx_string("COM error lul!");
		usart1_tx_char('\n');
		if((checker & (1 << PARITY_ERROR_MISO)) != 0) {
			usart1_tx_string("Parity error MISO.");
			usart1_tx_char('\n');
		}
		if((checker & (1 << PARITY_ERROR_MOSI)) != 0) {
			usart1_tx_string("Parity error MOSI.");
			usart1_tx_char('\n');
		}
		if((checker & (1 << COMMAND_INVALID)) != 0) {
			usart1_tx_string("Command Invalid.");
			usart1_tx_char('\n');
		}
		if((checker & (1 << FRAMING_ERROR)) != 0) {
			usart1_tx_string("Framing error.");
			usart1_tx_char('\n');
		}
	}
}
