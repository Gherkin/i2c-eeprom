#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int open_i2c_device(int bus_number) {
    char device[20];
    snprintf(device, sizeof(device), "/dev/i2c-%d", bus_number);
    int fd = open(device, O_RDWR);
    if (fd < 0) {
        perror("Failed to open I2C device");
        return -1;
    }
    return fd;
}

int i2c_write_byte(int fd, int addr, uint16_t reg, uint8_t value) {
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("Failed to set I2C slave address");
        return -1;
    }
    uint8_t buf[3];
    buf[0] = (reg >> 8) & 0xFF; // high byte of address
    buf[1] = reg & 0xFF;        // low byte of address
    buf[2] = value;             // data byte

    int tries = 0;
    while (tries < 100) {
        ssize_t written = write(fd, buf, 3);
        if( written < 0) {
            tries++;
        } else if (written != 3) {
            fprintf(stderr, "Partial write to I2C device: expected 3 bytes, wrote %zd bytes\n", written);
            return -1;
        } else {
            // Successfully wrote 3 bytes
            return 0;
        }
    }
    if( tries >= 20) {
        perror("Failed to write byte to I2C device after multiple attempts");
        return -1;
    }
    //usleep(10000);
    return 0;
}

int i2c_read_byte_rs(int fd, int addr, uint16_t reg, uint8_t *value) {
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];

    uint8_t addr_buf[2];
    addr_buf[0] = (reg >> 8) & 0xFF;
    addr_buf[1] = reg & 0xFF;

    messages[0].addr  = addr;
    messages[0].flags = 0; // Write
    messages[0].len   = 2;
    messages[0].buf   = addr_buf;

    messages[1].addr  = addr;
    messages[1].flags = I2C_M_RD; // Read
    messages[1].len   = 1;
    messages[1].buf   = value;

    packets.msgs  = messages;
    packets.nmsgs = 2;

    if (ioctl(fd, I2C_RDWR, &packets) < 0) {
        perror("Failed to perform I2C_RDWR with repeated start");
        return -1;
    }
    return 0;
}
