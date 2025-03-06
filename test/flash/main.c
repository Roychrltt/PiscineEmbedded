#include <avr/io.h>

int main(void)
{
	DDRB |= (1 << 0);

	TCCR1B |= ((1 << CS10) | (1 << CS11));
	while (1)
	{
		if (TCNT1 >= 62499)
		{
			PORTB ^= (1 << 0);
			TCNT1 = 0;
		}
	}
}
