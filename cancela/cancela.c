#include "../motor/motor.h"
#include "cancela.h"

cancela_status_t cancela_entrada    = CANCELA_INIT;
cancela_status_t cancela_saida      = CANCELA_INIT;

// Temporizador do tempo em que o sinal de solictação ficará em niovel 1
short timer_signal  = TIME_SIGNAL;

// Temporizador para garantir a saida completa do veiculo antes de fechar
short timer_close   = TIME_CLOSE;

/**
 *
 * Função de gerenciamento das cancelas
 */
void cancela_task(void){

    handle_cancela_entrada();
    
    handle_cancela_saida();
}
//--------------------------------------------------------

/**
 * 
 * Gerenciamento da cancela de entrada
 */
void handle_cancela_entrada(void){

    if(cancela_entrada  == CANCELA_REQUEST_TICKET){
        
        if(!timer_signal){
            
            SIGNAL = 0;

            if(veiculo_presente_entrada() && ticket_ok()){

                cancela_entrada_open();
                
                timer_close = TIME_CLOSE;
            }
        }
    }else if(cancela_entrada  == CANCELA_OPEN){

        if(veiculo_presente_entrada()){

            timer_close = TIME_CLOSE;
            
        }else{
            
            cancela_entrada_close();
        }        
    }    
}
//--------------------------------------------------------

/**
 * 
 * Gerenciamento da cancela de saida
 */
void handle_cancela_saida(void){
}
//--------------------------------------------------------

/**
 * 
 *  Abre a cancela de entrada
 * 
 */
void cancela_entrada_open(void){

    cancela_entrada  = CANCELA_OPEN;
    
    motor_start(&motor_entrada,SENTIDO_HORARIO,3);
}
//--------------------------------------------------------

/**
 * 
 *  Fecha a cancela de entrada
 * 
 */
void cancela_entrada_close(void){

    cancela_entrada  = CANCELA_CLOSE;

    motor_start(&motor_entrada,SENTIDO_ANTI_HORARIO,3);    
}
//--------------------------------------------------------

/**
 * 
 *  Abre a cancela de saida
 * 
 */
void cancela_saida_open(void){

    cancela_saida  = CANCELA_OPEN;
    
    motor_start(&motor_saida,SENTIDO_HORARIO,3);
}
//--------------------------------------------------------

/**
 * 
 *  Fecha a cancela de saida
 * 
 */
void cancela_saida_close(void){

    cancela_saida  = CANCELA_CLOSE;

    motor_start(&motor_saida,SENTIDO_ANTI_HORARIO,3);    
}
//--------------------------------------------------------

/**
 * 
 *  Inicialização da cancelas
 * 
 */
void cancela_init(void){
    
    // Define como entrada os pinos conectados ao sensores de presença
    TRISA |= (PIN_SENSOR_ENTRADA | PIN_SENSOR_SAIDA | PIN_TICKET);

    // Define como saída o pino do sinal de ticket
    TRISB &= ~(PIN_SIGNAL);
    
    SIGNAL = 0;
    
    cancela_entrada = CANCELA_INIT;
    cancela_saida   = CANCELA_INIT;
}
//--------------------------------------------------------

/**
 * 
 * Solicata ticket antes de liberar a entrada
 */
void request_print_ticket(void){
    
    SIGNAL = 1;
    
    timer_signal    = TIME_SIGNAL;
    
    cancela_entrada  = CANCELA_REQUEST_TICKET;
}
//--------------------------------------------------------

/**
 * Retorna se o veiculo esta presente na cancela de entrada
 * 
 * @return 
 */
inline bool veiculo_presente_entrada(void){

    return SENSOR_ENTRADA==0;
}
//--------------------------------------------------------

/**
 * Retorna se o veiculo esta presente na cancela de saida
 * 
 * @return 
 */
inline bool veiculo_presente_saida(void){

    return SENSOR_SAIDA==0;
}
//--------------------------------------------------------

/**
 * Indica se o ticket foi impresso
 * 
 * @return 
 */
inline bool ticket_ok(void){

    return TICKET==1;
}
//--------------------------------------------------------
