#pragma once
#include "DataTypes/SystemList.h"

namespace System
{
  namespace Data
  {
    template <typename T>
    class LinkedList : virtual public List<T>
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
      struct element
      {
        T m_data;
        element *m_next_element = nullptr;
      };

    private:
      unsigned long m_length;
      element *m_first;
      T m_err;

    public:
      LinkedList()
      {
        m_first = nullptr;
        m_length = 0x00;
      }
      LinkedList(List<T> &list)
      {
        m_first = nullptr;
        m_length = 0x00;
        this = list;
      }
      ~LinkedList() { _delete_(); }

    private:
      element *_last_()
      {
        element *tmp = m_first;
        while (tmp->m_next_element != nullptr)
          tmp = tmp->m_next_element;
        return tmp;
      }

      T _set_(index key, T value)
      {
        element *tmp = _search_(key);
        if (tmp == nullptr)
          return m_err;
        return (tmp->m_data = value);
      }

      T _push_(index key, T value)
      {
        if (key > (m_length))
          return m_err;
        element *newElement = new element;
        newElement->m_data = value;
        if (isEmpty() || !key)
        {
          newElement->m_next_element = this->m_first;
          this->m_first = newElement;
          m_length++;
          return newElement->m_data;
        }
        element *prev = _search_(key - 1);
        newElement->m_next_element = prev->m_next_element;
        prev->m_next_element = newElement;
        m_length++;
        return newElement->m_data;
      }

      T _pop_(index key)
      {
        if (isEmpty() || key > (m_length - 1))
          return m_err;
        element *previous = nullptr;
        element *current = nullptr;
        T current_data;

        if (!key)
        {
          current = m_first;
          current_data = m_first->m_data;
          m_first = m_first->m_next_element;
          m_length--;
          delete current;
          return current_data;
        }
        previous = _search_(key - 1);
        current = previous->m_next_element;
        current_data = current->m_data;
        previous->m_next_element = previous->m_next_element->m_next_element;
        m_length--;
        delete current;
        return current_data;
      }

      T _get_(index key) const
      {
        if (isEmpty() || key > (m_length - 1))
          return m_err;
        element *tmp = m_first;
        for (index i = 0; i < key; i++)
          tmp = tmp->m_next_element;
        return tmp->m_data;
      }

      index _get_index_(T value) const
      {
        for (index i = 0; i < m_length; i++)
          if (value == _get_(i))
            return i;
        return 0;
      }

      element *_search_(index key)
      {
        if (isEmpty() || key > (m_length - 1))
          return nullptr;
        element *tmp = m_first;
        for (index i = 0; i < key; i++)
          tmp = tmp->m_next_element;
        return tmp;
      }

      void _swap_(List<T> &list)
      {
        LinkedList<T> tmp;
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

      void _reset_() { _delete_(); }

      void _delete_()
      {
        unsigned long total = m_length;
        for (index i = 0; i < total; i++)
          _pop_(0x00);
        m_first = nullptr;
      }

    public:
      // Capacity
      bool isEmpty() const override { return m_first == nullptr || !m_length; }

      unsigned long Size() const override { return m_length; }

      bool Exist(T value) const override { return _get_index_(value) ? true : false; }

      T getErrorCase() const override { return m_err; }

      // Element Acess
      T First() const override { return _get_((index)0); }

      T Last() const override { return _get_((index)(m_length - 1)); }

      T Get(index key) const override { return _get_(key); }

      index Get(T value) const override { return _get_index_(value); }

      // Modifiers
      T Set(index key, T value) override { return _set_(key, value); }

      T PushFront(T value) override { return _push_(0x00, value); }

      T PushBack(T value) override { return _push_(m_length, value); }

      T Push(index key, T value) override { return _push_(key, value); }

      T PopFront() override { return _pop_(0x00); }

      T PopBack() override { return _pop_(m_length - 1); }

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
