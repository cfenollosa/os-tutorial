#include <stdint.h>
#include "keyboard.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 	0x0E
#define ENTER 		0x1C
#define CAPS_LOCK 	0x3A
#define TAB 		0x0F


static char key_buffer[256];

#define SC_MAX 57

int caps_count = 0;

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
        
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

const char sc_ascii_small[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) 
{
	/* The PIC leaves us the scancode in port 0x60 */
	uint8_t scancode = port_byte_in(0x60);

	if (scancode == CAPS_LOCK) ++caps_count; 	// Implement Caps Lock
	if (scancode > SC_MAX) return;
	if (scancode == BACKSPACE) {
		if (key_buffer[0] != '\0') { 	// No use of backspace if key_buffer is empty
			backspace(key_buffer);
			kprint_backspace();
		}
	} else if(scancode == ENTER) {
		kprint("\n");
		user_input(key_buffer); /* kernel-controlled function */
		key_buffer[0] = '\0';
	} else {
		char letter;
		if(caps_count % 2 == 0)
			letter = sc_ascii_small[(int)scancode];
		else
			letter = sc_ascii[(int)scancode];
		/* remember that kprint() accepts only char[] */
		char str[2] = {letter, '\0'};
		append(key_buffer, letter);
		kprint(str);
	}

	UNUSED(regs);
}

void init_keyboard() 
{
	register_interrupt_handler(IRQ1, keyboard_callback);
}

