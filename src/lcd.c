#include "../inc/lcd.h"

void InitLCD (void) {                     // Start up, initialization rutine

	lcdddr |= ~(1<<0);                   // PORTx1:7 outputs (LCD)

	lcdport &= (1<<0);
	_delay_ms (20);                      // Power on delay 20ms

	out = 0b00110000;

	lcdport = (lcdport | out);
	_delay_us (100);

	lcdport = (lcdport | En);            // Init
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_ms (5);

	lcdport = (lcdport | En);            // Init
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (200);

	lcdport = (lcdport | En);            // Init
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_ms (5);

	lcdport &= (1<<0);

	out = 0b00100000;                    // 4 bit interface

	lcdport = (lcdport | out);
	_delay_us (100);

	lcdport = (lcdport | En);
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (50);
}

void WrIn (uint8_t tmp) {           // Write Instruction routine

	lcdport &= (1<<0);

	out = tmp & 0b11110000;       // Upper

	lcdport = (lcdport | out);
	_delay_us (100);

	lcdport = (lcdport | En);
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (100);

	lcdport &= (1<<0);

	out = tmp << 4;               // Lower

	lcdport = (lcdport | out);
	_delay_us (100);

	lcdport = (lcdport | En);
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (50);
}

void WrDa (uint8_t tmp) {          		 // Write Data routine

	lcdport &= (1<<0);

	out = tmp & 0b11110000;              // Upper

	lcdport = (lcdport | out | Da);
	_delay_us (100);

	lcdport = (lcdport | En);
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (100);

	lcdport &= (1<<0);

	out = tmp << 4;                      // Lower

	lcdport = (lcdport | out | Da);
	_delay_us (100);

	lcdport = (lcdport | En);
	_delay_us (100);

	lcdport = (lcdport & ~En);
	_delay_us (50);
}

void SeCu (uint8_t addr) {                // Send cursor to a specific address
	WrIn (0b10000000 | addr);
}

