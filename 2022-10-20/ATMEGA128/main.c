#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define	RS_Pin	0x01	// H: ������	L: ���
#define	RW_Pin	0x02	// H: �б�	L: ����
#define	E_Pin	0x04	// H: Enable

void lcd_write_instruc (unsigned char instruc){
	_delay_ms(2);
	PORTD=PORTD & (~(RS_Pin));      	// �����Ͱ� �ƴ� ����� ��
	PORTD=PORTD & (~(RW_Pin));      	// ���� ���� ����
	PORTD=PORTD & (~(E_Pin));       	// Enable�� 0���� ����
	PORTE=instruc;                  	// ������ ������ ����� �Է�
	PORTD=PORTD | (E_Pin);            	// Enable�� 1���� ����
	PORTD=PORTD & (~(E_Pin));       	// Enable�� 1 -> 0���� �ٽ� �����ϸ鼭 �ϰ����� ����
}

void lcd_init (void){
	_delay_ms(2);
	DDRD=0xFF;
	DDRE=0xFF;
	lcd_write_instruc(0x06);        	// Ŀ�� ��ġ ����
	lcd_write_instruc(0x0C);        	// ���÷��� ����, Ŀ�� ����
	lcd_write_instruc(0x38);        	// 8��Ʈ ������ ������, 2���� ���÷��� ����
}

void lcd_goto(unsigned char row){
	_delay_ms(2);
	if(row==0)
		lcd_write_instruc(0x80);		//see Figures 4 and 10
	if(row==1)
		lcd_write_instruc(0xC0);		//see Figures 4 and 10
}

void lcd_write_char (unsigned char c){	
	_delay_ms(2);
	PORTD=PORTD | (RS_Pin);        		// ����� �ƴ� �����͸� ��
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

void main(void)
{
	lcd_init();
	lcd_goto(0);
	lcd_write_string("  Hello World  ");
	lcd_goto(1);
	lcd_write_string(" Micro Processer ");
	while (1){
        continue;
    }
}