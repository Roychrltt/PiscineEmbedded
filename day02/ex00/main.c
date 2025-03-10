#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200
#define UBRR (F_CPU / 16 / (UART_BAUDRATE - 1))

// 8N1 : each character is transmitted using 8 bits, no parity bit, 1 stop bit
void	uart_init(unsigned int ubrr)
{
	// datasheet, p.185
	// USART Baud Rate Register
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// datasheet, p.201 - 203
	// UART Control and Status Register
	UCSR0B = (1 << TXEN0); // enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits data
}

// datasheet, p.186
void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // USART Data Register Empty
	UDR0 = c;
}

int main(void)
{
	uart_init(UBRR); // Universal Asynchronous Receiver/Transmitter
	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
}
