#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "CoadjutorSystem/CoadjutorInterrupt.h"
#include "Macros/SystemMacros.h"


namespace System
{
  class Time
  {
  public:
    static void Begin();
    static unsigned long Ticks();
    static void Pause(unsigned long delay_ms);
  };
}
