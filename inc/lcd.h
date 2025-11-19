#pragma once
#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <avr/io.h>
#include <util/delay.h>

#define lcdport PORTL                    // Define LCD PORT

#define lcdddr DDRL                      // Define LCD DDR

#define En 0b00001000                    // E signal

#define Da 0b00000100             		// RS, data signal (0 for instruction)

uint8_t out;

/* 	Examples for LCD
* 	#define CDRC 0b00000001           // Clear Display and Reset Cursor (2ms delay)
  	WrIn(0b00101100);                // 001, 4 bit, 2 lines 2x16, 5x11 dots, xx
	WrIn(0b00001111);                // 00001, Display on, cursor on, blinking on
	WrIn(0b00000110);                // 000001, Cursor increase, display not shift
	WrIn(CDRC);                      // Clear display, reset cursor (2ms delay)
	_delay_ms (2);

	char first_name[4] = "Gian";
	char last_name[4] = "Kare";

	for(uint8_t i=0; i<4; i++){
		WrDa(first_name[i]);
	}

	SeCu (0x40);

	for(uint8_t i=0; i<4; i++) {
		WrDa(last_name[i]);
	}

	_delay_ms(5000);
*/

void InitLCD (void);                     // Start up, initialization rutine

void WrIn (uint8_t tmp);	             // Write Instruction routine

void WrDa (uint8_t tmp);         		 // Write Data routine

void SeCu (uint8_t addr);                // Send cursor to a specific address

#endif /* INC_LCD_H_ */
