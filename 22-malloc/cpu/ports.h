#ifndef PORTS_H
#define PORTS_H

#include "../cpu/type.h"

unsigned char port_byte_in (u16 port);
void port_byte_out (u16 port, u8 data);
unsigned short port_word_in (u16 port);
void port_word_out (u16 port, u16 data);

#endif
