#include "utils.h"

/**
 * Rotina de delay
 */
void delay(long tempo) {
    
    while(tempo > 0) { 
        _delay(1000); 
        tempo--; 
    } 
}
//-----------------------------------------------------------------------------
