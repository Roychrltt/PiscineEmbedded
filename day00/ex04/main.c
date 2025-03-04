#include <avr/io.h>
#include <util/delay.h>

void	init_io(uint8_t value)
{
	// datasheet, p.85
	DDRB |= 0x17;
	PORTB = value;
	DDRD &= ~((1 << PD2) | (1 << PD4));
	PORTD |= (1 << PD2) | (1 << PD4);
}

uint8_t debounce(uint8_t pin)
{
	// datasheet, p.84
	if (!(PIND & (1 << pin)))
	{
		_delay_ms(50);
		if (!(PIND & (1 << pin)))
		{
			while (!(PIND & (1 << pin))) _delay_ms(10);
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	uint8_t value = 0;
	init_io(value);
	while (1)
	{
		if (debounce(PD2))
		{
			if (value == 0x07) value += 9;
			else if (value < 0x17) value++;
		}
		if (debounce(PD4))
		{
			if (value == 0x10) value -= 9;
			else if (value > 0) value--;
		}
		PORTB = (value & 0x07) | (value & 0x10);
	}
}
