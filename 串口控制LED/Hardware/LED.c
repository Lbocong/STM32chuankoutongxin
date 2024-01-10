#include "stm32f10x.h"

void LED_init(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE );                    //PA2     低电平点亮
	
	GPIO_InitTypeDef    GPIO_Initstructure;
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP ;             //普通推挽输出
	GPIO_Initstructure.GPIO_Pin =GPIO_Pin_2  ;
	GPIO_Initstructure.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	GPIO_SetBits( GPIOA,GPIO_Pin_2);

}

void LED_ON(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
}
void LED_OFF(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
}

void LED_Turn(void)
{
	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
	{
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	}
	else{GPIO_ResetBits(GPIOA,GPIO_Pin_2);}
	
}