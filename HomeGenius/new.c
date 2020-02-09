/*
 * new.c
 *
 * Created: 09-Jan-20 2:14:34 PM
 *  Author: ahmed
 */
/*#include "new.h" 
volatile uint8 g_pass[4];
void doorAccess(void)
{
	lcd_Clear();
	lcd_DispStrXY(1,8,"Door Access");
	lcd_DispStrXY(2,1,"Pass:");
	uint8 enteredPass[4];
	uint8 flag = 0;
	uint8 enterKey;
	while(1)
	{
		for(uint8 i = 0 ; i < 4 ; i++)
		{
			enteredPass[i] = Keypad_getPressedKey();
			if(g_pass[i] == enteredPass[i])
			{
				flag++;
			}
		}
		enterKey = Keypad_getPressedKey();
		if(enterKey == 13)
		{
			if(flag != 4)
			{
				lcd_Clear();
				lcd_DispStrXY(1,8,"Door Access");
				lcd_DispStrXY(2,1,"Wrong Password");
				_delay_ms(1000);
				flag = 0;
			}
			else
			{
				lcd_Clear();
				lcd_DispStrXY(1,8,"Door Access");
				lcd_DispStrXY(2,1,"Guranted");
				_delay_ms(1000);
				break;
			}
		}
	}
	/*open the door*/
	/*DDRE|=(1<<PE3);
	Timer3_PWMInit(4);
	_delay_ms(2000);
	Timer3_PWMInit(6);
	_delay_ms(2000);
	Timer3_PWMInit(8);
	_delay_ms(2000);
}
void changePass(void)
{
	lcd_Clear();
	lcd_DispStrXY(1,8,"Change Password");
	lcd_DispStrXY(2,1,"OldPass:");
	uint8 enteredPass[4];
	uint8 flag = 0;
	uint8 enterKey;
	while(1)
	{
		for(uint8 i = 0 ; i < 4 ; i++)
		{
			enteredPass[i] = Keypad_getPressedKey();
			if(g_pass[i] == enteredPass[i])
			{
				flag++;
			}
		}
		enterKey = Keypad_getPressedKey();
		if(enterKey == 13)
		{
			if(flag != 4)
			{
				lcd_Clear();
				lcd_DispStrXY(1,8,"Change Password");
				lcd_DispStrXY(2,1,"Wrong Password");
				_delay_ms(1000);
				flag = 0;
			}
			else
			{
				lcd_Clear();
				lcd_DispStrXY(1,8,"Change Password");
				lcd_DispStrXY(2,1,"NewPass:");
				for(uint8 i = 0 ; i < 4 ; i++)
				{
					g_pass[i] = Keypad_getPressedKey();
					EEPROM_Write(0x0030+i,g_pass[i]);
				}
				lcd_DispStrXY(1,8,"Change Password");
				lcd_DispStrXY(2,1,"Success");
				_delay_ms(1000);
				break;
			}
		}
	}
}


int main()
{
	while(1)
	{
		while(distance <=40)
		{
			lCD_Init();
			lcd_Clear();
			lcd_DispStrXY(1,8,"HomeGenius");
			lcd_DispStrXY(2,1,"1:DA 2:CP");
			uint8 flag=1;
			while(flag==1)
			{
				lcd_Clear();
				lcd_DispStrXY(1,8,"HomeGenius");
				lcd_DispStrXY(2,1,"1:DA 2:CP");
				flag=0;
				uint8 key = Keypad_getPressedKey();
				unt8 enter = Keypad_getPressedKey();
				if(enter == 13)
				{
					switch(key)
					{
						case 1:
						doorAcess();
						break;
						case 2:
						changePass();
						break;
						default:
						lcd_Clear();
						lcd_DispStrXY(1,8,"invalid input");
						lcd_DispStrXY(2,1,"Please try again");
						flag=1;
						break;
					}
				}
				else
				{
					lcd_Clear();
					lcd_DispStrXY(1,8,"invalid input");
					lcd_DispStrXY(2,1,"Please try again");
				}
			}
		}
	}
}*/