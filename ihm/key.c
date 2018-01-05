#include "key.h"

//Temporizador de debounce
unsigned char debounce_botao = DEBOUNCE;

/**
 * Verica se o botão foi pressionado por um tempo minimo definido pela constante DEBOUNCE
 * @return 
 */
bool key_read(){
 
    if(!BOTAO ){
    
        debounce_botao = DEBOUNCE;
    }
    
    return !debounce_botao;
}
//-----------------------------------------------------------

/**
 * 
 * Inicializa o ihm
 */
void ihm_init(){
    
    TRISA |= BIT_BOTAO; 
    
    debounce_botao = DEBOUNCE;
}
//-----------------------------------------------------------
