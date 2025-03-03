#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1 << PB0);
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);
	while (1)
	{
		if (!(PIND & (1 << PD2)))
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD2)))
				PORTB ^= (1 << PB0);
			while (!(PIND & (1 << PD2)));
		}
	}
}
