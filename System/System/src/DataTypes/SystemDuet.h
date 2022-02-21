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
        this->__data1__ = cpy.__data1__;
        this->__data2__ = cpy.__data2__;
      }

      void operator=(Duet &&move)
      {
        this->__data1__ = move.__data1__;
        this->__data2__ = move.__data2__;
      }

    private:
      T1 __data1__;
      T2 __data2__;

    public:
      Duet() {}
      Duet(Duet &cpy) { *this = cpy; }
      Duet(Duet &&move) { *this = move; }
      Duet(T1 data1, T2 data2) : __data1__(data1), __data2__(data2) {}
      Duet(T1 data) : __data1__(data) {}
      Duet(T2 data) : __data2__(data) {}

    public:
      /**
       * @brief Get the first value of the Duet.
       *
       * @return Returns first object.
       */
      T1 &getFirst() { return __data1__; }

      /**
       * @brief Set first value of the Duet.
       *
       * @param data Data to be defined.
       */
      void setFirst(T1 data) { __data1__ = data; }

      /**
       * @brief Get the second value of the Duet.
       *
       * @return Returns second object.
       */
      T2 &getSecond() { return __data2__; }

      /**
       * @brief Set second value of the Duet.
       *
       * @param data Data to be defined.
       */
      void setSecond(T2 data) { __data2__ = data; }

      /**
       * @brief Set the Duet.
       *
       * @param d1 Data to be defined in first value.
       *
       * @param d2 Data to be defined in second value.
       */
      void setDuet(T1 d1, T2 d2)
      {
        __data1__ = d1;
        __data2__ = d2;
      }

      /**
       * @brief Create a new duet.
       *
       * @param d1 Data to be defined in first value.
       *
       * @param d2 Data to be defined in second value.
       *
       * @return Return a new duet with set values.
       */
      static Duet<T1, T2> CreateDuet(T1 d1, T2 d2) { return Duet<T1, T2>(d1, d2); }
    };
  }
}