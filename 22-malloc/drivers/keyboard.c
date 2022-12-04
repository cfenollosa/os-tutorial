#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C
#define LSHIFT_DOWN 0x2a
#define LSHIFT_UP 0xaa
int caps = 0;
static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    if (scancode == LSHIFT_UP){caps=0;}
    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        if (key_buffer[0] != '\0') {
            backspace(key_buffer);
            kprint_backspace();
        }
    } else if (scancode == ENTER) {
        kprint("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    }else if (scancode == LSHIFT_DOWN) {
        if (caps == 0) {
            caps++;
        }
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that kprint only accepts char[] */
        if (caps == 1) {letter = chrupper(letter);};
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kprint(str);
    }
    UNUSED(regs);
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}
