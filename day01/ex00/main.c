#include <avr/io.h>

int main(void)
{
	// datasheet, p.85
	DDRB |= (1 << PB1);
	while (1)
	{
		// datasheet, p.84
		PORTB ^= (1 << PB1);
		for (volatile uint32_t i = 0; i < 250000; i++)
		{}
	}

}
