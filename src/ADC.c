#pragma once
#include <avr/io.h>
#include "../inc/lcd.h"
#include "../inc/ADC.h"

uint8_t AdcOut1;
uint16_t AdcOut1_multiply_100, Adc_result_5V;

void InitADC (void) {

	ADCSRA = ((1<<ADEN) | (7<<ADPS0));   	// ADC Enable, single conversion, 62.5kHz sample

	ADMUX = ((1<<REFS0) | (1<<ADLAR));   	// AVcc(REFS1:0 = 0->AREF, 1->AVCC, 2->VREF=1.1V, 3->VREF=2.56V),
                   	   	   	   	   	        // left adjust result, PF0 (MUX5:0=0 default value)
	DIDR0 |= (1<<0);                     	// Disable Digital Input PF0
}

void GetADC (void) {

	ADCSRA |= (1<<ADSC);                    // Start conversion

	while (!(ADCSRA & (1<<ADIF)));          // Wait for conversion to complete

	AdcOut1 = ADCH;                     // Write data to variable

	char adc[7];
	itoa (AdcOut1, adc, 10);

	if(AdcOut1 >= 100){
		for (uint8_t idht = 0; idht < 3; idht++)
			WrDa(adc[idht]);              // Send ASCII string to LCD
	}
	else if (AdcOut1 >=10){
		WrDa('0');
		for (uint8_t idht = 0; idht < 2; idht++)
					WrDa(adc[idht]);              // Send ASCII string to LCD
	}
	else if (AdcOut1 <10){
		WrDa('0');
		WrDa('0');
		WrDa(adc[0]);
	}

	WrDa(' ');
	WrDa('V');
	WrDa(':');
	WrDa(' ');

	char adc100[7];
	AdcOut1_multiply_100 = AdcOut1*100;
	Adc_result_5V = AdcOut1_multiply_100/51;
	itoa (Adc_result_5V, adc100, 10);

	if(AdcOut1 >= 51){
		WrDa(adc100[0]);
		WrDa('.');
		WrDa(adc100[1]);
		WrDa(adc100[2]);
	}
	else if(AdcOut1 < 51 && AdcOut1 > 5){
		WrDa('0');
		WrDa('.');
		WrDa(adc100[0]);
		WrDa(adc100[1]);
	}
	else {
		WrDa('0');
		WrDa('.');
		WrDa('0');
		WrDa(adc100[0]);
	}
}
