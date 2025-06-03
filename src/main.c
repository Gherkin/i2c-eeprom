#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arg_handling.h"

FILE *input_file = NULL;
unsigned char *buffer = NULL;

int main(int argc, char *argv[]) {
    if (parse_arguments(argc, argv)) {
        return 0; // Exit after displaying help
    }

    input_file = fopen(bin_file, "rb");
    if (!input_file) {
        fprintf(stderr, "Error: Could not open binary file '%s'.\n", bin_file);
        return 1;
    }

    fseek(input_file, 0, SEEK_END);
    long file_size = ftell(input_file);
    fseek(input_file, 0, SEEK_SET);

    buffer = malloc(file_size);
    if (!buffer) {
        fprintf(stderr, "Error: Could not allocate memory for buffer.\n");
        fclose(input_file);
        return 1;
    }
    size_t bytes_read = fread(buffer, 1, file_size, input_file);
    if (bytes_read != file_size) {
        fprintf(stderr, "Error: Could not read the entire binary file '%s'.\n", bin_file);
        free(buffer);
        fclose(input_file);
        return 1;
    }
    
    for(size_t i = 0; i < bytes_read; i++) {
        printf("%02x ", buffer[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }


    free(buffer);
    fclose(input_file);
    return 0;
}