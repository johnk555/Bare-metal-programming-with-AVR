#pragma once
#ifndef INC_ROT_H_
#define INC_ROT_H_

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

volatile uint8_t i1;           // Has to be "volatile" if other routine than ISR(INTx_vect) affects "reg1bin"

volatile uint8_t lastA = 0;
volatile uint8_t lastB = 0;

/* Rotator Code
		WrIn(CDRC);                      // Clear display, reset cursor (2ms delay)
		_delay_ms (2);

		uint8_t hundreds = 0;
		uint8_t tens = 0;
		uint8_t units = 0;

		while (i1 >= 100) {i1 -= 100;
			hundreds++;}

		while (i1 >= 10) {i1 -= 10;
		    tens++;}

		// Remaining is units
		units = i1;

		// Print digits as ASCII
		WrDa(hundreds + '0');
		WrDa(tens + '0');
		WrDa(units + '0');
*/
/* Rotator Code v2.0 (better)
		WrIn(CDRC);                      // Clear display, reset cursor (2ms delay)
		_delay_ms (2);
		char buf[6];
		itoa(i1, buf, 10); // or just use hundreds/tens/units method
		for(uint8_t i=0; i<3; i++){
			WrDa(buf[i]);
		}*/

void InitROT(void)
{
    // Configure inputs with pull-ups
    DDRE &= ~((1<<4)|(1<<5));   // PE4, PE5 as input
    PORTE |= (1<<4)|(1<<5);     // enable pull-up

    // External interrupts on any edge
    EICRB |= (1<<ISC40) | (1<<ISC41); // INT4 any change
    EICRB |= (1<<ISC50) | (1<<ISC51); // INT5 any change

    // Enable INT4 & INT5
    EIMSK |= (1<<INT4) | (1<<INT5);

    sei(); // enable global interrupts
}

ISR(INT4_vect) {  // Channel A changed
    uint8_t A = bit_is_set(PINE,4);
    uint8_t B = bit_is_set(PINE,5);

    if (A != lastA) {        // only process if A changed
        if (A == B) i1++;    // CW
        else i1--;            // CCW
    }

    lastA = A;
    lastB = B;
}

ISR(INT5_vect) {  // Channel B changed
    uint8_t A = bit_is_set(PINE,4);
    uint8_t B = bit_is_set(PINE,5);

    if (B != lastB) {        // only process if B changed
        if (A != B) i1++;    // CW
        else i1--;            // CCW
    }

    lastA = A;
    lastB = B;
}

#endif /* INC_ROT_H_ */
