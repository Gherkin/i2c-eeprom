CC = gcc
CFLAGS = -Wall -Wextra -I./src -I/usr/include

-include config.mk

SRC = src/arg_handling.c src/common.c

all: read-eeprom write-eeprom

read-eeprom: src/read-eeprom.c $(SRC)
	$(CC) $(CFLAGS) $(KERNEL_INCLUDE) -o read-eeprom $(SRC) src/read-eeprom.c

write-eeprom: src/write-eeprom.c $(SRC)
	$(CC) $(CFLAGS) $(KERNEL_INCLUDE) -o write-eeprom $(SRC) src/write-eeprom.c

clean:
	rm -f $(TARGET) config.mk