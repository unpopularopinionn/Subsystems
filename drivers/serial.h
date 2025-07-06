#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>

// Initialize COM1 serial port at 115200 baud, 8N1
void serial_init(void);

// Write a single byte to serial port (blocking)
void serial_write_byte(char c);

// Write a null-terminated string to serial port
void serial_write(const char* str);

// Check if transmit buffer empty imma stop typing silly comments
int serial_is_transmit_empty(void);

#endif
// LOCK IN CHAT!