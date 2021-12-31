#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "SystemMacros.h"

namespace System
{
  class EEPROM
  {
  private:
    static char *__str_buff__;

  private:
    static void _eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr);

  public:
    static void Write(unsigned char data, unsigned int addr);
    static void Write(const char *data, unsigned int addr);
    static unsigned char Read(unsigned int addr);
    static void Clear(unsigned int addr);
  };
}