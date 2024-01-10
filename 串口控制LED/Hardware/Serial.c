#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>





uint8_t Serial_RxData;
uint8_t Serial_RxFlag;


void Serial_Init(void)
{
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1,ENABLE);
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef    GPIO_Initstructure;                                  //USART1_TX               PA9
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP ;                  //复用推挽输出
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_9  ;
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;               //USART_RX       PA10
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_10  ;
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
    USART_InitTypeDef  USART_InitStructure;                      //USART初始化
	USART_InitStructure.USART_BaudRate =9600 ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;    //无硬件数据流控制
	USART_InitStructure.USART_Mode  =  USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity   =  USART_Parity_No;                       //无奇偶校验位
	USART_InitStructure.USART_StopBits =USART_StopBits_1;	
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       ////USART1 NVIC配置
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           //开启USART1通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;        
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	
	NVIC_Init(&NVIC_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);          //开始串口接受中断
	
	USART_Init(USART1 ,&USART_InitStructure);           
	USART_Cmd (USART1,ENABLE);
	
}


void Serial_SendByte(uint8_t Byte)                          // 串口发送数据给上位机
{
	USART_SendData(USART1, Byte);
	while(USART_GetFlagStatus (USART1 ,USART_FLAG_TXE )==RESET);
	
}



void Serial_SendString(char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(String[i]);
	}
}



int fputc(int ch, FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}




void Serial_Printf(char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(String);
}






uint8_t Serial_GetRxFlag(void)
{
	if (Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	return 0;
}

uint8_t Serial_GetRxData(void)
{
	return Serial_RxData;
}

//void USART1_IRQHandler(void)                    //串口1中断服务程序，接受上位机的数据
//{
//	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)            //接受中断信号
//	{
//		Serial_RxData = USART_ReceiveData(USART1);                              //读取接受到的串口数据



//		Serial_RxFlag = 1;
//		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
//	}
//}
