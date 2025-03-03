#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= 0b00010111;
	PORTB |= 0b00010111;
	DDRD &= ~(1 << PD2);
	DDRD &= ~(1 << PD4);
	PORTD |= (1 << PD2);
	PORTD |= (1 << PD4);

	while (1)
	{
		if (!(PIND & (1 << PD2)))
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD2)))
				PORTB--;
			while (!(PIND & (1 << PD2)));
		}
		if (!(PIND & (1 << PD4)))
		{
			_delay_ms(50);
			if (!(PIND & (1 << PD4)))
				PORTB++;
			while (!(PIND & (1 << PD4)));
		}
	}
}
