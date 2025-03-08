#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200
#define UBRR (F_CPU / 16 / (UART_BAUDRATE - 1))

void	uart_init(unsigned int ubrr)
{
	// datasheet, p.185
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;

	// datasheet, p.201 - 203
	// UART Control and Status Register
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0); // enable receiver and transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits data
}

// datasheet, p.186
void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // USART Data Register Empty
	UDR0 = c;
}

char	uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0))); // wait for data to be received
	return UDR0;
}

int main(void)
{
	uart_init(UBRR); // Universal Asynchronous Receiver/Transmitter
	while (1)
	{
		char c = uart_rx();
		uart_tx(c);
	}
}
