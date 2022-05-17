#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Macros/SystemMacros.h"

namespace CoadjutorSystem
{
  class UART_INT
  {
  public:
    void RxEnable();
    void RxDisable();
    unsigned char RxStatus();
  };
}