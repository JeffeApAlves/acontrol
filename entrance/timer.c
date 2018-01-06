#include "motor/motor.h"
#include "cancela/cancela.h"
#include "ihm/key.h"
#include "timer.h"

short timer_signal;

/**
 * 
 * Vetor de interrupção de timer gerencia os temporizadores
 * base de tempo 1ms
 * 
 * 
 */
void interrupt tc_int  (void){

    if(INTCONbits.T0IF){ 
        
        INTCONbits.T0IF = 0;    // reseta flag de interrupção 

        if(!timer_motor)        // periodo step do motor
            timer_motor--;
        
        if(!timer_signal) 
            timer_signal--;
        
        if(!timer_close)
            timer_close--;
        
        if(debounce_botao)
            debounce_botao--;
    }
}
//------------------------------------------------------------------------------

/**
 * 
 * Incializa timer1
 * 
 */
void timer1_init(void){
 
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    T1CON  = 0b00000001;             //Prescaler 1:1 e on
}
//------------------------------------------------------------------------------

/**
 * 
 * Inicializa timer 0
 * 
 */
void timer0_init(void){
    
    OPTION_REG = 0x81;      //prescaler 1:4
    TMR0 = 6;               // (4/clock) * (256 - 6) * 4 = 1ms
    INTCONbits.T0IE = 1;
}
//------------------------------------------------------------------------------
