#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Interrupt/GlobalInterrupts.h"
#include "Macros/SystemMacros.h"
#include "Interrupt/TIMER0.h"
#include "Interrupt/TIMER1.h"


#define RESET 0x00
#define BEGIN 0x01
#define DISABLE 0x02

namespace System
{
  namespace Settings
  {
    class Interrupts
    {
    private:
      static CoadjutorSystem::Timer0 __timer_0__;
      static CoadjutorSystem::Timer1 __timer_1__;

    public:
      static CoadjutorSystem::Timer0 *TIMER0();
      static CoadjutorSystem::Timer1 *TIMER1();
    };
  }
}