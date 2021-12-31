#include "TIMER1.h"

unsigned char subSystem::Timer1::__status__ = FALSE;

void subSystem::Timer1::Enable()
{
  writeRegister(SREG, SREG_I, FALSE);
  writeRegister(TIMSK1, TOIE1, TRUE);
  TCCR1B = 0x01;
  TCNT1L = 0x80;
  TCNT1H = 0xC1;
  writeRegister(SREG, SREG_I, TRUE);
  __status__ = TRUE;
}

void subSystem::Timer1::Disable()
{
  writeRegister(SREG, SREG_I, FALSE);
  writeRegister(TIMSK1, TOIE1, FALSE);
  writeRegister(SREG, SREG_I, TRUE);
  __status__ = FALSE;
}

void subSystem::Timer1::Reset()
{
  TCNT1L = 0x80;
  TCNT1H = 0xC1;
}

unsigned char subSystem::Timer1::Status() { return __status__; }