#pragma once

#include <string.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "SystemMacros.h"
#include "SystemString.h"

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
    
    // Send
    UART &operator<<(const char *data);
    UART &operator<<(const System::Data::String &data);
    UART &operator<<(char command);
    UART &operator<<(int data);
    UART &operator<<(unsigned int data);
    UART &operator<<(long data);
    UART &operator<<(unsigned long data);
    UART &operator<<(float data);
    UART &operator<<(double data);

    // Receive
    UART &operator>>(unsigned char &data);
  };
}
