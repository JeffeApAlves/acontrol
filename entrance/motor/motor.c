#include "motor.h"

unsigned short timer_motor = TIMER_STEP_MOTOR;

motor_t motor_entrada,motor_saida;

/**
 *  A cada TIMER_STEP_MOTOR ms essa função sera executada para criar os sinais da bobina do motor
 *   
 * 
 */
void motor_task(void){
    
    if(timer_motor){
        
        motor_handle(&motor_entrada);
        motor_handle(&motor_saida);
        
        timer_motor=TIMER_STEP_MOTOR;
    }
}
//------------------------------------------------------------------------------

/**
 * 
 *  Handle individual do motor
 * 
 * @param motor
 */
void motor_handle(motor_t* motor){
    
    unsigned char coils,step;
    
    if(motor->status==MOTOR_DESLIGADO){
        
        coils = 0;
        
    }else{

        if(motor->voltas){

            step = ((motor->step++) % STEP_POR_VOLTA);
            
            if(motor->direction==SENTIDO_HORARIO){

                coils   = (!step? 0x02 : (0x01 << step));

            } else{

                coils   = (!step? 0x08:  (0x01 >>  step));
            }
            
            if(step==0){
                motor->voltas--;
            }
        }
        
        motor->set(coils);
    }
}
//------------------------------------------------------------------------------

/**
 * Liga o motor na direção indicada
 * 
 * @param motor
 * @param direction
 */
void motor_start(motor_t* motor,direction_t direction,unsigned char voltas){

    motor->status       = MOTOR_LIGADO;
    motor->direction    = direction;
    motor->voltas       = voltas;
}
//------------------------------------------------------------------------------

/**
 * Desliga o motor
 * 
 * @param motor
 */
void motor_off(motor_t* motor){
  
    motor->status       = MOTOR_DESLIGADO;
    motor->voltas       = 0;
}
//------------------------------------------------------------------------------

/**
 * Atualiza saidas dos motores
 * 
 * @param val
 */
void motor_entrada_set(unsigned char val){

    M1_L1 = PIN_M1_L1 & val; 
    M1_L2 = PIN_M1_L2 & val; 
    M1_L3 = PIN_M1_L3 & val; 
    M1_L4 = PIN_M1_L4 & val;    
}
//------------------------------------------------------------------------------

/**
 * Atualiza saidas dos motores
 * 
 * @param val
 */
void motor_saida_set(unsigned char val){

    M2_L1 = PIN_M2_L1 & val; 
    M2_L2 = PIN_M2_L2 & val; 
    M2_L3 = PIN_M2_L3 & val; 
    M2_L4 = PIN_M2_L4 & val; 
}
//------------------------------------------------------------------------------

/**
 * Inicializa motor M1 (cancela de entrada)
 * 
 */
void motor_entrada_init(void){
    
    // Configura pinos do motor como saida
    TRISA &= (~(PIN_M2_L1 | PIN_M2_L2 | PIN_M2_L3 |  PIN_M2_L4));
 
    motor_entrada.direction = SENTIDO_HORARIO;
    motor_entrada.step      = 0;
    motor_entrada.set       = motor_entrada_set;
            
    motor_off(&motor_entrada);
    motor_entrada_set(0);
}
//------------------------------------------------------------------------------
/**
 * 
 * Inicializa motor M2 (cancela de saida)
 * 
 */
void motor_saida_init(void){

    // Configura pinos do motor como saida
    TRISB &= (~(PIN_M2_L1 | PIN_M2_L2 | PIN_M2_L3 |  PIN_M2_L4));

    motor_saida.direction = SENTIDO_HORARIO;
    motor_saida.step      = 0;
    motor_saida.set       = motor_saida_set;

    motor_off(&motor_saida);
    motor_saida_set(0);
}
//------------------------------------------------------------------------------

/**
 * Inicaliza motores
 * 
 */
void motor_init(void){

    timer_motor = TIMER_STEP_MOTOR;
    motor_saida_init();
    motor_entrada_init();
}
//------------------------------------------------------------------------------