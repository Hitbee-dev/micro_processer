#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

/*
Project: INT0~3�� �̿��� LED On/Off
PORTA - LED ����
PORTD - ���ͷ�Ʈ ����
TodoList:	INT0 SW Push: LED all On
			INT1 SW Push: LED all Off
			INT2 SW Push: Even LED all On
			INT3 SW Push: Even LED, Odd LED 0.3�� �������� 5ȸ ����
*/

// ���ͷ�Ʈ ���� ��ƾ(ISR)
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
	DDRA = 0xff;		//PORTA�� ������� ����(�������� ����)
	EICRA = 0b11111010;	
	/*
	�̰� �� 11111010�̳ĸ�, 11 11 10 10���� ��� ����,
	���������� 11(INT0, �ϰ�����), 11(INT1, �ϰ�����), 10(INT2, ��¿���), 10(INT3, ��¿���)
	�̷��� �����Ǿ� �־ 0b11111010���� ���õȴ�.
	*/
	EIMSK = 0b00001111;	//INT0~3���� ���(�������� ����)
	SREG = 0b10000000;	//GLOBAL INTERRUPT ENABLE bit set�� 7bit�� 1�� �ٲ��ִ� ��
   while (1){
		;	//���� ���
   }
   return 0;
}