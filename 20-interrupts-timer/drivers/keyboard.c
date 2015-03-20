#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"

static void keyboard_callback(registers_t regs) {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);
    char *sc_ascii;
    int_to_ascii(scancode, sc_ascii);
    kprint("Keyboard scancode: ");
    kprint(sc_ascii);
    kprint(", ");
    print_letter(scancode);
    kprint("\n");
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback); 
}

void print_letter(u8 scancode) {
    switch (scancode) {
        case 0x0:
            kprint("ERROR");
            break;
        case 0x1:
            kprint("ESC");
            break;
        case 0x2:
            kprint("1");
            break;
        case 0x3:
            kprint("2");
            break;
        case 0x4:
            kprint("3");
            break;
        case 0x5:
            kprint("4");
            break;
        case 0x6:
            kprint("5");
            break;
        case 0x7:
            kprint("6");
            break;
        case 0x8:
            kprint("7");
            break;
        case 0x9:
            kprint("8");
            break;
        case 0x0A:
            kprint("9");
            break;
        case 0x0B:
            kprint("0");
            break;
        case 0x0C:
            kprint("-");
            break;
        case 0x0D:
            kprint("+");
            break;
        case 0x0E:
            kprint("Backspace");
            break;
        case 0x0F:
            kprint("Tab");
            break;
        case 0x10:
            kprint("Q");
            break;
        case 0x11:
            kprint("W");
            break;
        case 0x12:
            kprint("E");
            break;
        case 0x13:
            kprint("R");
            break;
        case 0x14:
            kprint("T");
            break;
        case 0x15:
            kprint("Y");
            break;
        case 0x16:
            kprint("U");
            break;
        case 0x17:
            kprint("I");
            break;
        case 0x18:
            kprint("O");
            break;
        case 0x19:
            kprint("P");
            break;
		case 0x1A:
			kprint("[");
			break;
		case 0x1B:
			kprint("]");
			break;
		case 0x1C:
			kprint("ENTER");
			break;
		case 0x1D:
			kprint("LCtrl");
			break;
		case 0x1E:
			kprint("A");
			break;
		case 0x1F:
			kprint("S");
			break;
        case 0x20:
            kprint("D");
            break;
        case 0x21:
            kprint("F");
            break;
        case 0x22:
            kprint("G");
            break;
        case 0x23:
            kprint("H");
            break;
        case 0x24:
            kprint("J");
            break;
        case 0x25:
            kprint("K");
            break;
        case 0x26:
            kprint("L");
            break;
        case 0x27:
            kprint(";");
            break;
        case 0x28:
            kprint("'");
            break;
        case 0x29:
            kprint("`");
            break;
		case 0x2A:
			kprint("LShift");
			break;
		case 0x2B:
			kprint("\\");
			break;
		case 0x2C:
			kprint("Z");
			break;
		case 0x2D:
			kprint("X");
			break;
		case 0x2E:
			kprint("C");
			break;
		case 0x2F:
			kprint("V");
			break;
        case 0x30:
            kprint("B");
            break;
        case 0x31:
            kprint("N");
            break;
        case 0x32:
            kprint("M");
            break;
        case 0x33:
            kprint(",");
            break;
        case 0x34:
            kprint(".");
            break;
        case 0x35:
            kprint("/");
            break;
        case 0x36:
            kprint("Rshift");
            break;
        case 0x37:
            kprint("Keypad *");
            break;
        case 0x38:
            kprint("LAlt");
            break;
        case 0x39:
            kprint("Spc");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80 
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                kprint("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                kprint("key up ");
                print_letter(scancode - 0x80);
            } else kprint("Unknown key up");
            break;
    }
}

