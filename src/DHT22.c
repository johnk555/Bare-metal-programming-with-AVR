#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/DHT22.h"

uint8_t dhtreg[5];
uint8_t rdf;
int16_t hum;
int16_t tmp;

/* Your code here */

void DHT22(){

	_delay_ms(1000);                           // 1s for DHT start up

	DDRC |= (1<<0);                            // MCU Port turns to output

	PORTC &= ~(1<<0);                          // MCU Request (PORT = 0)

	_delay_ms(18);

	PORTC |= (1<<0);                           // MCU Request (PORT = 1)

	_delay_us(40);

	DDRC &= ~(1<<0);                           // MCU Port turns to input

	PORTC |= (1<<0);                           // Enable pull up resistor

	_delay_us(20);

	while (!(bit_is_set(PINC,0)));             // DHT Response PC0 = 0

	_delay_us(100);                            // DHT Response PC0 = 1

	for (uint8_t rgi = 0; rgi < 5; rgi++) {      // Start reading DHT packet
		for (uint8_t bti = 0; bti < 8; bti++) {   // Start reading byte
			while (!(bit_is_set(PINC,0)));       // Wait while PC0 = 0
			_delay_us(40);
			dhtreg[rgi] = dhtreg[rgi]<<1;        // Shift register
			if (bit_is_set(PINC,0)) {              // Read 1
				dhtreg[rgi] |= (1<<0);            // Load value 1
				rdf = 0;                          // Reset fault counter
				while (bit_is_set(PINC,0)) {        // Wait while PC0 = 1
					rdf++;                          // Increase fault counter
					_delay_us(5);
					if (rdf > 100) {                  // If time out
						break;                       // Break previous “while”
					}
				}
			}
		}
	}
	hum = 0;                                 // DHT22
	hum = dhtreg[0]<<8;                      // DHT22
	hum |= dhtreg[1];                        // DHT22

	tmp = 0;                                 // DHT22
	tmp = dhtreg[2]<<8;                      // DHT22
	tmp |= dhtreg[3];                        // DHT22
}

void printData(){

	char humasc[6];
	char tmpasc[6];



	SeCu (0x00);
	_delay_ms (5);       // Send cursor to 1st line 1st rank

	WrDa('H');                        // Display H
	WrDa('=');                        // Display =
	itoa (hum, humasc, 10);           // Binary integer to decimal ASCII string
	if (hum<10)                       // For values lower than 1.0
		WrDa ('0');                       // Display 0 before decimal point

	for (uint8_t idht = 0; idht < ((unsigned)strlen(humasc)-1); idht++)
		WrDa (humasc[idht]);              // Send ASCII string to LCD

	WrDa('.');                        // Display . for decimal point
	WrDa (humasc[((unsigned)strlen(humasc)-1)]);    // Display last digit (decimal)
	WrDa('%');                        // Display
	/*WrDa('R');                        // Display R
	WrDa('H');                         // Display H

	for (uint8_t idht = (unsigned)strlen(humasc); idht < 6; idht++)
		WrDa(' ');                        // Complete with blanks

	SeCu (0x40);*/
	WrDa(' ');
	_delay_ms (5);       // Send cursor to 2nd line 1st rank

	WrDa('T');                        // Display T
	WrDa('=');                        // Display =

	if (bit_is_set(dhtreg[2],7)) {      // If negative temperature
		WrDa('-');                      // Display -
		tmp &= ~(1<<15);                // Clear negative bit
	}

	itoa (tmp, tmpasc, 10);           // Binary integer to decimal ASCII string

	if (tmp<10)                       // For values lower than 1.0
		WrDa ('0');                     // Display 0

	for (uint8_t idht = 0; idht < ((unsigned)strlen(tmpasc)-1); idht++)
		WrDa (tmpasc[idht]);              // Send ASCII string to LCD

	WrDa('.');                        // Display .
	WrDa (tmpasc[((unsigned)strlen(tmpasc)-1)]);    // Display last digit (decimal)
	WrDa(223);                        // Display degree symbol o
	WrDa('C');                        // Display C

	for (uint8_t idht = (unsigned)strlen(tmpasc); idht < 6; idht++)
		WrDa(' ');                        // Complete with blanks
}
