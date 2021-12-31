#pragma once
#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "SystemMacros.h"

#define ASCII_ZERO 48

namespace SystemData
{
  class Convert
  {
  private:
    char *__allocated_buffer__;
    unsigned int len;

  private:
    inline void init();

  public:
    Convert(int value);
    ~Convert();
    Convert &operator=(const char *cstr);
  };
}
