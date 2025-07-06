#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stddef.h>

// VGA colors baby!!
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

void vga_clear();
void vga_set_color(uint8_t fg, uint8_t bg);
void vga_putc(char c);
void vga_puts(const char* str);
void vga_puthex(uint32_t n);
void vga_putdec(uint32_t n);
void vga_move_cursor(uint8_t row, uint8_t col);
void vga_get_cursor(uint8_t* row, uint8_t* col);
void vga_scroll();
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_disable_cursor();

#endif
