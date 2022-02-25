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
      void operator=(Vector &cpy) { _copy_constructor_(cpy); }
      void operator=(Vector &&move) { _move_constructor_(move); }
      void operator+=(T data) { _add_(data); }
      T &operator[](unsigned long pos) { return __data_struct__[pos]; }

    private:
      unsigned long __buffer_size__;
      unsigned long __data_amount__;
      T *__data_struct__;

    private:
      inline void _init_()
      {
        __data_amount__ = 0x00;
        __buffer_size__ = 0x01;
        __data_struct__ = nullptr;
      }

    private:
      void _alloc_() { __data_struct__ = new T[__buffer_size__]; }

      void _copy_constructor_(Vector &cpy)
      {
        this->__buffer_size__ = cpy.__buffer_size__;
        this->__data_amount__ = cpy.__data_amount__;
        if (this->__data_struct__)
        {
          delete[] this->__data_struct__;
          this->__data_struct__ = nullptr;
        }
        this->__data_struct__ = new T[this->__buffer_size__];
        for (unsigned int i = 0; i < __data_amount__; i++)
          this->__data_struct__[i] = cpy.__data_struct__[i];
      }

      void _move_constructor_(Vector &&move)
      {
        if (this->__data_struct__)
          delete[] this->__data_struct__;
        this->__buffer_size__ = move.__buffer_size__;
        this->__data_amount__ = move.__data_amount__;
        this->__data_struct__ = move.__data_struct__;
        move.__buffer_size__ = 0x00;
        move.__data_amount__ = 0x00;
        move.__data_struct__ = nullptr;
      }

      void _relocation_copy_(T *temp)
      {
        for (unsigned long i = 0; i < __buffer_size__; i++)
          temp[i] = __data_struct__[i];
        delete[] __data_struct__;
        __data_struct__ = temp;
      }

      void _realloc_up_()
      {
        T *temp = new T[__buffer_size__ + 0x01];
        _relocation_copy_(temp);
        __buffer_size__ += 0x01;
        __data_amount__ += 0x01;
      }

      void _realloc_down_()
      {
        T *temp = new T[__buffer_size__ - 0x01];
        _relocation_copy_(temp);
        if (__buffer_size__ > 0x00)
          __buffer_size__ -= 0x01;
        if (__data_amount__ > 0x00)
          __data_amount__ -= 0x01;
      }

      void _shift_vector_(unsigned long cursor)
      {
        for (register unsigned long i = cursor; i < __data_amount__; i++)
          __data_struct__[i] = __data_struct__[i + 1];
      }

      T _get_(unsigned long pos) const { return __data_struct__[pos]; }

      void _set_(T data, unsigned long pos)
      {
        if (pos < __buffer_size__)
          __data_struct__[pos] = data;
      }

      void _add_(T data)
      {
        if (__data_struct__)
        {
          __data_struct__[__data_amount__] = data;
          _realloc_up_();
        }
      }

      void _remove_(unsigned long pos)
      {
        if (__data_struct__ && pos < __buffer_size__)
        {
          _shift_vector_(pos);
          _realloc_down_();
        }
      }

      void _swap_(Vector<T> &swap)
      {
        T *temp = this->__data_struct__;
        unsigned long vs_temp = this->__buffer_size__;
        unsigned long da_temp = this->__data_amount__;
        this->__data_struct__ = swap.__data_struct__;
        this->__buffer_size__ = swap.__buffer_size__;
        this->__data_amount__ = swap.__data_amount__;
        swap.__data_struct__ = temp;
        swap.__buffer_size__ = vs_temp;
        swap.__data_amount__ = da_temp;
      }

      void _reset_()
      {
        if (__data_struct__)
        {
          __data_amount__ = 0x00;
          __buffer_size__ = 0x01;
          delete[] __data_struct__;
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
      {
        _init_();
        *this = cpy;
      }

      Vector(Vector &&move)
      {
        _init_();
        *this = move;
      }

      ~Vector()
      {
        if (__data_struct__)
          delete[] __data_struct__;
      }

    public:
      /**
       * @return Returns the number of bytes allocated in the vector.
       */
      size_t Bytes() const { return sizeof(T) * __buffer_size__; }

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
       * @return Returns the first element.
       */
      T First() const { return _get_(0); }

      /**
       * @return Returns the last element.
       */
      T Last() const { return _get_(__data_amount__ - 0x01); }

      /**
       * @brief Returns the data stored in the vector position.
       *
       * @param pos Position in vector.
       */
      T At(unsigned long pos) const { return _get_(pos); }

      /**
       * @brief Set the data to an existing vector position.
       *
       * @param data Given to be written.
       *
       * @param pos Position in vector.
       */
      void Insert(T data, unsigned long pos) { _set_(data, pos); }

      /**
       * @brief Add data to the last position of the vector.
       *
       * @param data Given to be written.
       */
      void Push(T data) { _add_(data); }

      /**
       * @brief Removes the data in the last position of the vector.
       */
      void Pop() { _remove_(__buffer_size__ - 1); }

      /**
       * @brief Remove data at vector position.
       *
       * @param pos Position in vector.
       */
      void Pop(unsigned long pos) { _remove_(pos); }

      /**
       * @brief Swap contents.
       */
      void Swap(Vector<T> &swap) { _swap_(swap); }

      /**
       * @brief Resets the vector, removing all data.
       */
      void Reset() { _reset_(); }
    };
  }
}