#include "Addons/EEPROMPartition.h"

System::Data::Duet<bool, System::Properties::EEProperties> System::Addon::EEPartition::_its_start_(unsigned int addr, unsigned char *buff)
{
  unsigned int offset_ = 3;
  unsigned int part_addr_ = addr - offset_;
  if (buff[part_addr_] && buff[part_addr_ + 1] && buff[part_addr_ + 2])
  {
    __size__ = buff[part_addr_ + 1] | buff[part_addr_ + 2] << 8;
    __checker__ = buff[(part_addr_ + offset_) + __size__] | buff[(part_addr_ + offset_) + (__size__ + 1)] << 8;
    __firstCheck__ = (buff[part_addr_] + __size__) == __checker__;
    __secondCheck__ = buff[part_addr_] == buff[(part_addr_ + offset_) + (__size__ + 2)];
    if (__firstCheck__ && __secondCheck__)
      return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(true, System::Properties::EEProperties(buff[part_addr_], addr, addr + __size__));
  }
  return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(false, System::Properties::EEProperties(0x00, 0x00, 0x00));
}

System::Data::Duet<bool, System::Properties::EEProperties> System::Addon::EEPartition::_its_between_(unsigned int addr, unsigned char *buff)
{
  System::Data::Duet<bool, System::Properties::EEProperties> _start_;
  System::Data::Duet<bool, System::Properties::EEProperties> _end_;
  for (unsigned int i = 0; i < System::Memory::EEPROM::Size(); i++)
  {
    _start_ = _its_start_(i, buff);
    _end_ = _its_end_(i, buff);
    if (_start_.getFirst())
      if (_start_.getSecond().getStartAddr() < addr && _start_.getSecond().getEndAddr() > addr)
        return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(true, System::Properties::EEProperties(_start_.getSecond().getName(), _start_.getSecond().getStartAddr(), _start_.getSecond().getEndAddr()));
    if (_end_.getFirst())
      if (_end_.getSecond().getStartAddr() < addr && _end_.getSecond().getEndAddr() > addr)
        return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(true, System::Properties::EEProperties(_end_.getSecond().getName(), _end_.getSecond().getStartAddr(), _end_.getSecond().getEndAddr()));
  }
  return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(false, System::Properties::EEProperties(0x00, 0x00, 0x00));
}

System::Data::Duet<bool, System::Properties::EEProperties> System::Addon::EEPartition::_its_end_(unsigned int addr, unsigned char *buff)
{
  if (buff[addr] && buff[addr + 1] && buff[addr + 2])
  {
    __checker__ = buff[addr] | buff[addr + 1] << 8;
    __size__ = buff[(addr - (__checker__ - buff[addr + 2])) - 2] | buff[(addr - (__checker__ - buff[addr + 2])) - 1] << 8;
    __firstCheck__ = (__checker__ - buff[addr + 2]) == __size__;
    __secondCheck__ = buff[addr + 2] == buff[(addr - __size__) - 3];
    if (__firstCheck__ && __secondCheck__)
      return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(true, System::Properties::EEProperties(buff[addr + 2], addr - __size__, addr));
  }
  return System::Data::Duet<bool, System::Properties::EEProperties>::CreateDuet(false, System::Properties::EEProperties(0x00, 0x00, 0x00));
}

void System::Addon::EEPartition::_delete_(unsigned int addr)
{
  System::Properties::EEProperties props = _get_partition_(addr);
  if (props.getSize() > 0)
    System::Memory::EEPROM::Clean(props.getStartAddr() - 3, props.getEndAddr() + 3);
}

bool System::Addon::EEPartition::_create_(char name, unsigned int addr0, unsigned int addr1)
{
  if (!name && addr0 >= addr1 && addr0 < 3 && addr1 > 1020)
    return false;
  unsigned int _diff_ = addr1 - addr0;
  unsigned int _check_digit_ = name + _diff_;
  System::Memory::EEPROM::Write(name, addr0 - 3);
  System::Memory::EEPROM::Write(_diff_, addr0 - 2);
  System::Memory::EEPROM::Write(_check_digit_, addr1);
  System::Memory::EEPROM::Write(name, addr1 + 2);
  for (unsigned int i = addr0; i < addr1; i++)
    System::Memory::EEPROM::Write((unsigned char)0x00, i);
  return true;
}

bool System::Addon::EEPartition::_is_partition_(unsigned int addr)
{
  unsigned char *mem = System::Memory::EEPROM::Array();
  bool is_part = _its_start_(addr, mem).getFirst() || _its_between_(addr, mem).getFirst() || _its_end_(addr, mem).getFirst() ? true : false;
  System::Memory::EEPROM::FreeArray();
  return is_part;
}

System::Properties::EEProperties System::Addon::EEPartition::_get_partition_(unsigned int addr)
{
  unsigned char *mem = System::Memory::EEPROM::Array();
  System::Data::Duet<bool, System::Properties::EEProperties> _start_ = _its_start_(addr, mem);
  System::Data::Duet<bool, System::Properties::EEProperties> _final_ = _its_end_(addr, mem);
  System::Memory::EEPROM::FreeArray();
  return _start_.getFirst() ? _start_.getSecond() : (_final_.getFirst() ? _final_.getSecond() : _final_.getSecond());
}

bool System::Addon::EEPartition::Create(char name, unsigned int addr0, unsigned int addr1) { return _create_(name, addr0, addr1); }

void System::Addon::EEPartition::Delete(unsigned int addr) { return _delete_(addr); }

bool System::Addon::EEPartition::isPartition(unsigned int addr) { return _is_partition_(addr); }

System::Properties::EEProperties System::Addon::EEPartition::Get(unsigned int addr) { return _get_partition_(addr); }
