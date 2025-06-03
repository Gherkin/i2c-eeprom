#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>
#include <unistd.h>
#include <stdint.h>
#include <arg_handling.h>

unsigned char *buffer = NULL; // Buffer to hold read data

int main(int argc, char *argv[]) {
    if(parse_arguments(argc, argv)) {
        return 0; // Exit after displaying help
    }

    if(address_len == 8) {
        printf("only 16-bit supported at the moment\n");
        return 1; // Exit if address length is not supported
    }

    FILE *input_file = fopen(bin_file, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open binary file.\n");
        return 1;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    if(address_len == 8 && file_size > 256) {
        fprintf(stderr, "Error: File size exceeds 256 bytes for 8-bit address length.\n");
        fclose(input_file);
        return 1;
    } else if(address_len == 16 && file_size > 65536) {
        fprintf(stderr, "Error: File size exceeds 65536 bytes for 16-bit address length.\n");
        fclose(input_file);
        return 1;
    }

    buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory for buffer.\n");
        fclose(input_file);
        return 1;
    }
    long bytes_read = fread(buffer, 1, file_size, input_file);    
    fclose(input_file); // Close the input file
    if(bytes_read != file_size) {
        fprintf(stderr, "Error: Could not read the entire binary file.\n");
        free(buffer);
        return 1;
    }

    int fd = open_i2c_device(bus_index);

    for(uint16_t i = 0; i < bytes_read; i++) {
        if(i % 256 == 0) {
            fprintf(stderr, "Writing to device 0x%02x on bus /dev/i2c-%d, progress 0x%04x\n", dev_address, bus_index, i);
        }

        int error = i2c_write_byte(fd, dev_address, i, buffer[i]); 
        if(error != 0) {
            fprintf(stderr, "Error: Failed to write byte %d to EEPROM.\n", i);
            free(buffer);
            close(fd); // Close the I2C device
            return 1;
        }
    }

    close(fd); // Close the I2C device
    return 0;
} 