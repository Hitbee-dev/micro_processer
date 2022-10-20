#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define	RS_Pin	0x01	// H: 데이터	L: 명령
#define	RW_Pin	0x02	// H: 읽기	L: 쓰기
#define	E_Pin	0x04	// H: Enable

void lcd_write_instruc (unsigned char instruc){
	_delay_ms(2);
	PORTD=PORTD & (~(RS_Pin));      	// 데이터가 아닌 명령을 줌
	PORTD=PORTD & (~(RW_Pin));      	// 쓰기 권한 설정
	PORTD=PORTD & (~(E_Pin));       	// Enable을 0으로 설정
	PORTE=instruc;                  	// 데이터 버스에 명령을 입력
	PORTD=PORTD | (E_Pin);            	// Enable을 1으로 설정
	PORTD=PORTD & (~(E_Pin));       	// Enable을 1 -> 0으로 다시 생성하면서 하강에지 생성
}

void lcd_init (void){
	_delay_ms(2);
	DDRD=0xFF;
	DDRE=0xFF;
	lcd_write_instruc(0x06);        	// 커서 위치 지정
	lcd_write_instruc(0x0C);        	// 디스플레이 켜짐, 커서 꺼짐
	lcd_write_instruc(0x38);        	// 8비트 데이터 버스에, 2라인 디스플레이 설정
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
	PORTD=PORTD | (RS_Pin);        		// 명령이 아닌 데이터를 줌
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