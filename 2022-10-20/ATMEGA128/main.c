#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define	RS_Pin	0x01
#define	RW_Pin	0x02
#define	E_Pin	0x04

void lcd_write_instruc (unsigned char instruc){
	_delay_ms(2);
	PORTD=PORTD & (~(RS_Pin));      	//it is an instruction rather than data
	PORTD=PORTD & (~(RW_Pin));      	//it is write operation
	PORTD=PORTD & (~(E_Pin));       	//set E to 0 (see Figure 1)
	PORTE=instruc;                  	//put the instruction on the data bus
	PORTD=PORTD | (E_Pin);            	//set E to 1 (see Figure 1)
	PORTD=PORTD & (~(E_Pin));       	// set E to 0 to generate a falling edge
}

void lcd_init (void){
	_delay_ms(2);
	DDRE=0xFF;
	DDRD=0xFF;
	lcd_write_instruc(0x06);        	//Increment mode for the cursor
	lcd_write_instruc(0x0C);        	//The display on, the cursor off
	lcd_write_instruc(0x38);        	//An 8-bit data bus, two-line display
}

void lcd_clear(void){
	_delay_ms(2);
	lcd_write_instruc(0x01);        	//Clear the display
	lcd_write_instruc(0x02);        	//returns the display to its original status if it was shifted.
}

void lcd_write_char (unsigned char c){	
	_delay_ms(2);
	PORTD=PORTD | (RS_Pin);        		//it is data rather than an instruction
	PORTD=PORTD & (~(RW_Pin));
	PORTD=PORTD & (~(E_Pin));
	PORTE=c;
	PORTD=PORTD | (E_Pin);
	PORTD=PORTD & (~(E_Pin));
}

void lcd_write_string(char *s){
	_delay_ms(2);
	while(*s != 0){
		lcd_write_char(*s);
		s++;
	}
}

void lcd_goto(unsigned char column, unsigned char row){
	_delay_ms(2);
	if(row==0)
		lcd_write_instruc(0x80 + column);		//see Figures 4 and 10
	if(row==1)
		lcd_write_instruc(0xC0+ column);		//see Figures 4 and 10
}

void main(void)
{
	lcd_init();
	lcd_clear();
	lcd_goto(0,0);
	lcd_write_string("    All  About   ");
	lcd_goto(0,1);
	lcd_write_string("     Circuits   ");
	while (1){
        continue;
    }
}