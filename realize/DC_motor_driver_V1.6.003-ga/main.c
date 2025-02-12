/*
 * LD.c
 *
 * Created: 11.02.2014 17:33:24
 *  Author: Администратор
 */ 

#include "main.h"

//****************************************************************************************
// External Interrupt 0 service routine
//****************************************************************************************
ISR (INT0_vect)
{
	//---------------------------------------------------------------------------------------
	if ((time_diff!=0x00)&&(FLAGS.SETT_WORK_1!=0x00))
	{
		//---------------------------------------------------------------------------------------
		IMP_SEM_CLR_M1
		//---------------------------------------------------------------------------------------
	}
	else
	{
		//---------------------------------------------------------------------------------------
		
		//---------------------------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------------------
	return;
};
//****************************************************************************************
// External Interrupt 1 service routine
//****************************************************************************************
ISR (INT1_vect)
{
	//---------------------------------------------------------------------------------------
	RP++;
	//---------------------------------------------------------------------------------------
	return;
};
//****************************************************************************************
// Timer0 overflow interrupt service routine
//****************************************************************************************
ISR (TIMER0_OVF_vect)
{
	//---------------------------------------------------------------------------------------
	// Reinitialize Timer0 value
	TCNT0=0x06;
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	BUT_Debrief();
	if (FLAGS.SETT_WORK_1==0x00)
	{
		dig_show(0x00);
	}
	else if ((FLAGS.SETT_WORK_1==0x01)&&(RPS == 0))
	{
		dig_show(0x01);
	} 
	else if ((FLAGS.SETT_WORK_1==0x01)&&(FLAGS.POWER_SETT==0x01))
	{
		dig_show(0x02);
		FLAGS.POWER_SETT=0x00;
	}
	else if ((FLAGS.SETT_WORK_1==0x01)&&(FLAGS.POWER_SETT==0x02))
	{
		dig_show(0x03);
		FLAGS.POWER_SETT=0x00;
	}
	else if ((FLAGS.SETT_WORK_1==0x01)&&(FLAGS.POWER_SETT==0x03))
	{
		dig_show(0x04);
		FLAGS.POWER_SETT=0x00;
	}
	else
	{
		dig_show(0x02);
	};
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	return;
};
//****************************************************************************************
// Timer1 overflow interrupt service routine
//****************************************************************************************
ISR (TIMER1_OVF_vect)
{
	//---------------------------------------------------------------------------------------
	// Reinitialize Timer1 value
	TCNT1H=0xC2;
	TCNT1L=0xF7;
	//---------------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------------
	RPS = RP;
	RP = 0;
	//---------------------------------------------------------------------------------------
	func_timer();
	//---------------------------------------------------------------------------------------
	func_timer_2();
	//---------------------------------------------------------------------------------------
	func_reg_power();
	//---------------------------------------------------------------------------------------
	return;
};
//****************************************************************************************
// Timer2 overflow interrupt service routine
//****************************************************************************************
ISR (TIMER2_OVF_vect)
{
	//---------------------------------------------------------------------------------------
	if ((time_diff!=0x00)&&(FLAGS.SETT_WORK_1!=0x00))
	{
		//---------------------------------------------------------------------------------------
		IMP_SEM_SET_M1
		//---------------------------------------------------------------------------------------
	}
	else
	{
		//---------------------------------------------------------------------------------------
		STOP_WORK_1
		//---------------------------------------------------------------------------------------
	};
	//---------------------------------------------------------------------------------------
	return;
};

int main(void)
{
	init_mcu();
	BUT_Init();
	SEG_Init();
	uart_init();
	BUZZ_INIT
	//---------------------------------------------------------------------------------------
	if ( ((((PINA)>>(2))&1)==0x00 )&&( (((PINA)>>(5))&1)==0x00) )
	{
		//---------------------------------------------------------------------------------------
		beep_tone(2000);
		set_max_speed = 255;
		vork_time = 0x0000;
		beep_tone(300);
		//---------------------------------------------------------------------------------------
	} 
	else if ( ((((PINA)>>(2))&1)==0x00 )&&( (((PINA)>>(5))&1)!=0x00) )
	{
		//---------------------------------------------------------------------------------------
		beep_tone(2000);
		set_max_speed = eeprom_read_byte((uint8_t*)(0x00));
		vork_time = 0x0000;
		beep_tone(300);
		//---------------------------------------------------------------------------------------
	}
	else if ( ((((PINA)>>(2))&1)!=0x00 )&&( (((PINA)>>(5))&1)==0x00) )
	{
		//---------------------------------------------------------------------------------------
		beep_tone(2000);
		set_max_speed = 255;
		vork_time = eeprom_read_word((uint16_t*)(0x10));
		beep_tone(300);
		//---------------------------------------------------------------------------------------
	}
	else
	{
		beep_tone(30);
		set_max_speed = eeprom_read_byte((uint8_t*)(0x00));
		vork_time = eeprom_read_word((uint16_t*)(0x10));
		_delay_ms(200);
		beep_tone(30);
	};
	//---------------------------------------------------------------------------------------
	//Global enable interrupts
	sei();
	
    while(1)
    {
		//---------------------------------------------------------------------------------------
		func_meas_vars();
		//---------------------------------------------------------------------------------------
		func_show_vars();
		//---------------------------------------------------------------------------------------
		func_sel_rejim();
		//---------------------------------------------------------------------------------------
		_delay_ms(50);
		//---------------------------------------------------------------------------------------
		/*if (uart_rx_count())
		{
			if (uart_read()==0x55)
			{
				Func_reset();
			}else
			{
			};
		}else
		{
		};
	*/
	};
};