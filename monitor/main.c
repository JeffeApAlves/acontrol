/*
 * File:   main.c
 * Author: Jefferson
 *
 * Created on October 3, 2017, 7:32 AM
 */

// PIC10F200 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config CP = OFF         // Code Protect (Code protection off)
#pragma config MCLRE = OFF      // Master Clear Enable (GP3/MCLR pin fuction is digital I/O, MCLR internally tied to VDD)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define SENSOR      GPIObits.GP3
#define LED_RED     GPIObits.GP1
#define LED_GREEN   GPIObits.GP0
#define SIGNAL      GPIObits.GP2
#define TIME        5000

#include <stdbool.h>
#include <xc.h>

void init(void){
 
    TRISGPIO = 0b00001000;
    GPIO     = 0x00;
}
//------------------------------------------------------------------------------

/**
 * Para considerar a vaga livre o sensor tera que ficar por um tempo no estado 1
 * 
 * @return 
 */
inline bool space_free(){

    short tempo = TIME;
    
    while(tempo > 0 && SENSOR == 1) {
        
        _delay(1000); 
        tempo--; 
    } 

    return tempo==0;
}
//------------------------------------------------------------------------------

void update_status(void){
 
    if(space_free()){
       
        SIGNAL      = 0;
        LED_RED     = 0;
        LED_GREEN   = 1;
        
    }else{

        SIGNAL      = 1;
        LED_RED     = 1;
        LED_GREEN   = 0;
    }
}
//------------------------------------------------------------------------------

void main(void) {
    
    init();
    
    while(1){
        
        CLRWDT();
        
        update_status();
    }
    
    return;
}
//------------------------------------------------------------------------------