#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <common.h>
#include <unistd.h>
#include <stdint.h>

unsigned char buffer[32768]; // Buffer to hold read data

int main(int argc, char *argv[]) {
    int fd = open_i2c_device(0); // Open I2C device on bus 1

    //i2c_write_word(fd, 0x50, (uint16_t) 0x0000); // Write a word to EEPROM at address 0x50

    for(uint16_t i = 0; i < 32768; i++) {
        i2c_read_byte_rs(fd, 0x50, i, &buffer[i]); // Read from EEPROM at address 0x50
        //i2c_read_byte(fd, 0x50, buffer + i); // Read from EEPROM at address 0x50
    }

    FILE *output_file = fopen("eeprom_dump.bin", "wb");
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