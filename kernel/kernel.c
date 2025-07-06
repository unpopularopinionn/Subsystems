#include "../drivers/vga.h"
#include "../drivers/keyboard.h"
#include "../drivers/serial.h"
#include "../drivers/timer.h"
#include "interrupts.h"
#include <stdint.h>

// Panic handler: print message, halt CPU
void panic(const char* msg) {
    vga_set_color(0x0F, 0x04); // Bright white on red
    vga_clear();
    vga_puts("KERNEL PANIC: ");
    vga_puts(msg);
    vga_puts("\nSystem halted.\n");

    asm volatile ("cli; hlt");  // Disable interrupts and halt CPU forever
}

// Simple minimal console
void console_loop(void) {
    vga_set_color(0x0F, 0x00); // Light gray on black

    while (1) {
        char c = keyboard_get_char();

        if (c) {
            if (c == 0x03) { // Ctrl-C triggers panic for demo
                panic("User triggered panic (Ctrl-C)");
            }
            serial_write_byte(c);
            vga_putc(c);
        }
    }
}

void kernel_main(void) {
    // Initialize VGA and clear screen
    vga_set_color(0x0F, 0x00);
    vga_clear();

    vga_puts("MyKernel v1.0\n");
    vga_puts("Initializing subsystems...\n");

    // Initialize serial first (early debugging)
    serial_init();
    serial_write_string("Serial port ready.\n");

    // Initialize keyboard and timer drivers
    keyboard_init();
    timer_init(100);  // 100Hz timer interrupts

    // Remap PIC and setup IDT for interrupts
    pic_remap();
    idt_init();

    asm volatile("sti");  // Enable interrupts globally

    vga_set_color(0x0A, 0x00); // Light green on black
    vga_puts("Initialization complete!\n");
    serial_write_string("Initialization complete!\n");

    vga_set_color(0x0F, 0x00);

    // Enter console loop (keyboard input echoes to VGA & serial)
    console_loop();

    // Should never reach here, but just in case:
    panic("Kernel halted unexpectedly.");
}
