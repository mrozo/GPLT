#include <Libraries/Portx/Portx.h>

volatile struct PORTX_t PORTX; 

void InitPortx(void) {

  PORTA.OUTSET    =  PIN3_bm | PIN4_bm;
  PORTA.DIRSET    =  PIN3_bm | PIN4_bm;
  PORTE.OUTSET    =  PIN3_bm | PIN6_bm | PIN7_bm;
  PORTE.DIRSET    =  PIN3_bm | PIN6_bm | PIN7_bm;

  PORTC.DIRSET    =  PIN4_bm | PIN5_bm | PIN7_bm;
  PORTC.DIRCLR    =  PIN6_bm;
  PORTC.OUTCLR    =  PIN7_bm | PIN6_bm | PIN5_bm | PIN4_bm;
  PORTC.REMAP      =  PORT_SPI_bm;
  SPIC.CTRL      =  SPI_ENABLE_bm|
              SPI_MASTER_bm|
              SPI_MODE_3_gc|

              SPI_PRESCALER_DIV128_gc;

  #if PORTX_AUTOREFRESH

    SPIC.INTCTRL  =  SPI_INTLVL_LO_gc;
    PMIC.CTRL       =   PMIC_HILVLEN_bm|
              PMIC_MEDLVLEN_bm|
              PMIC_LOLVLEN_bm;
    sei();
    SPIC.DATA    =  0;
  #else
    PortxRefresh();
  #endif


}

#if PORTX_AUTOREFRESH == 0
void PortxRefresh(void) {
  PORTE.OUTCLR  =  PIN6_bm;


  PORTX.OUT     |=  PORTX.OUTSET;
  PORTX.OUT     &=  ~PORTX.OUTCLR;
  PORTX.OUT     ^=  PORTX.OUTTGL;
  PORTX.OUTSET  =  0;
  PORTX.OUTCLR  =  0;
  PORTX.OUTTGL  =  0;

  SPIC.DATA  =  PORTX.OUT;
  while(SPIC.STATUS == 0);
  PORTX.IN = SPIC.DATA;
  for(uint8_t i = 255; i; i--);
  PORTE.OUTSET  =  PIN6_bm;
}
#endif

ISR(SPIC_INT_vect) {
  PORTE.OUTSET  =  PIN6_bm;
  PORTX.OUT     |=  PORTX.OUTSET;
  PORTX.OUT     &=  ~PORTX.OUTCLR;
  PORTX.OUT     ^=  PORTX.OUTTGL;
  PORTX.OUTSET  =  0;
  PORTX.OUTCLR  =  0;
  PORTX.OUTTGL  =  0;
  PORTE.OUTCLR  =  PIN6_bm;
  PORTX.IN    =  SPIC.DATA;
  SPIC.DATA    =  PORTX.OUT;
}
