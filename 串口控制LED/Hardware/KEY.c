#include "stm32f10x.h"
#include  "Delay.h"
void Key_Init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB,ENABLE );                //PB1
	
	GPIO_InitTypeDef    GPIO_Initstructure;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU ;                          //上拉输入，默认为高电平（按键按下变为低电平，检测）
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_1 ;
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
}
uint8_t Key_GetNum(void)
{
	uint8_t  KeyNum =0;
	if  (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
	{
		Delay_ms (20);
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0);
		Delay_ms (20);
		KeyNum =1;
		
	}
	return KeyNum;
}


	