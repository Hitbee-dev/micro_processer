#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

int main()
 { 
   DDRA=0xff;
   DDRE=0xff;
   while (1){
	   PORTA = 0xff;
	   PORTE = 0x52;
	   }
   return 0;
 }