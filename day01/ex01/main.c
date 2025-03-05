#include <avr/io.h>

void	init_timer1(void)
{
	DDRB |= (1 << PB1);

	// datasheet, p.12, 140
	TCCR1A |= (1 << COM1A0); // Compare Output Mode, Toggle OC1A on Compare Mode

	// datesheet, p.141
	TCCR1B |= (1 << WGM12); // CTC mode, clear counter when it reaches OCR1A

	// datasheet, p.143
	TCCR1B |= (1 << CS12); // set prescaler to 256 to slow down the closk
	
	// datesheet, p.122, p.141
	OCR1A = 31249; // 16M / 256 / 2 - 1
}

int main(void)
{
	init_timer1();
	while (1)
	{
	}
}
