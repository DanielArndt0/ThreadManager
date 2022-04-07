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
      void twi_begin(unsigned long freq);
      void twi_start(void);
      void twi_restart(void);
      void twi_write(unsigned char byte);
      unsigned char twi_read();
      void twi_stop(void);
      void twi_disable(void);

    public:
      void Begin(unsigned long frequency);
      void Start(void);
      void Restart(void);
      void Write(unsigned char byte);
      unsigned char Read(void);
      void Stop(void);
      void Send(unsigned char data, unsigned char addr);
      unsigned char Receive(unsigned char addr);
      void Disable(void);
    };
  }
}
