#pragma once

namespace System
{
  namespace Data
  {
    template <typename T>
    class LIFO
    {
    public:
      void operator=(LIFO &cpy) { _copy_constructor_(cpy); }
      void operator=(LIFO &&move) { _move_constructor_(move); }
      void operator+=(T data) { _push_(data); }
      T &operator[](unsigned long pos) { return __data_struct__[pos]; }

    private:
      T *__data_struct__;
      unsigned long __buffer_size__;
      unsigned long __data_amount__;

    private:
      inline void _init_()
      {
        __data_amount__ = 0x00;
        __buffer_size__ = 0x01;
        __data_struct__ = nullptr;
      }

    private:
      void _alloc_() { __data_struct__ = new T[__buffer_size__]; }

      void _copy_constructor_(LIFO &cpy)
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

      void _move_constructor_(LIFO &&move)
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

      void _push_(T data)
      {
        if (__data_struct__)
        {
          __data_struct__[__data_amount__] = data;
          _realloc_up_();
        }
      }

      T _get_(unsigned long pos) const { return __data_struct__[pos]; }

      void _pop_()
      {
        if (__data_struct__)
        {
          _shift_vector_(__data_amount__ - 0x01);
          _realloc_down_();
        }
      }

      void _swap_(LIFO<T> &swap)
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
      LIFO()
      {
        _init_();
        _alloc_();
      }

      LIFO(LIFO &cpy)
      {
        _init_();
        *this = cpy;
      }

      LIFO(LIFO &&move)
      {
        _init_();
        *this = move;
      }

      ~LIFO()
      {
        if (__data_struct__)
          delete[] __data_struct__;
      }

    public:
      /**
       * @return Returns the number of bytes allocated on the stack.
       */
      size_t Bytes() const { return sizeof(T) * __buffer_size__; }

      /**
       * @brief Returns an amount of data added to the stack.
       */
      unsigned long Size() const { return __data_amount__; }

      /**
       * @brief Check if the stack is empty.
       *
       * @return Returns true if empty. Otherwise, it will return false.
       */
      bool Empty() const { return __data_amount__ < 0x01 ? true : false; }

      /**
       * @return Returns the first stack data.
       */
      T First() const { return _get_(0); }

      /**
       * @return Returns the last stack data.
       */
      T Last() const { return _get_(__data_amount__ - 0x01); }

      /**
       * @param pos Stack position.
       *
       * @return Returns data at the given stack position.
       */
      T At(unsigned long pos) const { return _get_(pos); }

      /**
       * @brief Insert data into stack.
       *
       * @param data Data to be entered.
       */
      void Push(T data) { _push_(data); }

      /**
       * @brief Remove the last data from the stack.
       */
      void Pop() { _pop_(); }

      /**
       * @brief Swap contents.
       */
      void Swap(LIFO<T> &swap) { _swap_(swap); }

      /**
       * @brief Resets the stack, removing all data.
       */
      void Reset() { _reset_(); }
    };
  }
}
