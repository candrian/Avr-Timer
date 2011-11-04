/***************************************************************************
 Timer firmware Oct, 2010
 (c) 2010 Andrianakis Charalampos
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include <avr/io.h>
#include <util/delay.h>

/* Segment Table */
char segment[10] = {0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x1F, 0x70, 0x7F, 0x73};

/* Beeping routine */
void beep(int i){
	uint8_t counter;
	for (counter = 1; counter <= i; counter++){
		/*Turn buzzer ON*/
		PORTD |= (1 << 7);
		_delay_ms(500);
		
        /*Turn buzzer OFF*/
		PORTD &= (0 << 7);
		_delay_ms(500);
	}
}

/* The delay is provided by _delay_ms and not by a counter */
void delay_display(void){
	char i,j;
	for(i = 5; i >= 0; i--){
		PORTB = segment[i];
		for(j = 9; j >= 0; j--){
			PORTD = segment[j];
			_delay_ms(1000);
		}   
	}   
}

int  main(void){
	
	/* Set PortB and PortD output for segments */
	PORTB = 0;
	DDRB = 0xFF;
	PORTD = 0; 
	DDRD = 0xFF;

	/* Set PC1 Output */
	PORTC = 0xFF;
	DDRC = 0x02;

	/* Display 00 to 7-segments */
	PORTB = segment[0];
	PORTD = segment[0];
	
	/* Turn relay OFF */
	PORTC &= (0 << 1);


	while(1){
		if ( PINC & 1 ){
			beep(1);
			//Turn relay ON
			PORTC |= (1 << 1);
			
			delay_display();

			//Turn relay OFF
			PORTC &= (0 << 1); 
			beep(3);
		}
	} 
	return 0;
}
