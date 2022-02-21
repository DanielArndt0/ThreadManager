#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Macros/SystemMacros.h"

namespace CoadjutorSystem
{
  class TIMER
  {
  public:
    virtual void Enable() = 0;
    virtual void Disable() = 0;
    virtual void Reset() = 0;
    virtual unsigned char Status() = 0;
  };
}
