#pragma once

namespace System
{
  namespace Data
  {
    template <typename T1, typename T2>
    class Duet
    {
    public:
      void operator=(Duet &cpy)
      {
        this->__key__ = cpy.__key__;
        this->__value__ = cpy.__value__;
      }

      void operator=(Duet &&move)
      {
        this->__key__ = move.__key__;
        this->__value__ = move.__value__;
      }

    private:
      T1 __key__;
      T2 __value__;

    public:
      Duet() {}
      Duet(Duet &cpy) { *this = cpy; }
      Duet(Duet &&move) { *this = move; }
      Duet(T1 key, T2 value) : __key__(key), __value__(value) {}

    public:
      /**
       * @brief Get the first value of the Duet.
       *
       * @return Returns first object.
       */
      T1 &getFirst() { return __key__; }

      /**
       * @brief Set first value of the Duet.
       *
       * @param data Data to be defined.
       */
      void setFirst(T1 data) { __key__ = data; }

      /**
       * @brief Get the second value of the Duet.
       *
       * @return Returns second object.
       */
      T2 &getSecond() { return __value__; }

      /**
       * @brief Set second value of the Duet.
       *
       * @param data Data to be defined.
       */
      void setSecond(T2 data) { __value__ = data; }

      /**
       * @brief Set the Duet.
       *
       * @param d1 Data to be defined in first value.
       *
       * @param d2 Data to be defined in second value.
       */
      void setDuet(T1 d1, T2 d2)
      {
        __key__ = d1;
        __value__ = d2;
      }

      /**
       * @brief Create a new duet.
       *
       * @param d1 Key to be defined.
       *
       * @param d2 Value to be defined.
       *
       * @return Return a new duet with set values.
       */
      static Duet<T1, T2> CreateDuet(T1 d1, T2 d2) { return Duet<T1, T2>(d1, d2); }
    };
  }
}