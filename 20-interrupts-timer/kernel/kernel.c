#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main() {
    isr_install();

    asm volatile("sti");
    init_timer(50);
}
