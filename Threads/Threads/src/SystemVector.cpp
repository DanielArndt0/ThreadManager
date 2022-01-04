#include "SystemVector.h"

/*
void System::Data::Vector::_init_()
{
  __data_amount__ = 0x00;
  __vector_size__ = 0x01;
  __vector__ = nullptr;
}

void System::Data::Vector::_realloc_up_()
{
  if ((__vector__ = (T *)realloc(__vector__, __vector_size__ + 0x01)) == NULL)
    return;
  memset(&__vector__[__vector_size__], 0x00, 0x01);
  __vector_size__ += 0x01;
  __data_amount__ += 0x01;
}

void System::Data::Vector::_realloc_down_()
{

  if ((__vector__ = (T *)realloc(__vector__, __vector_size__ - 0x01)) == NULL)
    return;
  __vector_size__ -= 0x01;
  __data_amount__ -= 0x01;
}

void System::Data::Vector::_shift_vector_(unsigned int cursor)
{
  for (register unsigned int i = cursor; i < __data_amount__; i++)
    __vector__[i] = __vector__[i + 1];
}

System::Data::Vector::Vector()
{
  _init_();
  __vector__ = (T *)calloc(__vector_size__, sizeof(T));
}

System::Data::Vector::~Vector()
{
  if (__vector__)
    free(__vector__);
}

unsigned int System::Data::Vector::Capacity() const { return __vector_size__; }

unsigned int System::Data::Vector::Size() const { return __data_amount__; }

T System::Data::Vector::Get(unsigned int pos) const { return __vector__[pos]; }

void System::Data::Vector::Add(T data)
{
  if (__vector__)
  {
    __vector__[__data_amount__] = data;
    _realloc_up_();
  }
}

void System::Data::Vector::Remove(unsigned int pos)
{
  if (__vector__ && pos < __vector_size__)
  {
    _shift_vector_(pos);
    _realloc_down_();
  }
}

void System::Data::Vector::Empty()
{
}
*/