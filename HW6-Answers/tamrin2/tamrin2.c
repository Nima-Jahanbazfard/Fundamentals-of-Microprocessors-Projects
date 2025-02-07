#include <mega32.h>
#include <alcd.h>
#include <stdio.h>
int tenth=0, second=0,m=0;
char st[20];
interrupt [TIM0_COMP] void timer0_comp_isr(void)
{ 
tenth++;
    if (tenth==10)
    {second++; tenth=0;m++;
    if(m<=10){
    lcd_clear();
    lcd_puts("Motor is on");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);
    PORTC=PORTC<<1;}
    if(PORTC>0x08){
    PORTC=0x01;}
    if(m>10 & m<=20){
    if(PORTC==0x04){
    PORTC=0x04;}
    if(PORTC==0x01){
    PORTC=0x01;}
    lcd_clear();
    lcd_puts("Motor is off");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);}
    if(m>20 & m<=30){
    PORTC=PORTC<<1;
    lcd_clear();
    lcd_puts("Motor is on");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);}
    if(PORTC>0x08){
    PORTC=0x01;}
    if(m>30 & m<=40){
    if(PORTC==0x04){
    PORTC=0x04;}
    if(PORTC==0x01){
    PORTC=0x01;}
    lcd_clear();
    lcd_puts("Motor is off");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);}
    if(m>40 & m<=50){
    PORTC=PORTC<<1;
    lcd_clear();
    lcd_puts("Motor is on");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);}
    if(PORTC>0x08){
    PORTC=0x01;}
    if(m>50 & m<=60){
    if(PORTC==0x04){
    PORTC=0x04;}
    if(PORTC==0x01){
    PORTC=0x01;}
    lcd_clear();
    lcd_puts("Motor is off");
    lcd_gotoxy(0,1);
    sprintf(st,"second=%d",second);
    lcd_puts(st);}
       if (second==60)
        {second=0;m=0;
        }
    }

}

void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=In Bit2=Out Bit1=Out Bit0=Out 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (0<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=T Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (0<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port B initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB7) | (0<<DDB6) | (0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB7) | (0<<PORTB6) | (0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Port C initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(0<<DDC7) | (0<<DDC6) | (0<<DDC5) | (0<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=0 Bit2=0 Bit1=0 Bit0=1 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (1<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (0<<PORTD4) | (0<<PORTD3) | (0<<PORTD2) | (0<<PORTD1) | (0<<PORTD0);

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 0.977 kHz
// Mode: CTC top=OCR0
// OC0 output: Disconnected
// Timer Period: 99.328 ms
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (1<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x00;
OCR0=0x60;

// Timer(s)/Counter(s) Interrupt(s) initialization
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (1<<OCIE0) | (0<<TOIE0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTA Bit 0
// RD - PORTA Bit 1
// EN - PORTA Bit 2
// D4 - PORTA Bit 4
// D5 - PORTA Bit 5
// D6 - PORTA Bit 6
// D7 - PORTA Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")

while (1)
      {
//      sprintf(st,"%d:%d:%d:%d",hour,minute,second,tenth);
//      lcd_gotoxy(0,1);
//      lcd_clear();
//      lcd_puts(st);

      }
}
