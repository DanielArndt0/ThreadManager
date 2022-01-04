#pragma once

#include <stdlib.h>
#include <string.h>

namespace System
{
  namespace Data
  {
    template <typename T>
    class Vector
    {
    private:
      unsigned int __vector_size__;
      unsigned int __data_amount__;
      T *__vector__;

    private:
      inline void _init_()
      {
        __data_amount__ = 0x00;
        __vector_size__ = 0x01;
        __vector__ = nullptr;
      }

    private:
      void _alloc_()
      {
        __vector__ = (T *)calloc(__vector_size__, sizeof(T));
      }

      void _realloc_up_()
      {
        if ((__vector__ = (T *)realloc(__vector__, __vector_size__ + 0x01)) == NULL)
          return;
        memset(&__vector__[__vector_size__], 0x00, 0x01);
        __vector_size__ += 0x01;
        __data_amount__ += 0x01;
      }
      void _realloc_down_()
      {
        if ((__vector__ = (T *)realloc(__vector__, __vector_size__ - 0x01)) == NULL)
          return;
        __vector_size__ -= 0x01;
        __data_amount__ -= 0x01;
      }
      void _shift_vector_(unsigned int cursor)
      {
        for (register unsigned int i = cursor; i < __data_amount__; i++)
          __vector__[i] = __vector__[i + 1];
      }

    public:
      Vector()
      {
        _init_();
        _alloc_();
      }
      Vector(Vector &cpy) = delete;
      ~Vector()
      {
        if (__vector__)
          free(__vector__);
      }

    public:
      // Get vector capacity
      unsigned int Capacity() const { return __vector_size__; }

      // Get vector size
      unsigned int Size() const { return __data_amount__; }

      // Get data from vector
      T Get(unsigned int pos) const { return __vector__[pos]; }

      // Add data from vector
      void Add(T data)
      {
        if (__vector__)
        {
          __vector__[__data_amount__] = data;
          _realloc_up_();
        }
      }

      // Remove data from vector
      void Remove(unsigned int pos)
      {
        if (__vector__ && pos < __vector_size__)
        {
          _shift_vector_(pos);
          _realloc_down_();
        }
      }

      // Empty vector
      void Empty()
      {
        if (__vector__)
        {
          __vector_size__ = 0x00;
          __data_amount__ = 0x00;
          free(__vector__);
          _alloc_();
        }
      }
    };
  }
}