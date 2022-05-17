#pragma once

#include <stdlib.h>
#include <string.h>

namespace System
{
  namespace Data
  {
#pragma once

#define offset 1

    template <typename T>
    class Vector
    {
    public:
      Vector &operator=(Vector &cpy) { return _copy_(cpy); }

      Vector &operator=(Vector &&move) { return _move_(move); }

      /**
       * @brief Add data to the last position of the vector.
       *
       * @param data Given to be written.
       */
      void operator+=(T data) { _add_(data); }

      /**
       * @brief Returns the data stored in the vector position.
       *
       * @param pos Position in vector.
       */
      T &operator[](unsigned long pos) { return m_data_struct[pos]; }

    private:
      unsigned long m_buffer_size;
      unsigned long m_data_amount;
      unsigned long m_buff_preinit;
      T *m_data_struct;

    private:
      void _alloc_() { m_data_struct = new T[m_buffer_size]; }

      Vector &_copy_(Vector &cpy)
      {
        this->m_buffer_size = cpy.m_buffer_size;
        this->m_data_amount = cpy.m_data_amount;
        this->m_buff_preinit = cpy.m_buff_preinit;
        if (this->m_data_struct)
        {
          delete[] this->m_data_struct;
          this->m_data_struct = nullptr;
        }
        this->m_data_struct = new T[this->m_buffer_size];
        for (unsigned int i = 0; i < m_data_amount; i++)
          this->m_data_struct[i] = cpy.m_data_struct[i];
        return *this;
      }

      Vector &_move_(Vector &&move)
      {
        if (this->m_data_struct)
          delete[] this->m_data_struct;
        this->m_buffer_size = move.m_buffer_size;
        this->m_data_amount = move.m_data_amount;
        this->m_data_struct = move.m_data_struct;
        this->m_buff_preinit = move.m_buff_preinit;
        move.m_buffer_size = 0x00;
        move.m_data_amount = 0x00;
        move.m_buff_preinit = 0x00;
        move.m_data_struct = nullptr;
        return *this;
      }

      void _relocation_copy_(T *temp)
      {
        for (unsigned long i = 0; i < m_buffer_size; i++)
          temp[i] = m_data_struct[i];
        delete[] m_data_struct;
        m_data_struct = temp;
      }

      void _realloc_up_()
      {
        if ((m_buffer_size - m_data_amount) <= offset)
        {
          T *temp = new T[(m_buffer_size *= 2)];
          _relocation_copy_(temp);
        }
        m_data_amount += 0x01;
      }

      void _realloc_down_()
      {
        if (((m_buffer_size - m_data_amount) > (m_buffer_size / 2) - offset) && m_data_amount > (m_buff_preinit - offset))
        {
          T *temp = new T[(m_buffer_size /= 2)];
          _relocation_copy_(temp);
        }
        if (m_data_amount > 0x00)
          m_data_amount -= 0x01;
      }

      void _shift_vector_(unsigned long cursor)
      {
        for (register unsigned long i = cursor; i < m_data_amount; i++)
          m_data_struct[i] = m_data_struct[i + 1];
      }

      bool _exist_(T data) const
      {
        if (m_data_struct)
        {
          for (unsigned long i = 0; i < m_data_amount; i++)
            if (m_data_struct[i] == data)
              return true;
        }
        return false;
      }

      T &_get_(unsigned long pos) const { return m_data_struct[pos]; }

      bool _add_(T data)
      {
        if (m_data_struct)
        {
          m_data_struct[m_data_amount] = data;
          _realloc_up_();
          return true;
        }
        return false;
      }

      bool _remove_(unsigned long pos)
      {
        if (m_data_struct && pos < m_buffer_size)
        {
          _shift_vector_(pos);
          _realloc_down_();
          return true;
        }
        return false;
      }

      Vector &_swap_(Vector<T> &swap)
      {
        T *temp = this->m_data_struct;
        unsigned long buffer_size_temp = this->m_buffer_size;
        unsigned long data_amount_temp = this->m_data_amount;
        unsigned long buff_preinit_temp = this->m_buff_preinit;
        this->m_data_struct = swap.m_data_struct;
        this->m_buffer_size = swap.m_buffer_size;
        this->m_data_amount = swap.m_data_amount;
        this->m_buff_preinit = swap.m_buff_preinit;
        swap.m_data_struct = temp;
        swap.m_buffer_size = buffer_size_temp;
        swap.m_data_amount = data_amount_temp;
        swap.m_buff_preinit = buff_preinit_temp;
        return *this;
      }

      bool _reset_()
      {
        if (m_data_struct)
        {
          m_data_amount = 0x00;
          m_buffer_size = m_buff_preinit;
          delete[] m_data_struct;
          _alloc_();
          return 1;
        }
        return 0;
      }

      bool _delete_()
      {
        if (m_data_struct)
        {
          m_data_amount = 0x00;
          m_buffer_size = 0x00;
          m_buff_preinit = 0x00;
          delete[] m_data_struct;
          m_data_struct = nullptr;
          return 1;
        }
        return 0;
      }

    public:
      Vector(unsigned long bufferReserve = 5) : m_data_amount(0x00)
      {
        m_buff_preinit = bufferReserve;
        m_buffer_size = m_buff_preinit;
        _alloc_();
      }

      Vector(Vector &cpy)
      {
        _copy_(cpy);
        *this = cpy;
      }

      Vector(Vector &&move)
      {
        _move_(move);
        *this = move;
      }

      ~Vector()
      {
        if (m_data_struct)
          delete[] m_data_struct;
      }

    public:
      /**
       * @return Returns the amount of data stored in the vector.
       */
      unsigned long Size() const { return m_data_amount; }

      /**
       * @return Returns the size of the buffer.
       */
      unsigned long ContainerSize() const { return m_buffer_size; }

      /**
       * @brief Check if the vector is empty.
       *
       * @return Returns true if empty. Otherwise, it will return false.
       */
      bool isEmpty() const { return (bool)m_data_amount; }

      /**
       * @return Returns the first element.
       */
      T &First() const { return _get_(0); }

      /**
       * @return Returns the last element.
       */
      T &Last() const { return _get_(m_data_amount - 0x01); }

      /**
       * @brief Checks true if the data exists in the vector.
       *
       * @param data Data to be verified.
       *
       * @return Returns true if the data exists in the vector.
       */
      bool Exist(T data) { return _exist_(data); }

      /**
       * @brief Returns the data stored in the vector position.
       *
       * @param pos Position in vector.
       */
      T &Get(unsigned long pos) const { return _get_(pos); }

      /**
       * @brief Add data to the last position of the vector.
       *
       * @param data Given to be written.
       */
      bool Push(T data) { return _add_(data); }

      /**
       * @brief Removes the data in the last position of the vector.
       */
      bool Pop() { return _remove_(m_data_amount - 0x01); }

      /**
       * @brief Remove data at vector position.
       *
       * @param pos Position in vector.
       */
      bool Pop(unsigned long pos) { return _remove_(pos); }

      /**
       * @brief Swap contents.
       */
      Vector &Swap(Vector<T> &swap) { return _swap_(swap); }

      /**
       * @brief Copy contents.
       */
      Vector &Copy(Vector &vector) { return _copy_(vector); }

      /**
       * @brief Resets the vector, removing all data.
       */
      bool Reset() { return _reset_(); }

      /**
       * @brief Delete the vector.
       */
      bool Delete() { return _delete_(); }
    };
  }
}