MCU = atmega328p
F_CPU = 16000000UL

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUDRATE = 115200

CFLAGS = -Wall -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU)

SRC = main.c
OBJ = $(SRC:.c=.o)
NAME = main

all: hex flash

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

hex: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME).bin $(OBJ)
	$(OBJCOPY) -O ihex -R .eeprom $(NAME).bin $(NAME).hex

flash: hex
	$(AVRDUDE) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b ${BAUDRATE} -U flash:w:$(NAME).hex:i

clean:
	rm -f $(OBJ) $(NAME).bin $(NAME).hex

