#include <avr/io.h>

void	init_timer1(void)
{
	// datasheet, p.100
	DDRB |= (1 << PB1);

	// datesheet, p.141
	// CTC Mode, clear timer on compare match
	TCCR1B |= (1 << WGM12); // Time/Counter Clock Register timer1 B
							// Waveform Generation Mode
	
	// datasheet, p.140
	TCCR1A |= (1 << COM1A0); // Compare Output Mode, Toggle OC1A/OC1B on Compare Mode
							 // Output Compare Pins for timer1's regsiter A/B

	// datesheet, p.122, p.141
	// Output Compare Register 1A
	OCR1A = 7812; // 16M / 1024 / 2

	// datasheet, p.143
	TCCR1B |= (1 << CS12) | (1 << CS10); // set prescaler to 1024 to slow down the closk
}

int main(void)
{
	init_timer1();
	while (1)
	{
	}
}
