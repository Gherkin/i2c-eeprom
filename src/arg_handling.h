#ifndef ARGS_H
#define ARGS_H

#include <stdint.h>

int parse_arguments(int argc, char *argv[]);
void display_help();

extern int address_len; // Address length in bits (8 or 16)
extern int bus_index; // I2C bus index (0 for /dev/i2c-0)
extern uint8_t dev_address; // Device address in hex (default 0x50)
extern char *bin_file; // Path to the binary file to be processed
extern int data_len; // Data length in bytes (default 32768)

#endif // ARGS_H