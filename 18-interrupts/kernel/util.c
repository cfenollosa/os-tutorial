#include "util.h"

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    // reverse
    char aux_char = 0;
    unsigned int front_index = 0;
    unsigned int back_index = strlen(str)-1;
    while(front_index < back_index){
        aux_char = str[front_index];
        str[front_index] = str[back_index];
        str[back_index] = aux_char;
        front_index++;
        back_index--;
    }
}
