/*
 * uart.h
 *
 * Created: 2020-03-03 21:20:28
 *  Author: Knalle
 */ 


#ifndef UART_H_
#define UART_H_

#include "fcpu.h"
#include <avr/io.h>
//#include <util/setbaud.h>

#define TRUE	1
#define FALSE	0

		
#define PARITY_ERROR_FLAG			2	/**< Bit position of the USART Parity Error in usart control and status register A. */
#define DATA_OVERRUN_FLAG			3	/**< Bit position of the Data OverRun in usart control and status register A. */
#define FRAME_ERROR_FLAG			4	/**< Bit position of the Frame Error in usart control and status register A. */
#define DATA_REGISTER_EMPTY_FLAG	5	/**< Bit position of the USART Data Register Empty in usart control and status register A. */
#define TX_COMPLETE_FLAG			6	/**< Bit position of the USART Transmit Complete in usart control and status register A. */
#define RX_COMPLETE_FLAG			7	/**< Bit position of the USART Receive Complete in usart control and status register A. */
#define TX_BIT_8					0	/**< Bit position of the USART Transmit Data Bit 8 (9th bit) in usart control and status register A. */
#define RX_BIT_8					1	/**< Bit position of the USART Receive Data Bit 8 (9th bit) in usart control and status register A. */		
#define USART_CLOCK_POLARITY_RF		0	/**< Set .clock_polarity to this macro for tx data to change on rising edge and rx data to be sampled on falling. This is default. */
#define USART_CLOCK_POLARITY_FR		2	/**< Set .clock_polarity to this macro for tx data to change on falling edge and rx data to be sampled on rising. */
#define USART_5_BITS_C				0	/**< Set .nbr_data_bits_c to this macro for 5 bit data. */
#define USART_6_BITS_C				1	/**< Set .nbr_data_bits_c to this macro for 6 bit data. */
#define USART_7_BITS_C				2	/**< Set .nbr_data_bits_c to this macro for 7 bit data. */
#define USART_8_BITS_C				3	/**< Set .nbr_data_bits_c to this macro for 8 bit data. This is default. */
#define USART_STOP_BITS_1			0	/**< Set .nbr_stop_bits to this macro for 2 stop bits. */
#define USART_STOP_BITS_2			1	/**< Set .nbr_stop_bits to this macro for 2 stop bits. */
#define USART_PARITY_MODE_ODD		3	/**< Set .parity_mode to this macro for odd parity. */
#define USART_PARITY_MODE_EVEN		2	/**< Set .parity_mode to this macro for even parity. */
#define USART_PARITY_MODE_DISABLED	0	/**< Set .parity_mode to this macro for disable parity. This is default. */
#define USART_MODE_ASYNC			0	/**< Set .usart_mode to asynchronous mode. This is default. */
#define USART_MODE_SYNC				1	/**< Set .usart_mode to synchronous mode. */
#define USART_MODE_MSPI3			3	/**< Set .usart_mode for disable parity. This is default. */







typedef struct usart0_regs {
	volatile uint8_t multi_processor_mode 		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t double_speed				: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t parity_error_flag			: 1;	/**< Read only. */
	volatile uint8_t data_overrun_flag			: 1;	/**< Read only. */
	volatile uint8_t frame_error_flag			: 1;	/**< Read only. */
	volatile uint8_t data_register_empty_flag	: 1;	/**< Read only. */
	volatile uint8_t tx_complete_flag			: 1;	/**< Read only. */
	volatile uint8_t rx_complete_flag			: 1;	/**< Read only. */
														
	volatile uint8_t tx_bit_8					: 1;	/**< The ninth TX bit of the data packet. */
	volatile uint8_t rx_bit_8					: 1;	/**< The ninth TX bit of the data packet. */
	volatile uint8_t data_bits_9_b				: 1;	/**< Set this to TRUE (1) for nine data bits. nbr_data_bits_c needs to be set to USART_8_BITS_C. */
	volatile uint8_t tx_enable					: 1;	/**< Set to TRUE (1) to enables the transmitter. */
	volatile uint8_t rx_enable					: 1;	/**< Set to TRUE (1) to enables the receiver. */
	volatile uint8_t dreg_empty_int_enable		: 1;	/**< USART data register empty interrupt. Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default.*/
	volatile uint8_t tx_complete_int_enable		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t rx_complete_int_enable		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
														
	volatile uint8_t clock_polarity				: 1;	/**< Rising or falling edge. Use the USART_CLOCK_POL macros. Transmit data is changed on rising edge and rx data sampled on falling by default. */
	volatile uint8_t nbr_data_bits_c			: 2;	/**< The number of data bits to form a packet, see USART_X_BITS macros. For nine bits see data_bits_9_b. Eight bits is default. */
	volatile uint8_t nbr_stop_bits				: 1;	/**< One or two stop bits. Use USART_STOP_BITS macro. One by default. */
	volatile uint8_t parity_mode				: 2;	/**< Even or odd parity. Use USART_PARITY macros. Disabled by default. */
	volatile uint8_t usart_mode					: 2;	/**< Asynchronous, synchronous or master SPI. Use USART_MODE macros. Asynchronous by default.*/	
} usart0_t;



typedef struct usart1_regs{
	volatile uint8_t multi_processor_mode 		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t double_speed				: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t parity_error_flag			: 1;	/**< Read only. */
	volatile uint8_t data_overrun_flag			: 1;	/**< Read only. */
	volatile uint8_t frame_error_flag			: 1;	/**< Read only. */
	volatile uint8_t data_register_empty_flag	: 1;	/**< Read only. */
	volatile uint8_t tx_complete_flag			: 1;	/**< Read only. */
	volatile uint8_t rx_complete_flag			: 1;	/**< Read only. */
	
	volatile uint8_t tx_bit_8					: 1;	/**< The ninth TX bit of the data packet. */
	volatile uint8_t rx_bit_8					: 1;	/**< The ninth TX bit of the data packet. */
	volatile uint8_t data_bits_9_b				: 1;	/**< Set this to TRUE (1) for nine data bits. nbr_data_bits_c needs to be set to USART_8_BITS_C. */
	volatile uint8_t tx_enable					: 1;	/**< Set to TRUE (1) to enables the transmitter. */
	volatile uint8_t rx_enable					: 1;	/**< Set to TRUE (1) to enables the receiver. */
	volatile uint8_t dreg_empty_int_enable		: 1;	/**< USART data register empty interrupt. Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default.*/
	volatile uint8_t tx_complete_int_enable		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	volatile uint8_t rx_complete_int_enable		: 1;	/**< Set to TRUE (1) to enable, FALSE (0) to disable. Disabled by default. */
	
	volatile uint8_t clock_polarity				: 1;	/**< Rising or falling edge. Use the USART_CLOCK_POL macros. Transmit data is changed on rising edge and rx data sampled on falling by default. */
	volatile uint8_t nbr_data_bits_c			: 2;	/**< The number of data bits to form a packet, see USART_X_BITS macros. For nine bits see data_bits_9_b. Eight bits is default. */
	volatile uint8_t nbr_stop_bits				: 1;	/**< One or two stop bits. Use USART_STOP_BITS macro. One by default. */
	volatile uint8_t parity_mode				: 2;	/**< Even or odd parity. Use USART_PARITY macros. Disabled by default. */
	volatile uint8_t usart_mode					: 2;	/**< Asynchronous, synchronous or master SPI. Use USART_MODE macros. Asynchronous by default.*/
} usart1_t;


 //volatile usart0_t *usart0 = (volatile usart0_t *) 0x000000C0;
 //volatile usart1_t *usart1 = (volatile usart1_t *) 0x000000C8;

void usart0_tx_data(uint8_t data);
void usart0_tx_char(char ch);
void usart0_tx_string(char *string);
void usart0_set_baudrate();

void usart1_tx_data(uint8_t data);
void usart1_tx_char(char ch);
void usart1_tx_string(char *string);
void usart1_set_baudrate();

#endif /* UART_H_ */