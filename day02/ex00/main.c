#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define UART_BAUDRATE 115200
#define UBRR_VALUE (F_CPU / 16 / UART_BAUDRATE - 1)

static void	uart_init()
{
	UBRR0H = (UBRR_VALUE >> 8);
	UBRR0L = UBRR_VALUE;

	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

static void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = c;
}

int main(void)
{
	uart_init();
	while (1)
	{
		uart_tx('Z');
		_delay_ms(1000);
	}
}
