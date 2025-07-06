#include "../drivers/keyboard.h"
#include "../drivers/timer.h"
#include "../drivers/serial.h"
#include "interrupts.h"

void irq_handler_common(uint8_t irq) {
    switch(irq) {
        case 0:
            timer_handler();
            break;
        case 1:
            keyboard_handler();
            break;
        case 4:  // COM1 IRQ
            // Could add serial_handler() here if implemented IRQ-driven
            break;
        default:
            // Unhandled IRQ
            break;
    }
}
