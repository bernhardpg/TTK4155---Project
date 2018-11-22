#ifndef SYSTEM_CONSTANTS_H_INCLUDED
#define SYSTEM_CONSTANTS_H_INCLUDED

#define F_CPU 16000000 // 16 MHz
#define RX_VECTOR USART0_RX_vect
#define UART_DATA_BIT USBS0
#define MOSI_PIN DDB2
#define SCK_PIN DDB1
#define SS_PIN PB0
#define SELECT_PIN PB7
#define RECEIVE_INTERRUPT INT4
#define RECEIVE_ISC0 ISC40
#define RECEIVE_ISC1 ISC41
#define RECEIVE_ISC_REG EICRB
#define RECEIVE_CONTROL_REG EIMSK

#endif
