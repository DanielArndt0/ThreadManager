#pragma once
#include "DataTypes/SystemTypedefs.h"
#include "DataTypes/ArrayContainer.h"
#include "DataTypes/ListContainer.h"

namespace System
{
  namespace Data
  {
    template <typename T>
    class ArrayList : virtual public ArrayContainer<T>, virtual public List<T>
    {
    public:
      // Operators
      T operator[](index key) const override { return this->cGet(key); }

      List<T> &operator=(List<T> &list) override
      {
        this->Copy(list);
        return *this;
      }

    public:
      // Capacity
      bool isEmpty() const override { return this->cIsEmpty(); }

      unsigned long Size() const override { return this->cSize(); }

      T Error() const override { return this->cError(); }

      bool Exist(T value) const override { return this->cExist(value); }

      unsigned long getPoolSize() const { return this->cGetPoolSize(); }

      // Element Acess
      T First() const override { return this->cGet(0x00); }

      T Last() const override { return this->cGet(this->cSize() - 1); }

      T Get(index key) const override { return this->cGet(key); }

      index Get(T value) const override { return this->cGetIndex(value); }

      // Modifiers
      T Put(index key, T value) override { return this->cPut(key, value); }

      T PushFront(T value) override { return this->cPushFront(value); }

      T PushBack(T value) override { return this->cPushBack(value); }

      T Push(index key, T value) override { return this->cPush(key, value); }

      T PopFront() override { return this->cPop(0x00); }

      T PopBack() override { return this->cPop(this->cSize() - 1); }

      T Pop(index key) override { return this->cPop(key); }

      T Pop(T value) override { return this->cPop(this->cGetIndex(value)); }

      void Reset() override { this->cReset(); }

      void Delete() override { this->cDelete(); }

      void Swap(List<T> &list) override
      {
        ArrayList<T> tmp;
        tmp.Copy(list);
        list.Copy(*this);
        this->Copy(tmp);
      }
    };
  }
}