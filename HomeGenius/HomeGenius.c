/*
 * new.c
 *
 * Created: 09-Jan-20 2:14:34 PM
 *  Author: ahmed
 */
#include "keypad.h"
#include "ADC.h"
#include "eeprom.h"
#include "icu.h"
#include "lcd.h"
#include "timer.h"
#include "avr/interrupt.h"
#include "uart.h"

uint8 str[50];
volatile uint8 uartFlag = 0;
uint8* str1="@TV,ON";
uint8* str2="@TV,OFF";
uint8* str3="@AC,ON";
uint8* str4="@AC,OFF";
uint8 i=0;

void buzzer_on(void)
{
	PORTE|=(1<<7);
	_delay_ms(50);
	PORTE&=~(1<<7);
}

void fireSystem(void)
{
	uint16 var;
	var=ADC_Read(ADC0);
	var/=15;
	if (var>=45)
	{
		Timer0_CTCInit();
		PORTE^=(1<<PE7);
		lcd_DispStrXY(1,15,"FA");
		lcd_DispStrXY(2,13,"T:");
		lCD_DispInt(var);
		_delay_ms(200);
		lcd_DispStrXY(1,15,"  ");
		lcd_DispStrXY(2,13,"    ");
		//lcd_Clear();
	}
	else
	{
		TCCR0=0;
	}

	
}
void uart_test(void)
{
	uartFlag++;
	static uint8 dataStr[10];
	if(g_uartDataReg == '#')
	{
		uint8 i = 0;
		while(dataStr[i+1]==str1[i])
		{
			if(dataStr[6]=='N')
			{
				setBit(PORTA,0);
			}
			i++;
		}
		while(dataStr[i+1]==str2[i])
		{
			if(dataStr[7]=='F')
			{
				clearBit(PORTA,0);
			}
			i++;
		}
		while(dataStr[i+1]==str3[i])
		{
			if(dataStr[6]=='N')
			{
				setBit(PORTA,7);
			}
			i++;
		}
		while(dataStr[i+1]==str4[i])
		{
			if(dataStr[7]=='F')
			{
				clearBit(PORTA,7);
			}
			i++;
		}
		/*if(dataStr[1]=='@' && dataStr[2]=='T' && dataStr[3]=='V' && dataStr[4]==',' && dataStr[5]=='O' && dataStr[6]=='N')
		{
			setBit(PORTA,0);
		}
		else if(dataStr[1]=='@' && dataStr[2]=='T' && dataStr[3]=='V' && dataStr[4]==',' && dataStr[5]=='O' && dataStr[6]=='F'&& dataStr[7]=='F')
		{
			clearBit(PORTA,0);
		}
		else if(dataStr[1]=='@' && dataStr[2]=='A' && dataStr[3]=='C' && dataStr[4]==',' && dataStr[5]=='O' && dataStr[6]=='N')
		{
			setBit(PORTA,7);
		}
		else if(dataStr[1]=='@' && dataStr[2]=='A' && dataStr[3]=='C' && dataStr[4]==',' && dataStr[5]=='O' && dataStr[6]=='F'&& dataStr[7]=='F')
		{
			clearBit(PORTA,7);
		}
		else
		{
			uartFlag = 0 ;
			for(uint8 i = 0 ; i < 10 ;i++)
			{
				dataStr[i] = 0;
			}
		}*/
	}
	else
	{
		lcd_DispChar(g_uartDataReg);
		dataStr[uartFlag] = g_uartDataReg;	
	}
}

volatile uint8 g_pass[4];
void doorAccess(void)
{
	uint8 flag = 0;
	while(flag==0)
	{
		lcd_Clear();
		lcd_DispStrXY(1,4,"Door Access");
		lcd_DispStrXY(2,1,"Pass:");
		uint8 enteredPass[4];
		uint8 i;	
		uint8 enterKey;
		for( i = 0 ; i < 4 ; i++)
		{
			enteredPass[i] = Keypad_getPressedKey();
			_delay_ms(500);
			enteredPass[i] = Keypad_getPressedKey();
			buzzer_on();
			if(enteredPass[i]!=13 && enteredPass[i]!='L' && enteredPass[i]!='C')
			{			
				lCD_DispInt(enteredPass[i]);
				if(g_pass[i] == enteredPass[i])
				{
					flag++;
				}
			}
			else if(enteredPass[i]=='L')
			{
				i=-1;
				lcd_DispStrXY(2,6,"    ");
				lcd_Gotoxy(2,6);
			}
			else if (enteredPass[i]=='C')
			{
				_delay_ms(300);
				return;
			}
			
		}
		
		while(1)
		{			
			enterKey = Keypad_getPressedKey();
			_delay_ms(300);
			enterKey = Keypad_getPressedKey();
			buzzer_on();
			if(enterKey == 13)
			{
				if(flag != 4)
				{
					lcd_Clear();
					lcd_DispStrXY(1,4,"Door Access");
					lcd_DispStrXY(2,1,"Wrong Password");
					_delay_ms(2000);
					flag = 0;
				}
			else
			{
				lcd_Clear();
				lcd_DispStrXY(1,4,"Door Access");
				lcd_DispStrXY(2,1,"Guaranteed");
				_delay_ms(2000);
			}
			break;
		}
		else if (enterKey=='L')
		{
			flag=0;
			break;
		}
		else if (enterKey=='C')
		{
			_delay_ms(300);
			return;
		}
	}
	
		/*open the door*/
		if(flag==4)
		{
		
		DDRE|=(1<<PE3);
		Timer3_PWMInit(187);
		_delay_ms(2000);
		Timer3_PWMInit(250);
		_delay_ms(2000);
		Timer3_PWMInit(124);
		_delay_ms(2000);
		}
	}
}
void changePass(void)
{
	uint8 flag = 0;
	uint8 enteredPass[4];
	uint8 l_pass[4];
	uint8 enterKey;
	uint8 i;
	while(flag==0)
	{
		lcd_Clear();
		lcd_DispStrXY(1,2,"Change Pass");
		lcd_DispStrXY(2,1,"OldPass:");
		
		
			
		for(i = 0 ; i < 4 ; i++)
		{
			enteredPass[i] = Keypad_getPressedKey();
			_delay_ms(500);
			enteredPass[i] = Keypad_getPressedKey();
			buzzer_on();
			if(enteredPass[i]!=13 && enteredPass[i]!='L' && enteredPass[i]!='C')
			{
				lCD_DispInt(enteredPass[i]);
				if(g_pass[i] == enteredPass[i])
				{
					flag++;
				}
			}
			else if(enteredPass[i]=='L')
			{
				i=-1;
				lcd_DispStrXY(2,9,"    ");
				lcd_Gotoxy(2,9);
			}
			else if (enteredPass[i]=='C')
			{
				_delay_ms(300);
				return;
			}
			
		}
		while (1)
		{
			enterKey = Keypad_getPressedKey();
			_delay_ms(300);
			enterKey = Keypad_getPressedKey();
			buzzer_on();
			if(enterKey == 13)
			{
				if(flag != 4)
				{
					lcd_Clear();
					lcd_DispStrXY(1,2,"Change Pass");
					lcd_DispStrXY(2,1,"Wrong Pass");
					_delay_ms(2000);
					flag = 0;
				}
				else
				{
					uint8 flag3=1;
					while(flag3==1)
					{
						
					lcd_Clear();
					lcd_DispStrXY(1,2,"Change Pass");
					lcd_DispStrXY(2,1,"NewPass:");
					for( i = 0 ; i < 4 ; i++)
					{
						l_pass[i] = Keypad_getPressedKey();
						_delay_ms(500);
						l_pass[i] = Keypad_getPressedKey();
						buzzer_on();
						if(l_pass[i]!=13 && l_pass[i]!='L' && l_pass[i]!='C')
						{
							lCD_DispInt(l_pass[i]);
						}
						else if(l_pass[i]=='L')
						{
							i=-1;
							lcd_DispStrXY(2,9,"    ");
							lcd_Gotoxy(2,9);
						}
						else if (l_pass[i]=='C')
						{
							_delay_ms(300);
							return;
						}				
						
					}
					uint8 flag2=1;
				
					while (flag2==1)
					{
						enterKey = Keypad_getPressedKey();
						_delay_ms(300);
						enterKey = Keypad_getPressedKey();
						buzzer_on();
						if (enterKey == 13)
						{
							for(i=0;i<4;i++)
							{
								EEPROM_Write(0x0030+i,l_pass[i]);
								_delay_ms(100);
							}
							lcd_Clear();
							lcd_DispStrXY(1,2,"Change Pass");
							lcd_DispStrXY(2,1,"Success");
							_delay_ms(2000);
							flag2=0;
							flag3=0;
							flag=1;
						}
						else if (enterKey=='L')
						{
							flag2=0;
							flag3=1;
							flag=0;
							break;
						}
						else if (enterKey=='C')
						{
							_delay_ms(300);
							return;
						}
					}
					} 
				
				}
				break;
			}
			else if (enterKey=='L')
			{
				flag=0;
				break;
			}
			else if (enterKey=='C')
			{
				_delay_ms(300);
				return;
			}
		
		}
	}
}


int main()
{
	/*Enable global interrupt */
	sei();
	EEPROM_Init();
	ICU_Init();
	
	uart_setCallback(uart_test);
	UART_Init();
	UART_Receiver_Int_Enable();
	
	DDRA=0x81;
	
	
	_delay_ms(200);
	
	
	ADC_Init();
	
	setCallback(fireSystem);
	Timer2_OVFInit();
	
	
	DDRF|=(1<<PF3);
	PORTF|=(1<<PF3);
	
	
	
	
	



	
	 
	/*Buzzer direction */
	DDRE|=(1<<7);
	/*Led direction */
	DDRB|=(1<<PB4);
	
	/* ADC on */
	
	

/*
	uint16 var;
	var=ADC_Read(ADC0);
	var/=15;
	if (var>=45)
	{
		Timer0_CTCInit();
		lcd_DispStrXY(1,1,"Firing Alarm");
		lcd_DispStrXY(2,1,"Temp is : ");
		lCD_DispInt(var);
		_delay_ms(200);
		lcd_Clear();
	}
	else
	{
		TCCR0=0;
	}
*/


	
	
	
	/*
	for(uint8 i = 0 ; i < 4 ; i++)
	{
		EEPROM_Write(0x0030+i,0);
		_delay_ms(100);
	}
	*/
	/*
	lCD_Init();
	for(uint8 i = 0 ; i < 4 ; i++)
	{
		uint8 temp = EEPROM_Read(0x0030+i);
		lCD_DispInt(temp);
	}
	*/
	
	
	
	for(uint8 i = 0 ; i < 4 ; i++)
	{
		g_pass[i]=EEPROM_Read(0x30+i);
		_delay_ms(100);
	}
	
	
	
	
	DDRD|=(1<<PD5);
	uint16 check_distance;
	while(1)
	{
		PORTD|= (1<<PD5);
		_delay_us(10);
		PORTD&=~(1<<PD5);
		_delay_ms(1000);
		check_distance=((distance/58)+1);
	
		
		while(check_distance <= 40)
		{
			PORTF&=~(1<<PF3);
			_delay_ms(200);
			//Timer1_OVFInit();
			lCD_Init();
			lcd_Clear();
			lcd_DispStrXY(1,4,"HomeGenius");
			lcd_DispStrXY(2,1,"1:DA 2:CP");
			uint8 flag=1;
			while(flag==1)
			{
				lcd_Clear();
				lcd_DispStrXY(1,4,"HomeGenius");
				lcd_DispStrXY(2,1,"1:DA 2:CP");
				flag=0;
				uint8 key = Keypad_getPressedKey();
				buzzer_on();
				switch(key)
				{
					case 1:
					doorAccess();
					break;
					case 2:
					changePass();
					break;
					default:
					lcd_Clear();
					lcd_DispStrXY(1,2,"invalid input");
					lcd_DispStrXY(2,1,"Please try again");
					_delay_ms(2000);
					flag=1;
					break;
				}
			}
		}
	}
}