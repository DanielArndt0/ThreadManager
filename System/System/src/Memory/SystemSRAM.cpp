#include "Memory/SystemSRAM.h"

extern char *__brkval;

unsigned int System::Memory::RAM::freeRAM()
{
  char v;
  return __brkval ? &v - __brkval : &v - __malloc_heap_start;
}

unsigned int System::Memory::RAM::stackPointer() { return (__IO_ADDR(0x3D) | __IO_ADDR(0x3E) << 0x08); }
