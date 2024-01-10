#include "stm32f10x.h"  
#ifndef  __SERIAL_H
#define __SERIAL_H

#include<stdio.h>

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);

void Serial_Printf(char *format, ...);
void Serial_SendString(char *String);

void Serial_Printf(char *format, ...);
void USART1_IRQHandler(void);
uint8_t Serial_GetRxFlag(void);
uint8_t Serial_GetRxData(void);


#endif
