﻿#include "KeyBoard.h"


void init_KeyBoard()
{
	GPIO_TypeDef GPIO_InitStructure;


/*******************启动滴答计时器**********************************/

	SysTick->LOAD |= 0x00002328;//9000,相当于1ms定时
	SysTick->CTRL &= 0xfffffffb;//systick定时器配置时钟源 HCLK/8
	SysTick->CTRL |= 0x00000001;//启动滴答计时器，（以未产生SysTick中断的方式）
	
/*************************键盘初始化*****************************/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1; //ÁÐ
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	

}
/****************************滴答计时器定时*********************************************/
u8 time_1ms()
{
	SysTick->VAL = 0x00;      //将滴答计时器清零
	while (SysTick->CTRL != 0x00010001 )
	{

	}
	return KeyScan();
}

/*****************************读取键盘返回button值*********************************************/
u8 KeyScan()
{
	u8 button = 255; //设定一个初值
/****************************拉低KEY5*****************************************/
	GPIO_ResetBits(GPIOE, GPIO_Pin_2);
	GPIO_SetBits(GPIOE, GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5);
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		button = 15;
	}
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
		button = 14;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0)
	{
		button = 13;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
	{
		button = 12;
	}

/****************************拉低KEY6*****************************************/
	GPIO_ResetBits(GPIOE, GPIO_Pin_3);
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_5);
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		button = 11;
	}
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
		button = 10;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0)
	{
		button = 9;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
	{
		button = 8;
	}

/****************************拉低KEY7*****************************************/
	GPIO_ResetBits(GPIOE, GPIO_Pin_4);
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_5);
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		button = 7;
	}
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
		button = 6;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0)
	{
		button = 5;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
	{
		button = 4;
	}

/****************************拉低KEY8*****************************************/
	GPIO_ResetBits(GPIOE, GPIO_Pin_5);
	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1) == 0)
	{
		button = 3;
	}
	if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0) == 0)
	{
		button = 2;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_6) == 0)
	{
		button = 1;
	}
	if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3) == 0)
	{
		button = 0;
	}
	return button;
}

/*******************************键盘消抖**********************************************************/
u8 XiaoDou()
{
	u8 flag = 1;
	u8 KeyValue = time_1ms();
	for (int i = 1; i < 10; i++)
	{
		if (KeyValue != time_1ms())
		{
			flag = 0;
			break;
		}
	}
	if (flag)
	{
		return KeyValue;
	}
	else
	{
		return 255;
	}
}

/*存在的问题 读取函数不知道放在什么位置上比较好  返回值为255时表示未读取到键盘输入*/