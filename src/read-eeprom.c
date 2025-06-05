#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>
#include <unistd.h>
#include <stdint.h>
#include <arg_handling.h>

unsigned char *buffer; // Buffer to hold read data

int main(int argc, char *argv[]) {
    if(parse_arguments(argc, argv)) {
        return 0; // Exit after displaying help
    }

    buffer = malloc(data_len); // Allocate memory for the buffer
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory for buffer.\n");
        return 1;
    }

    int fd = open_i2c_device(bus_index); // Open I2C device on bus 1


    for(uint16_t i = 0; i < data_len; i++) {
        i2c_read_byte_rs(fd, dev_address, i, &buffer[i], address_len); // Read from EEPROM at address 0x50
    }

    FILE *output_file = fopen(bin_file, "wb");
    if (!output_file) {
        perror("Failed to open output file");
        close(fd); // Close the I2C device
        return 1;
    }
    size_t bytes_written = fwrite(buffer, 1, sizeof(buffer), output_file);
    if (bytes_written != sizeof(buffer)) {
        perror("Failed to write all data to output file");
        fclose(output_file);
        close(fd); // Close the I2C device
        return 1;
    }
    fclose(output_file); // Close the output file
    close(fd); // Close the I2C device
    return 0;
} 