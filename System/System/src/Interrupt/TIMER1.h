#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "CoadjutorSystem/CoadjutorTimers.h"
#include "Macros/SystemMacros.h"

namespace CoadjutorSystem
{
  class Timer1 : public TIMER
  {
  public:
    void Enable() override;
    void Disable() override;
    void Reset() override;
    unsigned char Status() override;
  };
}