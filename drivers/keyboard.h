#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// Initialize keyboard driver and interrupt handler
void keyboard_init(void);

// Read one character from keyboard buffer (blocking)
char keyboard_get_char(void);

// Optional but why the fuck not?: check if character is available (non-blocking)
int keyboard_has_char(void);

#endif
