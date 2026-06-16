/*
 * File:   sourcecode.c
 * Author: msona
 *
 * Created on 15 June, 2026, 1:01 PM
 */


#include <xc.h>
#define rs RB0
#define rw RB1
#define en RB2



#define r1 RD0
#define r2 RD1
#define r3 RD2
#define r4 RD3
#define c1 RD4
#define c2 RD5
#define c3 RD6

void delay();
void delay1();
void lcd(unsigned char);
void cmd(unsigned char);
void EEPROM_Write(unsigned char addr,unsigned char data);
unsigned char EEPROM_Read(unsigned char addr);
void Store_Default_Password();
unsigned char CheckPassword(char entered[]);
void main()

{
    unsigned char n[]="enter key:";
    unsigned char j;

    char input[4];
    unsigned char count = 0;
    TRISC=0X00;
    TRISB=0XF0;
    TRISD=0XF0;
    cmd(0x38);
    cmd(0x10);
    cmd(0x0c);
    cmd(0x80);
    if(EEPROM_Read(0x10) != 'K')
{
    Store_Default_Password();
    EEPROM_Write(0x10,'K');
}
    for(j=0;n[j]!='\0';j++)
    {
      lcd(n[j]);  
    }
    cmd(0xc0);
    
    while(1)
    {
        r1=0;
        if(c1==0)
{
    if(count < 4)
    {
        input[count] = '1';
        count++;
        lcd('1');
    }
    delay1();
}
        if(c2==0)
{
    if(count < 4)
    {
        input[count] = '2';
        count++;
        lcd('2');
    }
    delay1();
}
        if(c3==0)
{
    if(count < 4)
    {
        input[count] = '3';
        count++;
        lcd('3');
    }
    delay1();
}
        r1=1;r3=r4=1;r2=0;
        if(c1==0)
{
    if(count < 4)
    {
        input[count] = '4';
        count++;
        lcd('4');
    }
    delay1();
}
        if(c2==0)
{
    if(count < 4)
    {
        input[count] = '5';
        count++;
        lcd('5');
    }
    delay1();
}
        if(c3==0)
{
    if(count < 4)
    {
        input[count] = '6';
        count++;
        lcd('6');
    }
    delay1();
}
        r1=r4=r2=1;r3=0;
        if(c1==0)
{
    if(count < 4)
    {
        input[count] = '7';
        count++;
        lcd('7');
    }
    delay1();
}
        if(c2==0)
{
    if(count < 4)
    {
        input[count] = '8';
        count++;
        lcd('8');
    }
    delay1();
}
        if(c3==0)
{
    if(count < 4)
    {
        input[count] = '9';
        count++;
        lcd('9');
    }
    delay1();
}
        r1=r2=r3=1;r4=0;
        if(c1==0)
{
    if(count < 4)
    {
        input[count] = '*';
        count++;
        lcd('*');
    }
    delay1();
}
        if(c2==0)
{
    if(count < 4)
    {
        input[count] = '0';
        count++;
        lcd('0');
    }
    delay1();
}
        if(c3==0)
{
    if(count < 4)
    {
        input[count] = '#';
        count++;
        lcd('#');
    }
    delay1();
}
        r4=1;
        if(count == 4)
{
    if(CheckPassword(input))
    {
        cmd(0x01);
        cmd(0x80);
        lcd('O'); lcd('P'); lcd('E'); lcd('N');
    }
    else
    {
        cmd(0x01);
        cmd(0x80);
        lcd('W'); lcd('R'); lcd('O'); lcd('N'); lcd('G');
    }

    count = 0;
}
    
    }
    
}

void cmd(unsigned char a)
{
    rs=0;
    PORTC=a;
    rw=0;
    en=1;
    delay();
    en=0;
}

void lcd(unsigned char b)
{
    rs=1;
    PORTC=b;
    rw=0;
    en=1;
    delay();
    en=0;
}
void delay()
{
    unsigned int i;
    for(i=0;i<2000;i++);
}

void delay1()
{
    unsigned int v2;
    for(v2=0;v2<4000;v2++);
}
void EEPROM_Write(unsigned char address,unsigned char data)
{
    EEADR = address;
    EEDATA = data;

    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;

    INTCONbits.GIE = 0;

    EECON2 = 0x55;
    EECON2 = 0xAA;

    EECON1bits.WR = 1;

    while(EECON1bits.WR);

    EECON1bits.WREN = 0;

    INTCONbits.GIE = 1;
}
unsigned char EEPROM_Read(unsigned char address)
{
    EEADR = address;

    EECON1bits.EEPGD = 0;  
    EECON1bits.RD = 1;

    return EEDATA;
}
void Store_Default_Password()
{
    EEPROM_Write(0,'1');
    EEPROM_Write(1,'2');
    EEPROM_Write(2,'3');
    EEPROM_Write(3,'4');
}
unsigned char CheckPassword(char entered[])
{
    unsigned char i;

    for(i=0;i<4;i++)
    {
        if(entered[i] != EEPROM_Read(i))
            return 0;
    }

    return 1;
}
