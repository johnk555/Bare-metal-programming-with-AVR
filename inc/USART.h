#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char trdata;
unsigned char rvdata;

void USART_Init(unsigned int baud) {           			 // Initialization routine (USART0, RX->PE0, TX->PE1)

	UBRR0H = (unsigned char)(baud>>8);        			 // Set baud rate

	UBRR0L = (unsigned char)baud;

	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);     	 // Enable receiver, transmiter, receiver complete
                                                 	 	 // interrupt
	//UCSR0C = (1<<URSEL00)|(1<<USBS0)|(3<<UCSZ00); 	 // Set frame format: 2 stop bit, 8 data,
                                                		 // asynchronous operation & no parity
}

void USART_Transmit(unsigned char trnsm) {     // USART Transmit routine

	while (!(UCSR0A & (1<<UDRE0)));           // Wait for empty transmit buffer

	UDR0 = trnsm;                             // Put data into buffer, sends
                                          	  // the data
}

unsigned char USART_Receive(void) {            // USART Receive routine
	while (!(UCSR0A & (1<<RXC0)));            // Wait for unread data in buffer
	return UDR0;                              // Return data to caller
}

ISR(USART0_RX_vect) {                          // Receive Complete Interrupt
	rvdata = USART_Receive();                 // Send received data to variable rvdata
}
