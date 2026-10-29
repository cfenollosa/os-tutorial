#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../drivers/rtc.h"
#include "kernel.h"
#include "../libc/string.h"
#include "../libc/mem.h"
#include <stdint.h>

void kernel_main() {
    isr_install();
    irq_install();

    /* Start with a clean screen, the first line is for the clock */
    clear_screen();
    show_clock();
    kprint("\nType something, it will go through the kernel\n"
        "Type END to halt the CPU or PAGE to request a kmalloc()\n"
        "Type TIME or DATE to read the real time clock\n> ");
}

void user_input(char *input) {
    if (strcmp(input, "END") == 0) {
        kprint("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "PAGE") == 0) {
        /* Lesson 22: Code to test kmalloc, the rest is unchanged */
        uint32_t phys_addr;
        uint32_t page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        kprint("Page: ");
        kprint(page_str);
        kprint(", physical address: ");
        kprint(phys_str);
        kprint("\n");
    } else if (strcmp(input, "TIME") == 0) {
        rtc_time_t t;
        read_rtc(&t);
        char time_str[16] = "";
        time_to_ascii(&t, time_str);
        kprint("Time: ");
        kprint(time_str);
        kprint("\n");
    } else if (strcmp(input, "DATE") == 0) {
        rtc_time_t t;
        read_rtc(&t);
        char date_str[16] = "";
        date_to_ascii(&t, date_str);
        kprint("Date: ");
        kprint(date_str);
        kprint("\n");
    }
    kprint("You said: ");
    kprint(input);
    kprint("\n> ");
}
