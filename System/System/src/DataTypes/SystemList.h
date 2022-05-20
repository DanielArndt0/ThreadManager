#pragma once
#include "DataTypes/SystemTypedefs.h"

namespace System
{
  namespace Data
  {
    template <typename T>
    class List
    {
    public:
      // Operators
      virtual List<T> &operator=(List<T> &list) = 0;

      // Capacity
      virtual bool isEmpty() const = 0;
      virtual unsigned long Size() const = 0;
      virtual bool Exist(T value) const = 0;

      // Element Acess
      virtual T First() const = 0;
      virtual T Last() const = 0;
      virtual T Get(System::index key) const = 0;
      virtual System::index Get(T value) const = 0;
      virtual T getErrorCase() const = 0;

      // Modifiers
      virtual T Set(System::index key, T value) = 0;
      virtual T PushFront(T value) = 0;
      virtual T PushBack(T value) = 0;
      virtual T Push(System::index key, T value) = 0;
      virtual T PopFront() = 0;
      virtual T PopBack() = 0;
      virtual T Pop(System::index key) = 0;
      virtual T Pop(T value) = 0;

      // Operations
      virtual void Copy(List<T> &list) = 0;
      virtual void Swap(List<T> &list) = 0;
      virtual void Merge(List<T> &list) = 0;
      virtual void Reverse() = 0;
      virtual void Delete() = 0;
    };
  }
}
