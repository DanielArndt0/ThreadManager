#include "Memory/SystemEEPROM.h"
#include "DataTypes/SystemString.h"

unsigned char *System::Memory::EEPROM::__mem_buff__;
char *System::Memory::EEPROM::__str_buff__;
unsigned int System::Memory::EEPROM::__eeprom_size__;

void System::Memory::EEPROM::_init_()
{
  __mem_buff__ = nullptr;
  __str_buff__ = nullptr;
  __eeprom_size__ = __EEPROM_SIZE;
}

void System::Memory::EEPROM::_eeprom_clear_write_(unsigned char selectWriteOp, unsigned char data, unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return;
  __WRITE_REG(SREG, SREG_I, __FALSE);
  while (__CHECK(EECR, EEPE))
    ;
  while (__CHECK(SPMCSR, SELFPRGEN))
    ;
  __WRITE_REG(EECR, EEPM1, __FALSE);
  __WRITE_REG(EECR, EEPM0, __FALSE);
  EEAR = addr;
  if (selectWriteOp)
    EEDR = data;
  __WRITE_REG(EECR, EEMPE, __TRUE);
  __WRITE_REG(EECR, EEPE, __TRUE);
  __WRITE_REG(SREG, SREG_I, __TRUE);
}

template <typename T>

void System::Memory::EEPROM::_convert_write_(T data, unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return;
  for (unsigned int i = 0x00; i < sizeof(data); i++)
    _eeprom_clear_write_(0x01, (data >> (8 * i) & 0xFF), addr + i);
}

void System::Memory::EEPROM::_write_string_(const char *data, unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return;
  unsigned char len = (unsigned char)strlen(data);
  for (register unsigned int i = 0; i <= len; i++)
    _eeprom_clear_write_(0x01, data[i], addr + i);
}

unsigned char System::Memory::EEPROM::_read_(unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return 0x00;
  while (__CHECK(EECR, EEPE))
    ;
  EEAR = addr;
  __WRITE_REG(EECR, EERE, __TRUE);
  return EEDR;
}

template <typename T>
T System::Memory::EEPROM::_convert_read_(T t, unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return t;
  for (unsigned int i = 0x00; i < sizeof(t); i++)
    t |= (T)_read_(addr + i) << (i * 8);
  return t;
}

const char *System::Memory::EEPROM::_read_string_(unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return "";
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

unsigned int System::Memory::EEPROM::_used_mem_(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= __eeprom_size__ && addr2 > __eeprom_size__ && addr1 >= addr2)
    return 0x00;
  unsigned int cnt = 0x00;
  for (unsigned int i = addr1; i < addr2; i++)
    if (_read_(i) != 0x00)
      cnt += 0x01;
  return cnt;
}

unsigned char *System::Memory::EEPROM::_get_mem_(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= addr2 && addr2 > __eeprom_size__)
    return nullptr;
  if (__mem_buff__ == nullptr)
    __mem_buff__ = new unsigned char[__eeprom_size__];
  for (register unsigned int i = addr1; i < addr2; i++)
    __mem_buff__[i] = _read_(i);
  return __mem_buff__;
}

void System::Memory::EEPROM::_release_array_()
{
  if (__mem_buff__)
  {
    delete[] __mem_buff__;
    __mem_buff__ = nullptr;
  }
}

unsigned int System::Memory::EEPROM::_free_mem_(unsigned int addr1, unsigned int addr2) { return __eeprom_size__ - _used_mem_(addr1, addr2); }

System::Memory::EEPROM::EEPROM() { _init_(); }

System::Memory::EEPROM::~EEPROM()
{
  if (__mem_buff__)
    delete[] __mem_buff__;
  if (__str_buff__)
    delete[] __str_buff__;
}

unsigned int System::Memory::EEPROM::Size() { return __eeprom_size__; }

unsigned int System::Memory::EEPROM::Used() { return _used_mem_(0, __eeprom_size__); }

unsigned int System::Memory::EEPROM::Empty() { return _free_mem_(0, __eeprom_size__); }

void System::Memory::EEPROM::Write(char data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(unsigned char data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(int data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(unsigned int data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(long data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(unsigned long data, unsigned int addr) { _convert_write_(data, addr); }

void System::Memory::EEPROM::Write(const char *data, unsigned int addr) { _write_string_(data, addr); }

char System::Memory::EEPROM::ReadChar(unsigned int addr) { return _convert_read_((char)0, addr); }

unsigned char System::Memory::EEPROM::ReadUChar(unsigned int addr) { return _convert_read_((unsigned char)0, addr); }

int System::Memory::EEPROM::ReadInt(unsigned int addr) { return _convert_read_((int)0, addr); }

unsigned int System::Memory::EEPROM::ReadUInt(unsigned int addr) { return _convert_read_((unsigned int)0, addr); }

long System::Memory::EEPROM::ReadLong(unsigned int addr) { return _convert_read_((long)0, addr); }

unsigned long System::Memory::EEPROM::ReadULong(unsigned int addr) { return _convert_read_((unsigned long)0, addr); }

const char *System::Memory::EEPROM::ReadString(unsigned int addr) { return _read_string_(addr); }

void System::Memory::EEPROM::Clean(unsigned int addr)
{
  if (addr >= __EEPROM_SIZE)
    return;
  _eeprom_clear_write_(0x00, 0x00, addr);
}

void System::Memory::EEPROM::Clean(unsigned int addr1, unsigned int addr2)
{
  if (addr1 >= addr2 && addr2 >= __EEPROM_SIZE)
    return;
  for (unsigned int i = addr1; i < addr2; i++)
    _eeprom_clear_write_(0x00, 0x00, i);
}

unsigned char *System::Memory::EEPROM::Array() { return _get_mem_(0, __eeprom_size__); }

void System::Memory::EEPROM::FreeArray() { _release_array_(); }