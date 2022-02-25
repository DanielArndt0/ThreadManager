#pragma once

#include <stdlib.h>
#include "Macros/SystemMacros.h"

namespace System
{
  namespace Memory
  {
    class RAM
    {
    public:
      unsigned int freeRAM();
      unsigned int stackPointer();
    };
  }
}