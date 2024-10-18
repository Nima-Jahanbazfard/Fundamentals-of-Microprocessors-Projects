#include <mega32.h>
#include <alcd.h>
#include <delay.h>
#include <stdio.h>
int d;
float w=0;
char st[40];
interrupt [EXT_INT0] void ext_int0_isr(void){
      
      if(PORTC==0x01){
      PORTC=0x01;}
      if(PORTC==0x02){
      PORTC=0x02;}
      if(PORTC==0x04){
      PORTC=0x04;}
      if(PORTC==0x08){
      PORTC=0x08;}
      if(PORTC==0x10){
      PORTC=0x10;}
      while(1){ 
      if(PIND.0==0){
      while(PIND.0==0){;} 
      d+=20;}
      if(PIND.1==0){
      while(PIND.1==0){;}
      d-=20;}
      if(PORTC==0x01){
      PORTC=0x10;}
      lcd_gotoxy(0,1);
      lcd_puts("turn left");
      PORTC=PORTC>>1;
      delay_ms(d); 
      w=(15000/d);
      sprintf(st, "w=%0.1fn/m d=%i", w , d);
      lcd_clear();
      lcd_puts(st);
      if(PIND.3==0){
      while(PIND.3==0){;}
      break;
      }
      } 
      }
      
// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
      if(PORTC==0x01){
      PORTC=0x01;}
      if(PORTC==0x02){
      PORTC=0x02;}
      if(PORTC==0x04){
      PORTC=0x04;}
      if(PORTC==0x08){
      PORTC=0x08;}
      if(PORTC==0x10){
      PORTC=0x10;}
      while(1){
       if(PIND.0==0){
      while(PIND.0==0){;} 
      d+=20;}
      if(PIND.1==0){
      while(PIND.1==0){;}
      d-=20;}
      if(PORTC==0x10){
      PORTC=0x01;}
      lcd_gotoxy(0,1);
      lcd_puts("turn right");
      delay_ms(d);
      PORTC=PORTC<<1; 
      w=(15000/d); 
      sprintf(st, "w=%0.1fn/m d=%i",w ,d);
      lcd_clear();
      lcd_puts(st);
      if(PIND.2==0){
      while(PIND.2==0){;}
      break;
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
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=P Bit2=P Bit1=P Bit0=P 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (1<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: Off
GICR|=(1<<INT1) | (1<<INT0) | (0<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (0<<INTF2);

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
d=200;
while (1)
      {
      
      }
      }
