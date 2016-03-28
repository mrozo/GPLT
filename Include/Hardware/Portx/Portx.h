#ifndef EXTRINO_PORTX_H_
#define EXTRINO_PORTX_H_

#include <avr/io.h>
#include <avr/interrupt.h>

#define PORTX_AUTOREFRESH		1

struct PORTX_t {
	uint8_t volatile IN;
	uint8_t volatile OUT;
	uint8_t volatile OUTSET;
	uint8_t volatile OUTCLR;
	uint8_t volatile OUTTGL;
};
volatile struct PORTX_t PORTX; 

void InitPortx(void);

#if PORTX_AUTOREFRESH == 0
void PortxRefresh(void);
#endif

#endif /* EXTRINO_PORTX_H_ */
