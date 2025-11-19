/*
 * keyboard.h
 *
 *  Created on: Oct 22, 2025
 *      Author: user
 */

#pragma once
#ifndef INC_KEYBOARD_H_
#define INC_KEYBOARD_H_

#include <avr/io.h>
#include <util/delay.h>
#include "../inc/lcd.h"

uint8_t line;
uint8_t data;
uint8_t count=0;

void Keyb (void) {                //Keyboard rutine
	if(count == 16)
		SeCu (0x40);
	if(count == 32){
		WrIn(0b00000001);
		count = 0;
	}
	line =1;
	for (uint8_t i1 = 0; i1 < 4; i1++){
		PORTA = ~line;
		line = line << 1;
		_delay_ms(1);
		while (PINA < 0b11101111){
			_delay_ms(5);
			switch (PINA) {
				case 0b11101110:                //Button 1 pressed
					data = 1;
					WrDa('1');
					count++;
					while (PINA == 0b11101110);     //Button still pressed
					break;

				case 0b11101101:                //Button 4 pressed
					data = 4;
					WrDa('4');
					count++;
					while (PINA == 0b11101101);
					break;

				case 0b11101011:                //Button 7 pressed
					data = 7;
					WrDa('7');
					count++;
					while (PINA == 0b11101011);
					break;

				case 0b11100111:                //Button * pressed
					data = 14;
					WrDa('*');
					count++;
					while (PINA == 0b11100111);
					break;

				case 0b11011110:                //Button 2 pressed
					data = 2;
					WrDa('2');
					count++;
					while (PINA == 0b11011110);
					break;

				case 0b11011101:                //Button 5 pressed
					data = 5;
					WrDa('5');
					count++;
					while (PINA == 0b11011101);
					break;

				case 0b11011011:                //Button 8 pressed
					data = 8;
					WrDa('8');
					count++;
					while (PINA == 0b11011011);
					break;

				case 0b11010111:                //Button 0 pressed
					data = 0;
					WrDa('0');
					count++;
					while (PINA == 0b11010111);
					break;

				case 0b10111110:                //Button 3 pressed
					data = 3;
					WrDa('3');
					count++;
					while (PINA == 0b10111110);
					break;

				case 0b10111101:                //Button 6 pressed
					data = 6;
					WrDa('6');
					count++;
					while (PINA == 0b10111101);
					break;

				case 0b10111011:                //Button 9 pressed
					data = 9;
					WrDa('9');
					count++;
					while (PINA == 0b10111011);
					break;

				case 0b10110111:                //Button # pressed
					data = 15;
					WrDa('#');
					count++;
					while (PINA == 0b10110111);
					break;

				case 0b01111110:                //Button A pressed
					data = 10;
					WrDa('A');
					count++;
					while (PINA == 0b01111110);
					break;

				case 0b01111101:                //Button B pressed
					data = 11;
					WrDa('B');
					count++;
					while (PINA == 0b01111101);
					break;

				case 0b01111011:                //Button C pressed
					data = 12;
					WrDa('C');
					count++;
					while (PINA == 0b01111011);
					break;

				case 0b01110111:                //Button D pressed
					data = 13;
					WrDa('D');
					count++;
					while (PINA == 0b01110111);
					break;
			}
		}
	}
}

#endif /* INC_KEYBOARD_H_ */
