#include <avr/io.h>
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
	UCSR0B = (1 << TXEN0); // enable transmitter
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // 8 bits data
}

// datasheet, p.186
void	uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0))); // USART Data Register Empty
	UDR0 = c;
}

void	uart_printstr(const char* str)
{
	int i = 0;
	while (str[i])
	{
		uart_tx(str[i]);
		i++;
	}
}

void	timer_init()
{
	TCCR1B |= (1 << CS12) | (1 << CS10); // prescaler as 1024
	TCCR1B |= (1 << WGM12);
	OCR1A = 31250;
	TIMSK1 |= (1 << OCIE1A);
}

ISR(TIMER1_COMPA_vect)
{
	uart_printstr("Hello World!\r\n");
}

int main(void)
{
	uart_init(UBRR); // Universal Asynchronous Receiver/Transmitter
	timer_init();
	sei(); // enable global interrupts
	while (1)
	{
	}
}
