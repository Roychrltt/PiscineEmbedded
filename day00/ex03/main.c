#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// datasheet, p.85
	DDRB |= (1 << PB0);
	PORTB &= ~(1 << PB0);
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	while (1)
	{
		// datasheet, p.84
		if (!(PIND & (1 << PD2)))
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD2)))
				PORTB ^= (1 << PB0);
			while (!(PIND & (1 << PD2)));
		}
	}
}
