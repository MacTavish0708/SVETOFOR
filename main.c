
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "misc.h"

int tiktak =0;
int r=0;
int g=10;
int gm=3;
int y=2;
int pg=4;
int pgm=5;
int d=6000000;



GPIO_InitTypeDef  GPIO_InitStructure;
void init_all()
{
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_3 ;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);


		GPIO_InitTypeDef gpio_cfg;
		GPIO_StructInit(&gpio_cfg);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		gpio_cfg.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio_cfg.GPIO_Pin = GPIO_Pin_0;
		GPIO_Init(GPIOB, &gpio_cfg);


		GPIO_InitTypeDef GPIO_InitStruct;
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);

		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);

		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
		EXTI_InitStruct.EXTI_Line = EXTI_Line0;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
		EXTI_Init(&EXTI_InitStruct);

}


void Delay(u32 ticks)
{
  while(ticks != 0) ticks--;
}



void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		Delay(500000);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1) {
		if(r==0){
        tiktak=1;
        r=1;
		}
		else {
			tiktak=0;
		    r=0;
		}
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
}
}



void avto_svetofor()
{
	  switch(tiktak){
	  case 0:
		   Delay(d);
		   GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		   GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		   GPIO_SetBits(GPIOA, GPIO_Pin_2);
		   Delay(d);
		   GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	  break;
	  case 1:
		  GPIO_SetBits(GPIOA, GPIO_Pin_3);
		   for(int i=1; i<=g; i++) //a
		     {
			   Delay(d);
		     }
		   for(int i=1; i<=gm; i++) //b
		     {
		  	   GPIO_ResetBits(GPIOA, GPIO_Pin_3);
			   Delay(d/2);
		  	   GPIO_SetBits(GPIOA, GPIO_Pin_3);
			   Delay(d/2);
		     }
		  GPIO_ResetBits(GPIOA, GPIO_Pin_3);
		  GPIO_SetBits(GPIOA, GPIO_Pin_2);
		   for(int i=1; i<=y; i++) //c
		     {
			   Delay(d);
		     }
		  GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		  GPIO_SetBits(GPIOA, GPIO_Pin_1);
		   for(int i=1; i<=g; i++) //d
		     {
			   Delay(d);
		     }
		  GPIO_SetBits(GPIOA, GPIO_Pin_2);
		   for(int i=1; i<=y; i++) //e
		     {
			   Delay(d);
		     }
		  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		  GPIO_ResetBits(GPIOA, GPIO_Pin_2);
		  GPIO_SetBits(GPIOA, GPIO_Pin_3);//f
		  break;
	  }
}



int main(void)
{
  init_all();
  while (1) {
	  avto_svetofor();
  }
}


/*
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "misc.h"


int tiktak =0;
int r=0;
int g=10;
int pg=4;
int pgm=5;
int d=6000000;

void Delay(u32 ticks)
{
  while(ticks != 0) ticks--;
}


void SetSysClockTo72(void)
{
	ErrorStatus HSEStartUpStatus;
    RCC_DeInit();
    RCC_HSEConfig( RCC_HSE_ON);
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    if (HSEStartUpStatus == SUCCESS)
    {
        RCC_HCLKConfig( RCC_SYSCLK_Div1);
        RCC_PCLK2Config( RCC_HCLK_Div1);
        RCC_PCLK1Config( RCC_HCLK_Div2);
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        RCC_PLLCmd( ENABLE);
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){}
        RCC_SYSCLKConfig( RCC_SYSCLKSource_PLLCLK);
        while (RCC_GetSYSCLKSource() != 0x08){}
    }
    else{while (1){}}
}


void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		Delay(500000);
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1) {

        tiktak=1;

		}
		EXTI_ClearITPendingBit(EXTI_Line0);
}
}



int main(void)
{
  SetSysClockTo72();

  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);


	GPIO_InitTypeDef gpio_cfg;
	GPIO_StructInit(&gpio_cfg);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpio_cfg.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio_cfg.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOB, &gpio_cfg);


	GPIO_InitTypeDef GPIO_InitStruct;
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStruct);


  while (1) {
	  switch(tiktak){
	  case 0:
		   GPIO_SetBits(GPIOA, GPIO_Pin_1); //1
		   if(r==1){
			   for(int i=1; i<=20; i++)
			     {
				   Delay(d);
			     }
		           r=0;
		   		}
	  break;
	  case 1:
		  r=1;
		   for(int i=1; i<=10; i++) //2
		     {
			   Delay(d);
		     }
		  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	  	  GPIO_SetBits(GPIOA, GPIO_Pin_2);
		   for(int i=1; i<=pg; i++) //3
		     {
			   Delay(d);
		     }
		   for(int i=1; i<=pgm; i++) //4
		     {
		  	   GPIO_ResetBits(GPIOA, GPIO_Pin_2);
			   Delay(d/2);
		  	   GPIO_SetBits(GPIOA, GPIO_Pin_2);
			   Delay(d/2);
		     }
  		  GPIO_ResetBits(GPIOA, GPIO_Pin_2); //5
  		  GPIO_SetBits(GPIOA, GPIO_Pin_1);
  		  tiktak=0;
  		  break;

	  }

  }
}
*/
