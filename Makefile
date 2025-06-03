CC = gcc
CFLAGS = -Wall -Wextra -I./src
SRC = src/arg_handling.c src/common.c /usr/lib/x86_64-linux-gnu/libi2c.so
TARGET = i2c-eeprom

all: $(TARGET)

read-eeprom: src/read-eeprom.c $(SRC)
	$(CC) $(CFLAGS) -o read-eeprom $(SRC) src/read-eeprom.c

write-eeprom: src/write-eeprom.c $(SRC)
	$(CC) $(CFLAGS) -o write-eeprom $(SRC) src/write-eeprom.c

clean:
	rm -f $(TARGET)