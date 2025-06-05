#ifndef COMMON_H
#define COMMON_H

#include <stdint.h>

int open_i2c_device(int bus_number);
int i2c_write_byte(int fd, int addr, uint16_t reg, uint8_t value, int address_len);
int i2c_read_byte_rs(int fd, int addr, uint16_t reg, uint8_t *value, int address_len);
int i2c_read_byte(int fd, int addr, uint8_t *value);
int i2c_write_word(int fd, int addr, uint16_t value);


#endif