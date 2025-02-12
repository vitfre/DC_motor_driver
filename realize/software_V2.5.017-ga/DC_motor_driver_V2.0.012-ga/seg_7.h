﻿/*
 * seg_7.h
 *
 * Created: 29.11.2013 20:54:42
 *  Author: Администратор
 */ 

#ifndef SEG_7_H_
#define SEG_7_H_
//---------------------------------------------------------------------------------------
#define com_catode
//#define com_anode
//---------------------------------------------------------------------------------------
#include <avr/io.h>
//---------------------------------------------------------------------------------------
#define MASK_OUT_SEGS 	(1<<_A)|(1<<_B)|(1<<_C)|(1<<_D)|(1<<_E)|(1<<_F)|(1<<_G)|(1<<_DP)
#define MASK_OUT_ROUD 	(1<<_1)|(1<<_2)|(1<<_3)|(1<<_4)
//---------------------------------------------------------------------------------------
//порт, к которому подключены выходы сегментов индикатора
#define PORT_LD			PORTC
#define DDRX_LD 		DDRC
//порт, к которому подключены выходы розрядов индикатора
#define PORT_SG			PORTB
#define DDRX_SG 		DDRB
//---------------------------------------------------------------------------------------
//номера выводов, к которым подключены сегменты индикатора
#define _A 				0
#define _B 				1
#define _C				2
#define _D 				3
#define _E 				4
#define _F 				5
#define _G				6
#define _DP				7
//номера выводов, к которым подключены столбцы индикатора
#define _1 				3
#define _2 				2
#define _3				1
#define _4				0
//---------------------------------------------------------------------------------------
volatile unsigned char dn=0x00;
volatile unsigned int dig_shn=0x0000;
volatile unsigned int led_num=0x1234; //переменная для индикатора
//---------------------------------------------------------------------------------------
#ifdef com_catode
//---------------------------------------------------------------------------------------
//Таблица цифр для семисегментника
//---------------------------------------------------------------------------------------
unsigned char led_table[10]={0b00111111,0b00000110,0b01011011,0b01001111,0b01100110,0b01101101,0b01111101,0b00000111,0b01111111,0b01101111};
unsigned char sig_table[5]={0b00000000,0b01111001,0b01000000,0b00001000,0b00000001};
//---------------------------------------------------------------------------------------
#endif
#ifdef com_anode
//---------------------------------------------------------------------------------------
//Таблица цифр для семисегментника
//---------------------------------------------------------------------------------------
unsigned char led_table[10]={0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000,0b10010000};
unsigned char sig_table[5]={0b11111111,0b00000110,0b10111111,0b11110111,0b11111110};
//---------------------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------------------
/**************************************************************************
*   Function name : SEG_Init
*   Returns :       нет
*   Parameters :    нет
*   Purpose :       инициализация портов ввода/вывода
*                   вызывается обычно в начале main`a
****************************************************************************/
void SEG_Init(void)
{
	//---------------------------------------------------------------------------------------
	PORT_LD |= MASK_OUT_SEGS;
	PORT_SG &=~ MASK_OUT_ROUD;
	DDRX_LD |= MASK_OUT_SEGS;
	DDRX_SG |= MASK_OUT_ROUD;
	//---------------------------------------------------------------------------------------
};
/**************************************************************************
*   Function name : dig_show
*   Returns :       нет
*   Parameters :    нет
*   Purpose :       вывод сегментов на дисплей
****************************************************************************/
void dig_show(unsigned char err)
{ //Здесь отображаем разряды
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	#ifdef com_catode
	PORT_SG&=0xF0; //Не показываем ни чего
	#endif
	//---------------------------------------------------------------------------------------
	#ifdef com_anode
	PORT_SG|=0x0F; //Не показываем ни чего
	#endif
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	if (dn==0)
	{
		//---------------------------------------------------------------------------------------
		dig_shn=led_num;     //Если первый разряд обновляем переменную
		//---------------------------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------------------
	if (dn==3)
	{
		//---------------------------------------------------------------------------------------
		if (err==0x05)
		{
			PORT_LD=led_table[dig_shn%10]; //Извлекаем разряд
		}
		else
		{
			PORT_LD=sig_table[err]; //Извлекаем символ
		};		
		//---------------------------------------------------------------------------------------
	}
	else
	{
		//---------------------------------------------------------------------------------------
		PORT_LD=led_table[dig_shn%10]; //Извлекаем разряд
		//---------------------------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------------------
	dig_shn/=10; //Сдвигаем разряд вправо
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	#ifdef com_catode
	PORT_SG|=(1<<dn); //Показываем разряд
	#endif
	//---------------------------------------------------------------------------------------
	#ifdef com_anode
	PORT_SG&=~(1<<dn); //Показываем разряд
	#endif
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	dn++;
	if (dn>3)
	{
		//---------------------------------------------------------------------------------------
		dn=0;
		//---------------------------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------------------
};
/**************************************************************************
*   Function name : Set_led_num
*   Returns :       нет
*   Parameters :    даные для дисплея
*   Purpose :       записывает в буфер дисплея даные для вывода
****************************************************************************/
void Set_led_num(unsigned int data)
{
	//---------------------------------------------------------------------------------------
	led_num = data;
	//---------------------------------------------------------------------------------------
};
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
#endif /* SEG_7_H_ */