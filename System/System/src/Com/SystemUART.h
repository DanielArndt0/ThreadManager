#pragma once

#include <string.h>
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Macros/SystemMacros.h"
#include "DataTypes/SystemTypes.h"

#define __BUFFER_SIZE__ 64

namespace System
{
  namespace Com
  {
    class UART
    {
    private:
      static unsigned int __uart_status__;
      UART *__buff__;

    public:
      static System::Data::Vector<char> __stack__;

    protected:
      UART *__uart_send__(unsigned char data);
      UART *__uart_send__(const char *data);
      static unsigned char __uart_receive__(void);

    public:
      void Begin(unsigned int baudRate);
      unsigned char Available();
      unsigned long bufferLength();
      void Flush(void);
      static void BufferManager();

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
      char operator>>(char &data);
    };
  }
}
