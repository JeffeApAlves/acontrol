#ifndef XC_HEADER_CANCELA_H
#define	XC_HEADER_CANCELA_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>

#define PIN_SENSOR_ENTRADA  0b00001000
#define PIN_SENSOR_SAIDA    0b00010000
#define PIN_SIGNAL          0b00000001
#define PIN_TICKET          0b00100000

#define SENSOR_ENTRADA      PORTAbits.RA3 
#define SENSOR_SAIDA        PORTAbits.RA4

#define TICKET              PORTAbits.RA5 
#define SIGNAL              PORTBbits.RB0 

#define TIME_SIGNAL         1000        // 1000ms  = 1s
#define TIME_CLOSE          5000        // 5000ms  = 5s


typedef enum{
    
    CANCELA_INIT,
    CANCELA_REQUEST_TICKET,
    CANCELA_OPEN,
    CANCELA_CLOSE
    
}cancela_status_t;

void cancela_saida_close(void);
void cancela_saida_open(void);
void cancela_entrada_close(void);
void cancela_entrada_open(void);
void cancela_init(void);
void cancela_task(void);
inline bool veiculo_presente_saida(void);
inline bool veiculo_presente_entrada(void);
inline bool ticket_ok(void);
void request_print_ticket(void);
void handle_cancela_entrada(void);
void handle_cancela_saida(void);

extern short timer_signal,timer_close;

#endif

