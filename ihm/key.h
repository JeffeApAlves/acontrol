#ifndef XC_HEADER_KEY_H
#define	XC_HEADER_KEY_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

#define BIT_BOTAO   0b00000100

#define DEBOUNCE        50      // 50 ms

#define BOTAO PORTAbits.RA2 

bool key_read();

void ihm_init();

extern unsigned char debounce_botao;
#endif

