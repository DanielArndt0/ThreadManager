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
    public:
      void operator+=(T data) { _add_(data); }
      T &operator[](unsigned long pos) { return __vector__[pos]; }

    private:
      unsigned long __vector_size__;
      unsigned long __data_amount__;
      T *__vector__;

    private:
      inline void _init_()
      {
        __data_amount__ = 0x00;
        __vector_size__ = 0x01;
        __vector__ = nullptr;
      }

    private:
      void _alloc_() { __vector__ = new T[__vector_size__]; }

      void _relocation_copy_(T *temp)
      {
        for (unsigned long i = 0; i < __vector_size__; i++)
          temp[i] = __vector__[i];
        delete[] __vector__;
        __vector__ = temp;
      }

      void _realloc_up_()
      {
        T *temp = new T[__vector_size__ + 0x01];
        _relocation_copy_(temp);
        __vector_size__ += 0x01;
        __data_amount__ += 0x01;
      }

      void _realloc_down_()
      {
        T *temp = new T[__vector_size__ - 0x01];
        _relocation_copy_(temp);
        if (__vector_size__ > 0x00)
          __vector_size__ -= 0x01;
        if (__data_amount__ > 0x00)
          __data_amount__ -= 0x01;
      }

      void _shift_vector_(unsigned long cursor)
      {
        for (register unsigned long i = cursor; i < __data_amount__; i++)
          __vector__[i] = __vector__[i + 1];
      }

      T _get_(unsigned long pos) { return __vector__[pos]; }

      void _set_(T data, unsigned long pos)
      {
        if (pos < __vector_size__)
          __vector__[pos] = data;
      }

      void _add_(T data)
      {
        if (__vector__)
        {
          __vector__[__data_amount__] = data;
          _realloc_up_();
        }
      }

      void _remove_(unsigned long pos)
      {
        if (__vector__ && pos < __vector_size__)
        {
          _shift_vector_(pos);
          _realloc_down_();
        }
      }

      void _reset_()
      {
        if (__vector__)
        {
          __data_amount__ = 0x00;
          __vector_size__ = 0x01;
          delete[] __vector__;
          _alloc_();
        }
      }

    public:
      Vector()
      {
        _init_();
        _alloc_();
      }

      Vector(Vector &cpy)
      { /* Desenvolver */
      }

      ~Vector()
      {
        if (__vector__)
          delete[] __vector__;
      }

    public:
      /**
       * @return Returns the number of bytes allocated in the vector.
       */
      size_t Bytes() const { return sizeof(T) * __vector_size__; }

      /**
       * @return Returns the amount of data stored in the vector.
       */
      unsigned long Size() const { return __data_amount__; }

      /**
       * @brief Check if the vector is empty.
       *
       * @return Returns true if empty. Otherwise, it will return false.
       */
      bool Empty() const { return __data_amount__ < 0x01 ? true : false; }

      /**
       * @brief Returns the data stored in the vector position.
       *
       * @param pos Position in vector.
       */
      T Get(unsigned long pos) const { _get_(pos); }

      /**
       * @brief Set the data to an existing vector position.
       *
       * @param data Given to be written.
       *
       * @param pos Position in vector.
       */
      void Set(T data, unsigned long pos) { _set_(data, pos); }

      /**
       * @brief Add data to the last position of the vector.
       *
       * @param data Given to be written.
       */
      void Add(T data) { _add_(data); }

      /**
       * @brief Removes the data in the first position of the vector.
       */
      void RemoveFirst() { _remove_(0); }

      /**
       * @brief Removes the data in the last position of the vector.
       */
      void RemoveLast() { _remove_(__vector_size__ - 1); }

      /**
       * @brief Remove data at vector position.
       *
       * @param pos Position in vector.
       */
      void Remove(unsigned long pos) { _remove_(pos); }

      /**
       * @brief Resets the vector, removing all data.
       */
      void Reset() { _reset_(); }
    };
  }
}