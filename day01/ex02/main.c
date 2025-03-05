#include <avr/io.h>

int main(void)
{
	DDRB |= (1 << PB1);

	// datasheet, p141
	TCCR1A |= (1 << COM1A1); // toggle OC1A on compare match, PWM mode, phase correct
	TCCR1A |= (1 << WGM11); // PWM mode, phase correct
	TCCR1B |= (1 << WGM13); // set WGM Mode 10
	TCCR1B |= (1 << CS12); // prescaler 256

	ICR1 = 31249; // 16M / 256 / 2
	OCR1A = 3124; // ICP1 / 10
	while (1)
	{
	}
}
