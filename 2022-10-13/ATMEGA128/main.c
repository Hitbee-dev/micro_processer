#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

int main(){ 
   DDRD = 0xff;
   DDRE = 0xff;
   DDRF = 0xff;
   while (1){
		PORTD = 0x5b;
	    PORTE = 0x66;
	    PORTF = 0x7d;
		//_delay_ms(500);
   }
   return 0;
}