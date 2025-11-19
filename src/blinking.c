#include "../inc/blinking.h"

void blinking(){
	_delay_ms(100);

	DDRA = 0b00000000;

	PORTA = 0b11111111;  //Enable pull up on inputs, send 1 to outputs

	DDRB = 0b11111111;

	PORTB = 0b11111111;

	while(1){
		PORTB = ~PORTB;

		_delay_ms(500);

		while(PINA == 0b11111110){
			PORTB = 0b11111111;
		}
	}
}
