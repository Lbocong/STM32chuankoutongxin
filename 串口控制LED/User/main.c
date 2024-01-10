#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
 #include "KEY.h"
#include "SERIAL.h"
 uint8_t  KeyNum;

extern uint8_t Serial_RxData;
 extern uint8_t Serial_RxFlag;

int main(void)
{	
	 LED_init();
	 Key_Init();
      Serial_Init( );
	
}
	
	 void USART1_IRQHandler(void)                    //串口1中断服务程序，接受上位机的数据
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)            //接受中断信号
	{
		Serial_RxData = USART_ReceiveData(USART1);                              //读取接受到的串口数据
		if(Serial_RxData=='A')LED_ON();
		if(Serial_RxData=='B')LED_OFF();
		Serial_RxFlag = 1;
		
		
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
	
	
	
	
	
	
	
	
	

