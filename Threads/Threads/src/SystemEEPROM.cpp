#include "SystemEEPROM.h"

char *System::EEPROM::__str_buff__ = NULL;

void System::EEPROM::_eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr)
{
  writeRegister(SREG, SREG_I, FALSE);
  while (check(EECR, EEPE));
  while (check(SPMCSR, SELFPRGEN));
  writeRegister(EECR, EEPM1, FALSE);
  writeRegister(EECR, EEPM0, FALSE);
  EEAR = addr;
  if (selectWriteOp)
    EEDR = data;
  writeRegister(EECR, EEMPE, TRUE);
  writeRegister(EECR, EEPE, TRUE);
  writeRegister(SREG, SREG_I, TRUE);
}

void System::EEPROM::Clear(unsigned int addr) { _eeprom_clear_write_(0x00, addr, 0x00); }

void System::EEPROM::Write(unsigned char data, unsigned int addr) { _eeprom_clear_write_(0x01, addr, data); }

void System::EEPROM::Write(const char *data, unsigned int addr)
{
  unsigned char len = (unsigned char)strlen(data);
  Write(len, addr);
  addr += 1;
  for (register unsigned int i = 0; i < len; i++)
    Write(data[i], addr + i);
  Write((unsigned char)0x00, (addr + len) + 1);
}

unsigned char System::EEPROM::Read(unsigned int addr)
{
  while (check(EECR, EEPE));
  EEAR = addr;
  writeRegister(EECR, EERE, TRUE);
  return EEDR;
}
