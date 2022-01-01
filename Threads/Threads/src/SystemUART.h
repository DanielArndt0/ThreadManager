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
    unsigned int __uart_status__;
    UART *__buff__;

  protected:
    UART *__uart_send__(unsigned char data);
    UART *__uart_send__(const char *data);
    unsigned char __uart_receive__(void);

  public:
    void Begin(unsigned int baudRate);
    void Flush(void);
    friend UART &operator<<(UART &buff, const char *data);
    friend UART &operator>>(UART &buff, unsigned char data);
  };
}
