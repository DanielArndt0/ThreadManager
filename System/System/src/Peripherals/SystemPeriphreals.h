#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Macros/SystemMacros.h"

#define OUTPUT 0x01
#define INPUT 0x00

namespace System
{
  class GPIO
  {
  private:
    static unsigned char __aref__;

  private:
    static unsigned char _port_selector_(volatile unsigned char **reg, unsigned char pin, unsigned char value);
    static unsigned char _port_selector_(volatile unsigned char **reg, unsigned char pin);
    static unsigned int _analog_read_(unsigned char pin);

  public:
    static unsigned int analogReadBits(unsigned char pin);
    static float analogReadVolts(unsigned char pin);
    static void pinConfig(unsigned char pin, unsigned char mode);
    static void pinWrite(unsigned char pin, unsigned char value);
    static unsigned char pinRead(unsigned char pin);
  };
}