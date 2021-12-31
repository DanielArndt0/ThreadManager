#include "TIMER0.h"

unsigned char subSystem::Timer0::__status__ = FALSE;

void subSystem::Timer0::Enable()
{
  writeRegister(SREG, SREG_I, FALSE);
  writeRegister(TIMSK0, TOIE0, TRUE);
  TCCR0B = 0x03;
  TCNT0 = 0x06;
  writeRegister(SREG, SREG_I, TRUE);
  __status__ = TRUE;
}

void subSystem::Timer0::Disable()
{
  writeRegister(SREG, SREG_I, FALSE);
  writeRegister(TIMSK0, TOIE0, FALSE);
  writeRegister(SREG, SREG_I, TRUE);
  __status__ = FALSE;
}

void subSystem::Timer0::Reset() { TCNT0 = 0x06; }

unsigned char subSystem::Timer0::Status() { return __status__; }