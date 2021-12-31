#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "GlobalInterrupts.h"
#include "SystemMacros.h"
#include "TIMER0.h"
#include "TIMER1.h"


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
      static subSystem::Timer0 __timer_0__;
      static subSystem::Timer1 __timer_1__;

    public:
      static subSystem::Timer0 *TIMER0();
      static subSystem::Timer1 *TIMER1();
    };
  }
}