#include "serial.h"
#include <stdint.h>

#define SERIAL_PORT 0x3F8  // COM1

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void serial_init(void) {
    outb(SERIAL_PORT + 1, 0x00);    // Disable all interrupts
    outb(SERIAL_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(SERIAL_PORT + 0, 0x01);    // Set divisor to 1 (lo byte) 115200 baud
    outb(SERIAL_PORT + 1, 0x00);    // Divisor hi byte
    outb(SERIAL_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(SERIAL_PORT + 2, 0xC7);    // Enable FIFO, clear them, 14-byte threshold
    outb(SERIAL_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int serial_is_transmit_empty(void) {
    return inb(SERIAL_PORT + 5) & 0x20;
}

void serial_write_byte(char c) {
    while (!serial_is_transmit_empty()) {
        __asm__ volatile("pause");
    }
    outb(SERIAL_PORT, c);
}

void serial_write(const char* str) {
    while (*str) {
        if (*str == '\n')
            serial_write_byte('\r');
        serial_write_byte(*str++);
    }
}
