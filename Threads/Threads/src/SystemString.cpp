#include "SystemString.h"

SystemData::Convert::Convert(int value)
{
  init();
  __allocated_buffer__ = (char *)calloc(sizeof(char), 0x05);
  __allocated_buffer__[0x00] = (value / E4) + ASCII_ZERO;
  __allocated_buffer__[0x01] = ((value % E4) / E3) + ASCII_ZERO;
  __allocated_buffer__[0x02] = ((value % E3) / E2) + ASCII_ZERO;
  __allocated_buffer__[0x03] = ((value % E2) / E1) + ASCII_ZERO;
  __allocated_buffer__[0x04] = (value / E1) + ASCII_ZERO;
  __allocated_buffer__[0x05] = 0x00;
}

SystemData::Convert::~Convert()
{
  free(__allocated_buffer__);
}

SystemData::Convert &SystemData::Convert::operator=(const char *str)
{

  return *this;
}

void SystemData::Convert::init()
{
  __allocated_buffer__ = NULL;
  len = 0x00;
}
