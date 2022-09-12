/*
 * 30-simple game.c
 *
 * Created: 8/20/2022 3:07:00 AM
 * Author : Islam Ashraf Mustafa
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "keypad_driver.h"
#include "timer.h"


int count=0;
unsigned char value=NOTPRESSED;
int main(void)
{
   LCD_vInit();
   keypad_vInit();
   timer_CTC_init_interrupt();
   LCD_vSend_string("3+?=8");
   while(1)
   {
   do{
	     if (count>=1000)
	     {
		     LCD_clearscreen();
		     LCD_movecursor(2,1);
		     LCD_vSend_string("time over");
		     _delay_ms(1000);
		     break;
		 }
	   value=keypad_u8check_press();
	 }while(value==NOTPRESSED);
	  _delay_ms(300);
	   if (value=='5')
	   {
		   LCD_clearscreen();
		   LCD_vSend_string("=");
		   LCD_vSend_char(value);
		   _delay_ms(500);
			LCD_movecursor(2,1);
		   LCD_vSend_string("Right answer");
		   _delay_ms(2000);
	   }
	   else if ((value!='5')&&(count<1000))
	   {
		    LCD_clearscreen();
			LCD_movecursor(2,1);
			LCD_vSend_string("wrong answer");
			 _delay_ms(1000);
			 LCD_clearscreen();
			  LCD_vSend_string("3+?=8");
	   }
	   
}
   }

ISR (TIMER0_COMP_vect)
{
	count++;
}