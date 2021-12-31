#pragma once

#include <string.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "SystemMacros.h"
#include "TIMER0.h"

#define __BUFFER_SIZE__ 64

namespace System
{
  class UART
  {
  private:
    static unsigned int __uart_status__;
    static UART *__buff__;

  protected:
    static UART *__uart_send__(unsigned char data);
    static UART *__uart_send__(const char *data);
    static unsigned char __uart_receive__(void);

  public:
    static void Begin(unsigned int baudRate);
    static void Flush(void);
    friend UART &operator<<(UART &buff, const char *data);
    friend UART &operator>>(UART &buff, unsigned char data);
  };
}
