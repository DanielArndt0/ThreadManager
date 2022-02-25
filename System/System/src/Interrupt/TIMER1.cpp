#include "Interrupt/TIMER1.h"

unsigned char CoadjutorSystem::Timer1::__status__ = __FALSE;

void CoadjutorSystem::Timer1::Enable()
{
  __WRITE_REG(SREG, SREG_I, __FALSE);
  __WRITE_REG(TIMSK1, TOIE1, __TRUE);
  TCCR1B = 0x01;
  TCNT1L = 0x80;
  TCNT1H = 0xC1;
  __WRITE_REG(SREG, SREG_I, __TRUE);
  __status__ = __TRUE;
}

void CoadjutorSystem::Timer1::Disable()
{
  __WRITE_REG(SREG, SREG_I, __FALSE);
  __WRITE_REG(TIMSK1, TOIE1, __FALSE);
  __WRITE_REG(SREG, SREG_I, __TRUE);
  __status__ = __FALSE;
}

void CoadjutorSystem::Timer1::Reset()
{
  TCNT1L = 0x80;
  TCNT1H = 0xC1;
}

unsigned char &CoadjutorSystem::Timer1::Status() { return __status__; }