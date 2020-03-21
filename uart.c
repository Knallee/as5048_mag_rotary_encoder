/*
 * uart.c
 *
 * Created: 2020-03-03 21:20:00
 *  Author: 2AM PULLUPS
 */

 #include "uart.h"
 

extern volatile usart0_t *usart0;		// on�dig?
extern volatile usart1_t *usart1;		// on�dig?

void usart0_tx_data(uint8_t data)
{
	while (!( UCSR0A & (1<<UDRE0)));	// Wait for empty transmit buffer
	UDR0 = data;						// Put data into buffer, sends the data
}

void usart0_tx_char(char ch)
{
	while (!( UCSR0A & (1<<UDRE0)));	// Wait for empty transmit buffer
	UDR0 = ch;							// Put data into buffer, sends the data
}

void usart0_tx_string(char *string)
{
	while(*string != 0x00) usart0_tx_char(*string++);
}

void usart0_set_baudrate(int baud)
{
	UBRR0 = UBBR0_VAL;
}

void usart1_tx_data(uint8_t data)
{
	while (!( UCSR1A & (1<<UDRE1)));	// Wait for empty transmit buffer
	UDR1 = data;						// Put data into buffer, sends the data
}

void usart1_tx_char(char ch)
{
	while (!( UCSR1A & (1<<UDRE1)));	// Wait for empty transmit buffer
	UDR1 = ch;							// Put data into buffer, sends the data
}

void usart1_tx_string(char *string)
{
	while(*string != 0x00) usart1_tx_char(*string++);
}

void usart1_set_baudrate()
{
	UBRR1 = UBBR1_VAL;
}

void usart1_send_uint8_as_ascii_string(uint8_t val)
{
	char string[4];
	itoa(val, string, 10);
	usart1_tx_string(string);
	usart1_tx_data(END_OF_TX_CHAR);
}

void usart1_send_uint16_as_ascii_string(uint16_t val)
{
	char string[6];
	itoa(val, string, 10);
	usart1_tx_string(string);
	usart1_tx_data(END_OF_TX_CHAR);
}