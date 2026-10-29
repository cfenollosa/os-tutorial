#ifndef RTC_H
#define RTC_H

#include <stdint.h>

typedef struct {
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint32_t year;
} rtc_time_t;

void read_rtc(rtc_time_t *t);
void time_to_ascii(rtc_time_t *t, char str[]);
void date_to_ascii(rtc_time_t *t, char str[]);
void show_clock();

#endif
