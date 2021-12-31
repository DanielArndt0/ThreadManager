#include "SystemTime.h"

extern unsigned long __system_tick_counter__;

void System::Time::Begin() { System::Settings::Interrupts::TIMER1()->Enable(); }

unsigned long System::Time::Ticks()
{
  writeRegister(SREG, SREG_I, FALSE);
  unsigned long t = __system_tick_counter__;
  writeRegister(SREG, SREG_I, TRUE);
  return t;
}

void System::Time::Pause(unsigned long delay_ms)
{
  if (delay_ms < 1)
    return;
  unsigned long __delay_ms__ = Ticks();
  while (delay_ms > 0 && (Ticks() - __delay_ms__) <= delay_ms);
}
