#include "Memory/SystemEEPROM.h"
#include "Com/SystemUART.h"
#include "DataTypes/SystemString.h"

extern System::UART Serial;

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

template <typename T>

void System::EEPROM::_convert_write_(T data, unsigned int addr)
{
  for (unsigned int i = 0x00; i < sizeof(data); i++)
  {
    _eeprom_clear_write_(0x01, (data >> (8 * i) & 0xFF), addr + i);
    Serial << "i: " << i << " | Data: " << System::Data::String((data >> (8 * i) & 0xFF), HEX) << " | Addr: " << addr + i << " | Addr Data:" << System::Data::String(data, HEX) << endl;
  } 
}

void System::EEPROM::_write_string_(const char *data, unsigned int addr)
{
  unsigned char len = (unsigned char)strlen(data);
  for (register unsigned int i = 0; i <= len; i++)
    _eeprom_clear_write_(0x01, data[i], addr + i);
}

unsigned char System::EEPROM::_read_(unsigned int addr)
{
  while (check(EECR, EEPE))
    ;
  EEAR = addr;
  writeRegister(EECR, EERE, TRUE);
  return EEDR;
}

template <typename T>
T System::EEPROM::_convert_read_(T t, unsigned int addr)
{
  for (unsigned int i = 0x00; i < sizeof(t); i++)
  {
    t |= (T)_read_(addr + i) << (i * 8);
    Serial << "i: " << i << " | Data: " << System::Data::String(t, HEX) << " | Addr: " << addr + i << " | Addr Data:" << System::Data::String(_read_(addr + i), HEX) << endl;
  }
  return t;
}

const char *System::EEPROM::_read_string_(unsigned int addr)
{
  if (_free_mem_(0, __eeprom_size__) > 0)
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

unsigned int System::EEPROM::_used_mem_(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= __eeprom_size__ && addr2 > __eeprom_size__ && addr1 >= addr2)
    return 0x00;
  unsigned int cnt = 0x00;
  for (unsigned int i = addr1; i < addr2; i++)
    if (_read_(i) != 0x00)
      cnt += 0x01;
  return cnt;
}

unsigned char *System::EEPROM::_get_mem_()
{
  if (__mem_buff__ == nullptr)
    __mem_buff__ = new unsigned char[__eeprom_size__];
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

unsigned int System::EEPROM::_free_mem_(unsigned int addr1, unsigned int addr2) { return __eeprom_size__ - _used_mem_(addr1, addr2); }

System::EEPROM::EEPROM() { _init_(); }

System::EEPROM::~EEPROM()
{
  if (__mem_buff__)
    delete[] __mem_buff__;
  if (__str_buff__)
    delete[] __str_buff__;
}

unsigned int System::EEPROM::Size() { return __eeprom_size__; }

unsigned int System::EEPROM::Used() { return _used_mem_(0, __eeprom_size__); }

unsigned int System::EEPROM::Empty() { return _free_mem_(0, __eeprom_size__); }

void System::EEPROM::Write(char data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(unsigned char data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(int data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(unsigned int data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(long data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(unsigned long data, unsigned int addr) { _convert_write_(data, addr); }

void System::EEPROM::Write(const char *data, unsigned int addr) { _write_string_(data, addr); }

char System::EEPROM::ReadChar(unsigned int addr) { return _convert_read_((char)0, addr); }

unsigned char System::EEPROM::ReadUChar(unsigned int addr) { return _convert_read_((unsigned char)0, addr); }

int System::EEPROM::ReadInt(unsigned int addr) { return _convert_read_((int)0, addr); }

unsigned int System::EEPROM::ReadUInt(unsigned int addr) { return _convert_read_((unsigned int)0, addr); }

long System::EEPROM::ReadLong(unsigned int addr) { return _convert_read_((long)0, addr); }

unsigned long System::EEPROM::ReadULong(unsigned int addr) { return _convert_read_((unsigned long)0, addr); }

const char *System::EEPROM::ReadString(unsigned int addr) { return _read_string_(addr); }

void System::EEPROM::Clear(unsigned int addr) { _eeprom_clear_write_(0x00, 0x00, addr); }

void System::EEPROM::Clear(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= addr2)
    return;
  for (unsigned int i = addr1; i < addr2; i++)
    _eeprom_clear_write_(0x00, 0x00, i);
}

unsigned char *System::EEPROM::Array() { return _get_mem_(); }

void System::EEPROM::FreeArray() { _release_array_(); }