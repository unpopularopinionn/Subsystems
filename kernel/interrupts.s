; interrupts.s

global irq0_handler
global irq1_handler
global irq2_handler
global irq3_handler
global irq4_handler
global irq5_handler
global irq6_handler
global irq7_handler
global irq8_handler
global irq9_handler
global irq10_handler
global irq11_handler
global irq12_handler
global irq13_handler
global irq14_handler
global irq15_handler

global idt_flush

section .text

; External C handler prototype
extern irq_handler

; Common IRQ handler prologue/epilogue macro to avoid repetition
%macro IRQ_HANDLER 1
%assign irqnum %1
irq%1_handler:
    cli
    push dword irqnum
    pusha
    call irq_handler
    popa
    add esp, 4
    sti
    iretd
%endmacro

IRQ_HANDLER 0
IRQ_HANDLER 1
IRQ_HANDLER 2
IRQ_HANDLER 3
IRQ_HANDLER 4
IRQ_HANDLER 5
IRQ_HANDLER 6
IRQ_HANDLER 7
IRQ_HANDLER 8
IRQ_HANDLER 9
IRQ_HANDLER 10
IRQ_HANDLER 11
IRQ_HANDLER 12
IRQ_HANDLER 13
IRQ_HANDLER 14
IRQ_HANDLER 15

; idt_flush - loads the IDT with lidt
; void idt_flush(uint32_t);
idt_flush:
    mov eax, [esp+4]
    lidt [eax]
    ret
