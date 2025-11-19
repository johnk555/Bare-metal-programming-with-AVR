#define F_CPU 16000000UL
#include "inc/blinking.h"
#include "inc/keyboard.h"
#include "src/lcd.c"
#include "inc/ROT.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "src/DHT22.c"
#include "src/ADC.c"
#include "inc/USART.h"
#define CDRC 0b00000001

void PWM0_init() {                       // Initialize PWM0

	DDRB |= (1 << PB7);                  // PWM PB7
	TCCR0A |= (3 << WGM00);              // FPWM
	TCCR0A |= (2 << COM0A0);             // Clear OC0A on Compare Match (3->Set)
	TCCR0B |= (5 << CS00);               // clk/1024
}

int main(void) {

	DDRA = 0b00001111;     				//Port A upper inputs, lower outputs
	PORTA = 0b11111111;    				//Enable pull up on inputs, send 1 to outputs

	InitLCD();
	WrIn(0b00101100);                	// 001, 4 bit, 2 lines 2x16, 5x11 dots, xx
	WrIn(0b00001111);                	// 00001, Display on, cursor on, blinking on
	WrIn(0b00000110);                	// 000001, Cursor increase, display not shift
	WrIn(CDRC);                      	// Clear display, reset cursor (2ms delay)
	_delay_ms (2);

	sei();                                    // Enable all Interrupts
	InitROT();
	PWM0_init();

	i1 = 0;

	USART_Init(103);                          // System Clock 16MHz: 103->9600


	while(1) {
		Keyb();           				//Check keyboard
		OCR0A = i1;      				// Set PWM duty cycle

		DHT22();
		printData();

		SeCu (0x40);
		_delay_ms (5);

		InitADC();
		GetADC();

		USART_Transmit ('5');
	}
}
