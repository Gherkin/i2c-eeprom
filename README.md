# CLI Utility

This project is a command-line interface (CLI) utility that processes command-line arguments and provides help text for users.

## Features

- Handles command-line arguments
- Displays help text for `-h` and `--help` options

## Files

- `src/main.c`: Entry point of the CLI utility.
- `src/args.h`: Header file for argument handling functions.
- `Makefile`: Build instructions for compiling the project.

## Building the Project

To build the CLI utility, run the following command in the project root directory:

```
make
```

This will compile the source files and create the executable.

## Running the CLI Utility

After building the project, you can run the CLI utility with the following command:

```
./cli-utility [options]
```

### Options

- `-h`, `--help`: Display help text and usage information.

## Usage Example

To see the help text, run:

```
./cli-utility -h
```

or

```
./cli-utility --help
``` 

This will display the available options and usage instructions for the CLI utility.