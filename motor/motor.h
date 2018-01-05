#ifndef XC_HEADER_MOTOR_H
#define	XC_HEADER_MOTOR_H

#include <xc.h> 

#define PIN_M2_L1   0b10000000
#define PIN_M2_L2   0b01000000
#define PIN_M2_L3   0b00100000
#define PIN_M2_L4   0b00010000

#define PIN_M1_L1   0b00000010
#define PIN_M1_L2   0b00000001
#define PIN_M1_L3   0b10000000
#define PIN_M1_L4   0b01000000

#define M1_L1       PORTAbits.RA1 
#define M1_L2       PORTAbits.RA0 
#define M1_L3       PORTAbits.RA7 
#define M1_L4       PORTAbits.RA6 

#define M2_L1       PORTBbits.RB7 
#define M2_L2       PORTBbits.RB6 
#define M2_L3       PORTBbits.RB5 
#define M2_L4       PORTBbits.RB4 

#define STEP_POR_VOLTA      4       // 4 step por volta
#define TIMER_STEP_MOTOR    20      // 20 ms

typedef	void (*set_val_t)(unsigned char);

typedef enum {
    
    MOTOR_CREATE,
    MOTOR_INIT_OK,
    MOTOR_DESLIGADO,
    MOTOR_LIGADO,
    
}motor_status_t;

typedef enum {

    SENTIDO_HORARIO,
    SENTIDO_ANTI_HORARIO

}direction_t;

typedef struct  {

    unsigned char   voltas;
    unsigned char   step;
    motor_status_t  status;
    direction_t     direction;
    set_val_t       set;
    
}motor_t;

void motor_init(void);
void motor_start(motor_t* motor,direction_t direction,unsigned char voltas);
void motor_stop(motor_t* motor);
void motor_entrada_set(unsigned char val);
void motor_saida_set(unsigned char val);
void motor_task(void);
void motor_handle(motor_t* motor);

extern unsigned short timer_motor;
extern motor_t motor_entrada,motor_saida;

#endif	/* XC_HEADER_TEMPLATE_H */

