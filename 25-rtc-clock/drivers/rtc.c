#include "rtc.h"
#include "screen.h"
#include "../cpu/ports.h"
#include "../libc/string.h"
#include <stdint.h>

/* CMOS ports: first we tell it which register we want, then we read it */
#define CMOS_ADDRESS 0x70
#define CMOS_DATA 0x71

static uint8_t read_register(uint8_t reg) {
    port_byte_out(CMOS_ADDRESS, reg);
    return port_byte_in(CMOS_DATA);
}

/* Bit 7 of register 0x0A is set while the RTC is updating its values */
static int update_in_progress() {
    return read_register(0x0A) & 0x80;
}

/* BCD stores each decimal digit in 4 bits, so 0x59 means 59 */
static uint8_t bcd_to_binary(uint8_t bcd) {
    return (bcd & 0x0F) + ((bcd >> 4) * 10);
}

void read_rtc(rtc_time_t *t) {
    /* Don't read in the middle of an update, we could get garbage */
    while (update_in_progress());

    t->second = read_register(0x00);
    t->minute = read_register(0x02);
    t->hour   = read_register(0x04);
    t->day    = read_register(0x07);
    t->month  = read_register(0x08);
    t->year   = read_register(0x09);

    /* Bit 2 of register 0x0B tells us if the values are binary or BCD */
    uint8_t reg_b = read_register(0x0B);
    if (!(reg_b & 0x04)) {
        t->second = bcd_to_binary(t->second);
        t->minute = bcd_to_binary(t->minute);
        t->hour   = bcd_to_binary(t->hour);
        t->day    = bcd_to_binary(t->day);
        t->month  = bcd_to_binary(t->month);
        t->year   = bcd_to_binary(t->year);
    }

    /* The RTC only gives us the last two digits */
    t->year += 2000;
}

/* Always print two digits, so 5 becomes "05" */
static void append_two_digits(char str[], int n) {
    append(str, n / 10 + '0');
    append(str, n % 10 + '0');
}

/* Writes "HH:MM:SS" into str */
void time_to_ascii(rtc_time_t *t, char str[]) {
    append_two_digits(str, t->hour);
    append(str, ':');
    append_two_digits(str, t->minute);
    append(str, ':');
    append_two_digits(str, t->second);
}

/* Writes "DD/MM/YYYY" into str */
void date_to_ascii(rtc_time_t *t, char str[]) {
    append_two_digits(str, t->day);
    append(str, '/');
    append_two_digits(str, t->month);
    append(str, '/');
    char year[8] = "";
    int_to_ascii(t->year, year);
    int i;
    for (i = 0; year[i] != '\0'; i++) append(str, year[i]);
}

/* Draws " HH:MM:SS  DD/MM/YYYY " on the top right corner */
void show_clock() {
    rtc_time_t t;
    read_rtc(&t);

    char clock[32] = " ";
    time_to_ascii(&t, clock);
    append(clock, ' ');
    append(clock, ' ');
    date_to_ascii(&t, clock);
    append(clock, ' ');

    kprint_at_color(clock, MAX_COLS - strlen(clock), 0, WHITE_ON_BLUE);
}
