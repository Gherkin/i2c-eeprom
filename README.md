# I2C EEPROM CLI Utilities

This project provides command-line utilities for reading from and writing to I2C EEPROM devices on Linux systems.

## Features

- Read the entire contents of an I2C EEPROM to a binary file
- Write a binary file to an I2C EEPROM
- Supports configurable I2C bus, device address, and address length
- Displays help text for `-h` and `--help` options

## Files

- `src/read-eeprom.c`: Utility to read EEPROM contents to `eeprom_dump.bin`
- `src/write-eeprom.c`: Utility to write a binary file to EEPROM
- `src/common.c` / `src/common.h`: Common I2C and EEPROM helper functions
- `src/arg_handling.c` / `src/arg_handling.h`: Command-line argument parsing
- `Makefile`: Build instructions for compiling the utilities

## Building the Project

To build the utilities, run the following command in the project root directory:

```
make
```

This will compile the source files and create the `read-eeprom` and `write-eeprom` executables.

## Usage

### Read EEPROM

```
./read-eeprom
```

This will read the entire EEPROM (default address 0x50 on bus 0) and write the contents to `eeprom_dump.bin`.

### Write EEPROM

```
./write-eeprom [options] bin-file
```

#### Options

- `-h`, `--help`                 Display help text and usage information
- `-l`, `--address-len [8|16]`   Set the address length in bits (default: 16)
- `-b`, `--bus-index [index]`    Set the I2C bus index (e.g., 0 for `/dev/i2c-0`)
- `-d`, `--dev-address [addr]`   Set the device address in hex (default: 0x50)

#### Example

```
./write-eeprom -b 1 -d 0x50 -l 16 firmware.bin
```

This writes `firmware.bin` to the EEPROM at address `0x50` on bus 1 using 16-bit addressing.

## Help

To see the help text for write-eeprom, run:

```
./write-eeprom -h
```

or

```
./write-eeprom --help
```