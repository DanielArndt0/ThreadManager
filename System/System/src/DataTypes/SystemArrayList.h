#pragma once
#include "DataTypes/SystemList.h"

namespace System
{
  namespace Data
  {
    template <typename T>
    class ArrayList : virtual public List<T>
    {
    public:
      // Operators
      T operator[](index key) const override { return this->_get_(key); }

      List<T> &operator=(List<T> &list) override
      {
        this->Copy(list);
        return *this;
      }

    private:
      unsigned long m_buffer_length;
      unsigned long m_length;
      unsigned long m_pool_init;
      T *m_data_struct;
      T m_err;

    public:
      ArrayList(unsigned long bufferReserve = 5)
      {
        m_pool_init = bufferReserve;
        m_buffer_length = m_pool_init;
        m_length = 0x00;
        _alloc_();
      }
      ~ArrayList() { _delete_(); }

    private:
      void _alloc_() { m_data_struct = new T[m_buffer_length]; }

      void _relocation_copy_(T *temp)
      {
        for (index i = 0; i < m_buffer_length; i++)
          temp[i] = m_data_struct[i];
        delete[] m_data_struct;
        m_data_struct = temp;
      }

      void _realloc_up_()
      {
        if ((m_buffer_length - m_length) <= 0x01)
        {
          T *temp = new T[(m_buffer_length * 2)];
          _relocation_copy_(temp);
          m_buffer_length *= 2;
        }
        m_length += 0x01;
      }

      void _realloc_down_()
      {
        if (((m_buffer_length - m_length) > (m_buffer_length / 2) - 0x01) && m_length > (m_pool_init - 0x01))
        {
          T *temp = new T[(m_buffer_length /= 2)];
          _relocation_copy_(temp);
        }
        if (m_length > 0x00)
          m_length -= 0x01;
      }

      void _shift_push_(unsigned long cursor)
      {
        for (index i = m_length; i > cursor; i--)
          m_data_struct[i] = m_data_struct[i - 1];
      }

      void _shift_pop_(unsigned long cursor)
      {
        for (index i = cursor; i < m_length; i++)
          m_data_struct[i] = m_data_struct[i + 1];
      }

      bool _exist_(T value) const
      {
        if (m_data_struct)
        {
          for (index i = 0; i < m_length; i++)
            if (m_data_struct[i] == value)
              return true;
        }
        return false;
      }

      T _set_(index key, T value)
      {
        if (key < m_length)
          return (m_data_struct[key] = value);
        return m_err;
      }

      T &_push_(index key, T value)
      {
        if (m_data_struct)
        {
          _realloc_up_();
          _shift_push_(key);
          m_data_struct[key] = value;
          return m_data_struct[key];
        }
        return m_err;
      }

      T _get_(index key) const
      {
        if (key < m_length)
          return m_data_struct[key];
        return m_err;
      }

      index _get_index_(T value) const
      {
        for (unsigned long i = 0; i < m_length; i++)
          if (value == m_data_struct[i])
            return i;
        return 0;
      }

      T _pop_(unsigned long key)
      {
        if (m_data_struct && key < m_buffer_length)
        {
          T tmp = m_data_struct[key];
          _shift_pop_(key);
          _realloc_down_();
          return tmp;
        }
        return m_err;
      }

      void _swap_(List<T> &list)
      {
        ArrayList<T> tmp;
        tmp.Copy(list);
        list.Copy(*this);
        this->Copy(tmp);
      }

      void _reverse_()
      {
        unsigned long size = this->Size();
        for (index i = 0; i < size; i++)
          this->_push_(0x00, this->_pop_(i));
      }

      void _reset_()
      {
        if (m_data_struct)
        {
          m_buffer_length = m_pool_init;
          m_length = 0x00;
          delete[] m_data_struct;
          _alloc_();
        }
      }

      void _delete_()
      {
        if (m_data_struct)
        {
          m_length = 0x00;
          m_buffer_length = 0x00;
          delete[] m_data_struct;
        }
      }

    public:
      // Capacity
      bool isEmpty() const override { return (m_data_struct == nullptr || !m_length); }

      unsigned long Size() const override { return m_length; }

      T getErrorCase() const override { return m_err; }

      bool Exist(T value) const override { return _exist_(value); }

      unsigned long getPoolSize() const { return m_buffer_length; }

      // Element Acess
      T First() const override { return m_data_struct[0x00]; }

      T Last() const override { return m_data_struct[m_length - 1]; }

      T Get(index key) const override { return _get_(key); }

      index Get(T value) const override { return _get_index_(value); }

      // Modifiers
      T Set(index key, T value) override { return _set_(key, value); }

      T PushFront(T value) override { return _push_(0x00, value); }

      T PushBack(T value) override { return _push_(m_length, value); }

      T Push(index key, T value) override { return _push_(key, value); }

      T PopFront() override { return _pop_(0x00); }

      T PopBack() override { return _pop_((m_length - 1)); }

      T Pop(index key) override { return _pop_(key); }

      T Pop(T value) override { return _pop_(_get_index_(value)); }

      // Operations
      void Swap(List<T> &list) override { _swap_(list); }

      void Reverse() override { _reverse_(); }

      void Reset() override { _reset_(); }

      void Delete() override { _delete_(); }
    };
  }
}