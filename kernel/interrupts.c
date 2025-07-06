#include <stdint.h>

// Ports for PIC
#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

// IDT entry structure (packed)
struct idt_entry {
    uint16_t base_lo;
    uint16_t sel;        // Kernel segment selector
    uint8_t  always0;
    uint8_t  flags;      // flags
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

#define IDT_ENTRIES 256
static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr idtp;

extern void idt_flush(uint32_t);

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

// PIC remap function — remaps IRQs 0-15 to interrupts 32-47
void pic_remap() {
    uint8_t a1 = inb(PIC1_DATA);
    uint8_t a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, 0x20); // IRQ0-7 -> int 32-39
    outb(PIC2_DATA, 0x28); // IRQ8-15 -> int 40-47
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);
}

// Send EOI to PICs
void pic_send_eoi(uint8_t irq) {
    if (irq >= 8) {
        outb(PIC2_COMMAND, 0x20);
    }
    outb(PIC1_COMMAND, 0x20);
}

// Set an entry in the IDT
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_lo = base & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
}

// Initialize IDT with IRQ handlers and exceptions (simple version)
void idt_init() {
    idtp.limit = (sizeof(struct idt_entry) * IDT_ENTRIES) - 1;
    idtp.base = (uint32_t)&idt;

    // Clear IDT
    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // Set IRQ handlers (IRQ0 = interrupt 32, IRQ1=33)
    extern void irq0_handler();
    extern void irq1_handler();
    extern void irq2_handler();
    extern void irq3_handler();
    extern void irq4_handler();
    extern void irq5_handler();
    extern void irq6_handler();
    extern void irq7_handler();
    extern void irq8_handler();
    extern void irq9_handler();
    extern void irq10_handler();
    extern void irq11_handler();
    extern void irq12_handler();
    extern void irq13_handler();
    extern void irq14_handler();
    extern void irq15_handler();

    idt_set_gate(32, (uint32_t)irq0_handler, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1_handler, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2_handler, 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3_handler, 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4_handler, 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5_handler, 0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6_handler, 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7_handler, 0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8_handler, 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9_handler, 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10_handler, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11_handler, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12_handler, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13_handler, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14_handler, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15_handler, 0x08, 0x8E);

    idt_flush((uint32_t)&idtp);
}

extern void irq_handler_common(uint8_t irq);

void irq_handler(uint8_t irq) {
    irq_handler_common(irq);
    pic_send_eoi(irq);
}
