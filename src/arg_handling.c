#include "arg_handling.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>


int address_len = 16; // Default address length
int bus_index = -1;
uint8_t dev_address = 0x50; // Default device address
char *bin_file = NULL;
int data_len = 32768; // Default data length

void display_help() {
    printf("Usage: %s [options] bin-file\n", "i2c-eeprom");
    printf("Options:\n");
    printf("  -h, --help                    Display this help text\n");
    printf("  -a, --address-len [length]    Set the address length (default 16)\n");
    printf("  -b, --bus-index [index]       The I2C bus index (0 for /dev/i2c-0)\n");
    printf("  -d, --dev-address [addr]      The device address in hex (default 0x50)\n");
    printf("  -l, --data-len [length]       Set the data length in bytes (default 32768)\n");
    printf("\n");

}

int parse_arguments(int argc, char *argv[]) {
    int i = 1;
    if(argc < 2) {
        display_help();
        return -1;
    }

    while(i < argc) {
        if(argv[i][0] != '-') {
            // If the argument is not an option, break the loop
            break;
        }

        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            display_help();
            return -1; // Exit after displaying help
        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--address-len") == 0) {
            if (i + 1 < argc) {
                address_len = atoi(argv[++i]);
                if (address_len != 8 && address_len != 16) {
                    fprintf(stderr, "Error: Invalid address length. Use 8 or 16.\n");
                    return -1;
                }
                // Set the address length in your application context
                printf("Address length set to %d bits.\n", address_len);
            } else {
                fprintf(stderr, "Error: Missing value for --address-len option.\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-b") == 0 || strcmp(argv[i], "--bus-index") == 0) {
            if (i + 1 < argc) {
                bus_index = atoi(argv[++i]);
                // Set the bus index in your application context
                printf("I2C bus index set to %d.\n", bus_index);
            } else {
                fprintf(stderr, "Error: Missing value for --bus-index option.\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dev-address") == 0) {
            if (i + 1 < argc) {
                char *endptr;
                dev_address = (uint8_t)strtol(argv[++i], &endptr, 16);
                if (*endptr != '\0') {
                    fprintf(stderr, "Error: Invalid device address format. Use hex format (e.g., 0x50).\n");
                    return -1;
                }
            } else {
                fprintf(stderr, "Error: Missing value for --dev-address option.\n");
                return -1;
            }
        } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--data-len") == 0) {
            if (i + 1 < argc) {
                data_len = atoi(argv[++i]);
                if (data_len <= 0) {
                    fprintf(stderr, "Error: Invalid data length. Must be a positive integer.\n");
                    return -1;
                }
                // Set the data length in your application context
                printf("Data length set to %d bytes.\n", data_len);
            } else {
                fprintf(stderr, "Error: Missing value for --data-len option.\n");
                return -1;
            }
        } else {
            fprintf(stderr, "Error: Unknown option '%s'. Use -h or --help for usage information.\n", argv[i]);
            return -1;
        }
        i++;
    }
    if (i != argc - 1) {
        fprintf(stderr, "Error: Expected a binary file argument after options.\n");
        return -1;
    }

    bin_file = argv[i];
    printf("Binary file set to: %s\n", bin_file);


    if (bus_index < 0) {
        fprintf(stderr, "Error: I2C bus index must be specified with -b or --bus-index.\n");
        return -1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            display_help();
        }
    }
    return 0;
}