#include "Memory/SystemEEPROM.h"

void System::EEPROM::_init_()
{
  __mem_buff__ = nullptr;
  __str_buff__ = nullptr;
  __eeprom_size__ = SIZE_EEPROM;
}

void System::EEPROM::_eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr)
{
  writeRegister(SREG, SREG_I, FALSE);
  while (check(EECR, EEPE))
    ;
  while (check(SPMCSR, SELFPRGEN))
    ;
  writeRegister(EECR, EEPM1, FALSE);
  writeRegister(EECR, EEPM0, FALSE);
  EEAR = addr;
  if (selectWriteOp)
    EEDR = data;
  writeRegister(EECR, EEMPE, TRUE);
  writeRegister(EECR, EEPE, TRUE);
  writeRegister(SREG, SREG_I, TRUE);
}

void System::EEPROM::_write_string_(const char *data, unsigned int addr)
{
  unsigned char len = (unsigned char)strlen(data);
  for (register unsigned int i = 0; i <= len; i++)
    _eeprom_clear_write_(0x01, data[i], addr + i);
}

char System::EEPROM::_read_(unsigned int addr)
{
  while (check(EECR, EEPE))
    ;
  EEAR = addr;
  writeRegister(EECR, EERE, TRUE);
  return EEDR;
}

const char *System::EEPROM::_read_string_(unsigned int addr)
{
  if (_free_mem_() > 0)
  {
    if (__str_buff__ != nullptr)
    {
      delete[] __str_buff__;
      __str_buff__ = nullptr;
    }
    unsigned int cnt = 0x00;
    do
    {
      cnt++;
    } while (_read_(addr + cnt) != 0x00);

    if (__str_buff__ == nullptr)
      __str_buff__ = new char[cnt];
    else
      return nullptr;

    for (unsigned int i = 0; i <= cnt; i++)
      __str_buff__[i] = _read_(i + addr);
    return __str_buff__;
  }
  return nullptr;
}

unsigned int System::EEPROM::_used_mem_()
{
  unsigned int cnt = 0x00;
  for (unsigned int i = 0x00; i < __eeprom_size__; i++)
    if (_read_(i) != 0x00)
      cnt += 0x01;
  return cnt;
}

char *System::EEPROM::_get_mem_()
{
  if (__mem_buff__ == nullptr)
    __mem_buff__ = new char[__eeprom_size__];
  for (register unsigned int i = 0x00; i < __eeprom_size__; i++)
    __mem_buff__[i] = _read_(i);
  return __mem_buff__;
}

void System::EEPROM::_release_array_()
{
  if (__mem_buff__)
  {
    delete[] __mem_buff__;
    __mem_buff__ = nullptr;
  }
}

unsigned int System::EEPROM::_free_mem_() { return __eeprom_size__ - _used_mem_(); }

System::EEPROM::EEPROM() { _init_(); }

System::EEPROM::~EEPROM()
{
  if (__mem_buff__)
    delete[] __mem_buff__;
  if (__str_buff__)
    delete[] __str_buff__;
}

unsigned int System::EEPROM::Size() { return __eeprom_size__; }

unsigned int System::EEPROM::Used() { return _used_mem_(); }

unsigned int System::EEPROM::Free() { return _free_mem_(); }

void System::EEPROM::Write(unsigned char data, unsigned int addr) { _eeprom_clear_write_(0x01, data, addr); }

void System::EEPROM::Write(const char *data, unsigned int addr) { _write_string_(data, addr); }

char System::EEPROM::Read(unsigned int addr) { return _read_(addr); }

const char *System::EEPROM::ReadString(unsigned int addr) { return _read_string_(addr); }

void System::EEPROM::Clear(unsigned int addr) { _eeprom_clear_write_(0x00, 0x00, addr); }

void System::EEPROM::Clear(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= addr2)
    return;
  for (unsigned int i = addr1; i < addr2; i++)
    _eeprom_clear_write_(0x00, 0x00, i);
}

char *System::EEPROM::Array() { return _get_mem_(); }

void System::EEPROM::FreeArray() { _release_array_(); }