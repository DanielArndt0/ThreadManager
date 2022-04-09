#pragma once

#include <avr/io.h>
#include "Macros/SystemMacros.h"

#define __TWI_WRITE 0x00
#define __TWI_READ 0x01
#define __TWI_ADDR_MASK 0xFE

namespace System
{
  namespace Com
  {
    class TWI
    {
    private:
      static void twi_begin(unsigned long freq);
      static void twi_start(void);
      static void twi_restart(void);
      static void twi_write(unsigned char byte);
      static unsigned char twi_read();
      static void twi_stop(void);
      static void twi_disable(void);

    public:
      static void Begin(unsigned long frequency);
      static void Start(void);
      static void Restart(void);
      static void Write(unsigned char byte);
      static unsigned char Read(void);
      static void Stop(void);
      static void Send(unsigned char data, unsigned char addr);
      static unsigned char Receive(unsigned char addr);
      static void Disable(void);
    };
  }
}
