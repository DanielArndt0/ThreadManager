#pragma once
#include "DataTypes/SystemTypedefs.h"
#include "DataTypes/SimpleContainer.h"
#include "DataTypes/LinkedContainer.h"

namespace System
{
  namespace Data
  {
    template <typename T>
    class LinkedQueue : virtual public LinkedContainer<T>, virtual public SimpleContainer<T>
    {
    public:
      bool isEmpty() const override { return this->cIsEmpty(); }

      unsigned long Size() const override { return this->cSize(); }

      T Error() const override { return this->cError(); }

      T First() const override { return this->cGet((index)0); }

      T Last() const override { return this->cGet((index)(this->cSize() - 1)); }

      T Push(T value) override { return this->cPushBack(value); }

      T Pop() override { return this->cPopFront(); }

      void Reset() override { this->cReset(); }

      void Delete() override { this->cDelete(); }
    };
  }
}