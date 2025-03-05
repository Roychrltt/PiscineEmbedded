#include <avr/io.h>
#include <util/delay.h>

#define PRESCALER 256
#define TOP F_CPU / PRESCALER / 2
#define INCREMENT_UNIT TOP / 10

void	init_io()
{
	DDRB |= (1 << PB1);
	DDRD &= ~((1 << PD2) | (1 << PD4));
	PORTD |= (1 << PD2) | (1 << PD4);
}

void	init_timer()
{
	TCCR1A |= (1 << COM1A1); // toggle OC1A on compare match, PWM mode, phase correct
	TCCR1A |= (1 << WGM11); // PWM mode, phase correct
	TCCR1B |= (1 << WGM13); // set WGM Mode 10
	TCCR1B |= (1 << CS12); // prescaler 256

	ICR1 = TOP;
	OCR1A = INCREMENT_UNIT;
}

uint8_t	debounce(uint8_t pin)
{
	if (!(PIND & (1 << pin)))
	{
		_delay_ms(10);
		if (!(PIND & (1 << pin)))
		{
			while (!(PIND & (1 << pin)));
			_delay_ms(10);
			return 1;
		}
	}
	return 0;

}

int main(int argc, char *argv[])
{
	init_io();
	init_timer();
	while (1) {
		if (debounce(PD2))
		{
			if (OCR1A < TOP)
				OCR1A += INCREMENT_UNIT;
		}
		if (debounce(PD4))
		{
			if (OCR1A - INCREMENT_UNIT > 0)
				OCR1A -= INCREMENT_UNIT;
		}
	}
}
