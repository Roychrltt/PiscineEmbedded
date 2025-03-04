#include <avr/io.h>

int main(void)
{
	// datasheet, p.85
	DDRB |= (1 << PB0);
	PORTB |= (1 << PB0);

	while (1);
}
