/*
 * File:   main.c
 * Author: Jefferson
 *
 * Created on October 2, 2017, 3:48 PM
 */


#include <xc.h>
#include "timer.h"
#include "configuracao.h"
#include "cancela/cancela.h"
#include "motor/motor.h"
#include "ihm/key.h"

void main(void) {
    
    motor_init();
   
    ihm_init();

    cancela_init();
    
    timer0_init();

    INTCONbits.GIE  = 1;             // Global interrupt enable

    while(1){

        // Clear dog
        CLRWDT();
        
        motor_task();
        
        cancela_task();
        
        if(key_read()){
 
            request_print_ticket();
        }
    }
    
    return;
}
//-----------------------------------------------------------------------------