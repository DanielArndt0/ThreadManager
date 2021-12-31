#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "TimersInterrupts.h"
#include "SystemMacros.h"

namespace subSystem
{
  class Timer0 : public TIMER
  {
  private:
    static unsigned char __status__;

  public:
    void Enable() override;
    void Disable() override;
    void Reset() override;
    unsigned char Status() override;
  };
}