#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

/*
Project: INT0~3을 이용한 LED On/Off
PORTA - LED 연결
PORTD - 인터럽트 연결
TodoList:	INT0 SW Push: LED all On
			INT1 SW Push: LED all Off
			INT2 SW Push: Even LED all On
			INT3 SW Push: Even LED, Odd LED 0.3초 간격으로 5회 점등
*/

// 인터럽트 서비스 루틴(ISR)
ISR(INT0_vect){
		PORTA = 0xff;		//LED all On
}
ISR(INT1_vect){
		PORTA = 0x00;		//LED all Off
}
ISR(INT2_vect){
		PORTA = 0b10101010;	//Even LED all On
}
ISR(INT3_vect){
	int i;
	for(i = 0; i < 5; i++){
			PORTA = 0b10101010;	//Even LED all On
			_delay_ms(300);
			PORTA = 0b01010101;	//Odd LED all On
			_delay_ms(300);
		}
}
int main(){ 
	DDRA = 0xff;		//PORTA를 출력으로 설정(레지스터 설정)
	EICRA = 0b11111010;	
	/*
	이게 왜 11111010이냐면, 11 11 10 10으로 끊어서 보면,
	순차적으로 11(INT0, 하강엣지), 11(INT1, 하강엣지), 10(INT2, 상승엣지), 10(INT3, 상승엣지)
	이렇게 구성되어 있어서 0b11111010으로 세팅된다.
	*/
	EIMSK = 0b00001111;	//INT0~3까지 사용(레지스터 설정)
	SREG = 0b10000000;	//GLOBAL INTERRUPT ENABLE bit set의 7bit를 1로 바꿔주는 것
   while (1){
		;	//무한 대기
   }
   return 0;
}